// Pin connection definitions
#define x_p  A0 // A0
#define x_n  A1 // A1
#define y_p  A3 // A3
#define y_n  A4 // A4

uint32_t read_x_coord(void);
uint32_t read_y_coord(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.print("\nStarting setup\n");

  pinMode(y_p,INPUT);
  pinMode(y_n,INPUT);  
  //digitalWrite(y_n,LOW);

  pinMode(x_p,OUTPUT);
  digitalWrite(x_p,LOW);
  pinMode(x_n,OUTPUT);
  digitalWrite(x_n,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.print(read_x_coord());
  Serial.print(",");
  Serial.print(read_y_coord());
  Serial.print("\n");
  delay(5);
}

uint32_t read_x_coord(void) {
  pinMode(y_p,INPUT);
  pinMode(y_n,INPUT);  
  //digitalWrite(y_n,LOW);

  pinMode(x_p,OUTPUT);
  digitalWrite(x_p,LOW);
  pinMode(x_n,OUTPUT);
  digitalWrite(x_n,HIGH);
  return analogRead(y_n);
}
uint32_t read_y_coord(void) {
  pinMode(x_p,INPUT);
  pinMode(x_n,INPUT);  
  //digitalWrite(y_n,LOW);

  pinMode(y_p,OUTPUT);
  digitalWrite(y_p,LOW);
  pinMode(y_n,OUTPUT);
  digitalWrite(y_n,HIGH);
  return analogRead(x_n);
}
