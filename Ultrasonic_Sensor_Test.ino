/*
                **********************This code is meant to test the HC-SR04 ultrasonic sensor*******************
Connections:-
Vcc -- 5v
Trig -- A0
Echo -- A1
Gnd -- Gnd 

Note: This code gives the distance (in cm) of the obstacle from the sensor
*/


// defines pins numbers
const int trigPin = A0;
const int echoPin = A1;
// defines variables
long duration;
int distance;
void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop() 
{
  int distance = obstacleDist();
  Serial.print("Distance: ");
  Serial.println(distance);
}

int obstacleDist() 
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  
  // when the sensor is too near to the obstacle it gives garbage values to avoid this we run the lines of code below
  if (distance >= 1000) 
  {
    distance = 0;
  }

  return distance;
}
