# A Mobile and Subtle Gesture Recognition System

Modern phones can detect external gestures to control features such as Apple's double/triple tap on the back of the phone or Samsung's S-Pen gesture recognition. However, these solutions offer a limited quantity of built-in tasks. For example, Apple's double/triple tap gestures can only map to two built-in tasks. And the S-Pen only supports six and is limited to interacting with a single phone.

The prototype's distinctions from related works include a pocket-size form-factor, including the sensors and computing resources contrasting PocketTouch. It will also be "always available". This is achieved using a resistive touchpad to detect and configure gestures to support more tasks and third-party apps like If This Then That (IFTTT). It can significantly expand the number of gestures the user in a subtle manner. Additionally, the system can act independently of the phone since it will be connected to WiFi via the ESP32. The modular nature means it can be used while attached to the phone, sitting on a desk, or connected to a laptop. 

The gestural input system comprises of: 1) a template matching algorithm that has 97+\% accuracy with one loaded template, 2) ESP32 microcontroller (a low-cost, low-power system on a chip), 3) a 3.7-inch Adafruit Resistive Touch screen, 4) Spotify API, and 5) IFTTT WebHooks. 

In the end, the gesture suite allows the user to: 1) pause a track, 2) resume a track, 3) save a track to a Liked Songs playlist, 4) re-calibrate the custom gesture, and 5) a custom gesture determined by the user.

**Steps to replicate results:**

# Hardware

## Materials

 - ESP32 ESP-32S WiFi Development Board ESP-WROOM-32 NodeMCU-32S Microcontroller Processor Integrated
 - Adafruit Resistive Touchscreen - 3.7" Diagonal
 - Adafruit Touch Screen Breakout Board for 4 pin 1.0mm FPC
 - USB 2.0 Cable A Male to Micro B Male
 - Power source (we used our laptop)

## Assembly
![Hardware Connections](https://raw.githubusercontent.com/rishabhpar/Resistive-Touch-Gesture-Recognition/main/Documentation/Figures/hw_connection.jpeg)

The output from the touch screen is connected through a ribbon cable which is difficult to wire to a microcontroller. Instead, a breakout board was used which simply splits the ribbon cable to output pins that can be connected to a breadboard as seen in the figure above.

The X+, X-, Y+, Y- pins are marked on the breakout board. Connect X+ to pin 4 of the ESP32, X- to pin 33, Y+ to pin 32, Y- to pin 15 via a breakout board

Connect the ESP32 to the USB cable tethered to the power source.

# Software

## Arduino IDE Setup

 1. Git clone the repo
 2. For the driver, you need to added folders+files in the C:\Program Files (x86)\Arduino\libraries folders
		so for Windows (Mac steps to come):

	- put **src\DebugPrint.h** in C:\Program Files (x86)\Arduino\libraries\DebugPrint folder
	-  put **src\GestureProcessing.h** and **src\GestureProcessing.cpp** in C:\Program Files (x86)\Arduino\libraries\GestureProcessing folder
	-  put **src\MicroDollar.h** and **src\MicroDollar.cpp** in C:\Program Files (x86)\Arduino\libraries\MicroDollar folder
	-  put **src\Recognizer.h** in C:\Program Files (x86)\Arduino\libraries\Recognizer folder
	-  put **src\Templates.h** in C:\Program Files (x86)\Arduino\libraries\Templates folder
3. Copy the **spotify-arduino-api-main** folder to C:\Users\ {user_name} \Documents\Arduino\libraries
4. Create a **secrets.h** file in the driver\data folder. In it you include:
	- const char SECRET_SSID[] = ""; // WiFi Credential
	- const char SECRET_PASS[] = "";	// WiFi Credential
	- const char SECRET_CLIENT_ID[] = ""; // Spotify Credential
	- const char SECRET_CLIENT_SECRET[] = "";	// Spotify Credential
5. In the Arduino IDE, go to Sketch > Include Library > Manage Libraries to add the **CircularBuffer 1.3.3** and **Adafruit TouchScreen 1.1.3** libraries.

## Spotify Setup

The client ID and client secret key can be created when making a project in [Spotify for Developers](https://developer.spotify.com/dashboard/). The refresh token was generated at this [site](https://getyourspotifyrefreshtoken.herokuapp.com/). The refresh token will be inserted as a string in driver/driver.ino as a constant.

## Flash

Compile and flash the code in **driver\driver.ino**

Ground truth templates are stored at **driver\data\template_data_int_normalized_64_ {x} .h**

Enjoy!