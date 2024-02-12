
int yellowLed = 3;
int redLed = 4;
int greenLed = 8;
int gasSensor = A0;  // Analog pin connected to the gas sensor
int flameSensor = 2;  // Digital pin connected to the flame sensor
int buzzer1 = 5; // PWM (~) pin
int buzzer2 = 6; // PWM (~) pin

// Threshold value based on several tests on tinkercad
int gasSensorThres = 100;



void setup() {
  pinMode(yellowLed, OUTPUT);  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(gasSensor, INPUT);
  pinMode(flameSensor, INPUT);
  Serial.begin(9600);

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
delay(2000);
}