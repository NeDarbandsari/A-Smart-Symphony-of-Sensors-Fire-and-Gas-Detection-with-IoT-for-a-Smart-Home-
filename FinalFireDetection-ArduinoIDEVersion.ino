#include <WiFiNINA.h>
#include <ThingSpeak.h>

char ssid[] = "Nathan's iPhone";
char pass[] = "test111!";
WiFiClient client;

unsigned long myChannelNumber =2354309;
const char * myWriteAPIKey = "BA5YN5SQFZAK05KI";

int yellowLed = 3;
int redLed = 4;
int greenLed = 8;
int gasSensor = A0;  // Analog pin connected to the gas sensor
int flameSensor = 2;  // Digital pin connected to the flame sensor
int buzzer1 = 5; // PWM (~) pin
int buzzer2 = 6; // PWM (~) pin

// Threshold value based on several tests
int gasSensorThres = 300;



void setup() {
  pinMode(yellowLed, OUTPUT);  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(gasSensor, INPUT);
  pinMode(flameSensor, INPUT);
  Serial.begin(9600);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
 
  ThingSpeak.begin(client); // Initialize ThingSpeak
}


void loop() {
  int gasSensorValue = analogRead(gasSensor);
  int flameSensorValue = digitalRead(flameSensor);
  Serial.print("gasSensor Value: ");
  Serial.println(gasSensorValue);
  Serial.print("flameSensor Value: ");
  Serial.println(flameSensorValue);

  if (gasSensorValue > gasSensorThres && flameSensorValue == LOW) {
    digitalWrite(yellowLed, HIGH);
    tone(buzzer1, 5000); // the buzzer sound frequency at 5000 Hz
    digitalWrite(redLed, HIGH);
    tone(buzzer2, 5000); // the buzzer sound frequency at 5000 Hz
    digitalWrite(greenLed, LOW);
    Serial.println("FIRE!! FIRE!!");

  } else if (gasSensorValue > gasSensorThres) {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    tone(buzzer1, 5000); // the buzzer sound frequency at 5000 Hz
    digitalWrite(redLed, LOW);
    noTone(buzzer2);
    Serial.println("Gas detected!!");

  } else if (flameSensorValue == LOW) {
    // HIGH MEANS NO FLAME
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    noTone(buzzer1);
    digitalWrite(redLed, HIGH);
    tone(buzzer2, 5000); // the buzzer sound frequency at 5000 Hz
    Serial.println("Fire detected!!");

  } else {
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    noTone(buzzer1);
    noTone(buzzer2);
  }

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
      }
    Serial.println("\nConnected.");
  }
 
 
 // Write to ThingSpeak
 
 
 ThingSpeak.setField(1, gasSensorValue);
 ThingSpeak.setField(2, flameSensorValue);
 int x=ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

 
 if(x == 200){
  Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
 
  delay(20000); // Wait 20 seconds to update the channel again


}