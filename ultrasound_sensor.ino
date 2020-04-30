//DEMO for sending data from arduino to pure data through serial communication.
//Note: here Serial.write() is used. This writes binary data to the serial port. The numbers you can send are limited to a range of 0 - 255. If you need to send bigger values look at this tutorial: https://www.arduino.cc/en/Tutorial/SerialCallResponseASCII

//Sensor 1
int trigPin1 = 11;    // Trigger
int echoPin1 = 12;    // Echo

//variables
long duration1, cm, distance1;
long unsigned currentMillis, previousMillis = 0;
int interval = 100;
int i= 0;
int lowerTwoDigits, higherTwoDigits = 0;

void setup() {
  //Start serial connection
  Serial.begin(9600);
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

}

void loop() {

  // Sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;
  Serial.print ( "Sensor1:  ");
  Serial.print ( distance1);
  Serial.println("cm");


  delay(500);

  ///////////////////////////////////////////////////////////////////////////////////////////////


  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    Serial.write(255); //send the value 255 to indicate that we are sending a set of new values. The PD patch uses this to synchronize to the data.
    i = distance1;
    i = i % 1024;
    lowerTwoDigits =  i % 100;
    higherTwoDigits =  i / 100;
    Serial.write(lowerTwoDigits);
    Serial.write(higherTwoDigits);

    previousMillis = currentMillis;
  }
}
