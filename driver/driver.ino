#include "TouchScreen.h"

#include "data/template_data_int_normalized_64_2.h"
using namespace TemplateDataIntNormalized64_2;

#include <DebugPrint.h>
#include <GestureProcessing.h>
#include <MicroDollar.h>
#include <Recognizer.h>
#include <Templates.h>
#include <CircularBuffer.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>


#include <SpotifyArduino.h>
#include <ArduinoJson.h>
#include <SpotifyArduinoCert.h>

#define WIFI 1

// Pin connection definitions
#define x_p  4 
#define x_n  33   // X_N Must be analog
#define y_p  32   // Y_P Must be analog
#define y_n  15 

#define SPOTIFY_MARKET "US"
#define SPOTIFY_REFRESH_TOKEN "AQDFVEEXBRCmN-ld4xxoeouF-ny9WZl0hr_ZYTLzEypWnFJmngtHRLTCiI501YBPVyF9cYYwqf_FEm4FF2PammWlV03bXTVRQZX3tD9ANmj3U1HnHZP-rvZwnp-s3p2j8sE"

MicroDollar dollar;
TouchScreen ts = TouchScreen(x_p, y_p, x_n, y_n, 600);

int addedPoints = 0;
int gesture;
int downSample;

const uint16_t num_of_elements = 64;
CircularBuffer<int, num_of_elements> inputGesture; 

/* WIFI CONNECTIONS */
const char* ssid = "utexas-iot";
const char* password =  "9943599082525808";
const char* host = "maker.ifttt.com";
const int httpsPort = 443;
WiFiClientSecure client;

/* SPOTIFY CONNECTIONS */
char clientId[] = "735b983b9cb6498f96476efc4f18e517";     // Your client ID of your spotify APP
char clientSecret[] = "fc9688121c9e4bdf929f0c5d6760865b"; // Your client Secret of your spotify APP (Do Not share this!)
SpotifyArduino spotify(client, clientId, clientSecret, SPOTIFY_REFRESH_TOKEN);

unsigned long delayBetweenRequests = 60000; // Time between requests (1 minute)
unsigned long requestDueTime;               //time when request due

/* Internal methods*/
void Capture_new_gesture(void);
void Play_Music(void);
void Pause_Music(void);

void setup() {
  Serial.begin(115200);

  dollar.init(samplePoints, nSamplePoints, samplesNormalized, sampleNames, nTemplates);

/* WIFI CONNECTION */
#if WIFI
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  client.setCACert(spotify_server_cert);

  Serial.println("Refreshing Access Tokens");
  if (!spotify.refreshAccessToken())
  {
      Serial.println("Failed to get access tokens");
  }

  
#endif
}

void recognizePoints() {
  addedPoints = 0;
  int increment = 1;

  while (inputGesture.available() > 0){ // pad the remaining with the last x,y coordinate
    int first = inputGesture[inputGesture.size() - 2];
    int second = inputGesture.last();

    inputGesture.push(first);
    inputGesture.push(second);
  }

  for (int i = 0; i < num_of_elements; i = i += 2)
  {
    int x = inputGesture[i];
    int y = inputGesture[i + 1];

    bool added = dollar.update(x, y);

    if (added)
      addedPoints++;
  }

  dollar.recognize();
}

void loop() {
  uint16_t pressure = ts.pressure();
  if (pressure > 200 && pressure < 2500 ) { // is pressed -> collect points
    uint16_t x = ts.readTouchX();
    uint16_t y = ts.readTouchY();

    Serial.print(x); Serial.print(","); Serial.print(y); Serial.print("\n");

    inputGesture.push(x);
    inputGesture.push(y);
    // if (inputGesture.isFull()) { // if 32 points have been collected -> try classifying
    //   recognizePoints();
    //   if (dollar.getScore() > 90){
    //     Serial.print(dollar.getName()); Serial.print("\n");
    //   }
    // }
  } else if (!inputGesture.isEmpty()) { // unpressed and contains values to classify -> classify
      recognizePoints();
      String classification = dollar.getName();      
      Serial.print(classification); Serial.print("\n");
      if(classification.equals("o")) {
        Play_Music();
      } else if(classification.equals("s")) {
        Pause_Music();
      } else if(classification.equals("c")) {
        if (millis() > requestDueTime){
            ESP.getFreeHeap();
    
            Serial.println("getting currently playing song:");
            int status = spotify.getCurrentlyPlaying(likeCurrentlyPlaying, SPOTIFY_MARKET);
            if (status == 200){
                Serial.println("Successfully got currently playing");
            } else if (status == 204){
                Serial.println("Doesn't seem to be anything playing");
            } else {
                Serial.print("Error: ");
                Serial.println(status);
            }
            requestDueTime = millis() + delayBetweenRequests;
        }  
      }
      inputGesture.clear();
  }

  delay(50);
}

void Play_Music(void) {
  client.setInsecure();
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  } else {
    Serial.println("Connected");
  }

  String url = "/trigger/ESP32-Gesture-Play/with/key/bCeqREdaNnm2WIpAMQpHlI";

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP32\r\n" +
               "Connection: close\r\n\r\n");


  Serial.println("request sent");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  String line = client.readStringUntil('\n');

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}

void Pause_Music(void) {
  client.setInsecure();
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  } else {
    Serial.println("Connected");
  }

  String url = "/trigger/ESP32-Gesture-Pause/with/key/bCeqREdaNnm2WIpAMQpHlI";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP32\r\n" +
               "Connection: close\r\n\r\n");


  Serial.println("request sent");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  String line = client.readStringUntil('\n');

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}

void likeCurrentlyPlaying(CurrentlyPlaying currentlyPlaying){
  HTTPClient https;
  https.begin(client, "https://maker.ifttt.com/trigger/ESP32-Gesture-Like/with/key/bCeqREdaNnm2WIpAMQpHlI");
  https.addHeader("Content-Type", "application/json");
  String data  = "{\"value1\":\"" + (String)currentlyPlaying.trackName + "\",\"value2\":\"" + (String)currentlyPlaying.artists[0].artistName + "\"}";

  int httpResponseCode = https.POST(data);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
}

//
///* Reads new gesture and adds to classification*/
//void Capture_new_gesture(void) {
//  int i = 0;
//  while(i < 64) {
//    uint16_t pressure = ts.pressure();
//    if(pressure < 5000) {
//      Serial.println("----");
//      Serial.print(custom[i]);
//      Serial.print(",");
//      Serial.println(custom[i+1]);
//      Serial.print(i);
//      Serial.print(". ");
//      uint16_t x = ts.readTouchX();
//      uint16_t y = ts.readTouchY();
//      Serial.print(x); Serial.print(","); Serial.print(y); Serial.print("\n");
//      custom[i] = x;
//      custom[i+1] = y;
//      Serial.print(custom[i]);
//      Serial.print(",");
//      Serial.println(custom[i+1]);
//      i += 2;
//    }
//    delay(50);
//  }
//  Serial.println("Finished custom");
//
//  /* Reinit recognition to upload custom gesture */
//  
//  /*Wait for user to lift finger */
//  while(ts.pressure() < 2500);
//  inputGesture.clear();
//
//}
