/*
            ****************************Code For four BO wheeled RC car***************************
components used:-
1. B0 motors X 4
2. Wheels X 4
3. TB6612FNG dual channel motor driver
4. HC-SR04 ultrasonic sensor
5. FlySky Fs-i6 transmitter module
6. FlySky FS-iA6B receiver module
7. Arduino Nano
8. 3.7V, 2000mah  18650 lithium ion battery X 2


Connections:-

  Motor driver and motors connection
  MotorA-
  +ve -- A01
  -ve -- A02

  MotorB-
  +ve -- B02
  -ve -- B01

  Motor dirver and Arduino connections
  D2 -- AIN1
  D3 -- AIN2
  D4 -- BIN1
  D5 -- PWMA
  D6 -- PWMB
  D7 -- BIN2
  5V -- VCC
  5V -- STBY
  GND -- GND
  VM -- Battery +ve

  Receiver and Arduino Connections
  D8 -- Ch1 // Roll
  D9 -- Ch2 // Pitch
  D10 -- Ch3 // Gas
  D11 -- Ch4 // Yaw
  5V -- +ve
  GND -- -ve

  Arduino and battery connection
  Vin -- +ve Battery
  Gnd -- -ve Battery


  Usage:-
  1. Here the throttle stick of the transmitter works as a accelerator.
  2. The yaw stick can be used to rotate the car clockwise or anti-clockwise.
  3. The roll stick can be used to turn the rc car left or right.
  4. The pitch stick can be used to move the car forward of backward.
  5. No two stick must be moved simultaneously(except throttle stick), if it is done it will make the car stop
  6. If any obstacle comes in front(<=15 cm) of the rc car it automatically stops.
  
*/




// variable to capture the receiver pulses
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
int receiver_input[5];
unsigned long timer_1, timer_2, timer_3, timer_4, current_time;

// Motor A
int pwmA = 5;
int in1A = 2;
int in2A = 3;


// Motor B
int pwmB = 6;
int in1B = 4;
int in2B = 7;


// ultrasonic sensor pins
const int trigPin = A0;
const int echoPin = A1;
// defines variables
long duration;
int distance;

void setup()
{
    Serial.begin(9600);
    PCICR |= (1 << PCIE0);   // Set PCIE0 to enable PCMSK0 scan.
    PCMSK0 |= (1 << PCINT0); // Set PCINT0 (digital input 8) to trigger an interrupt on state change.
    PCMSK0 |= (1 << PCINT1); // Set PCINT1 (digital input 9)to trigger an interrupt on state change.
    PCMSK0 |= (1 << PCINT2); // Set PCINT2 (digital input 10)to trigger an interrupt on state change.
    PCMSK0 |= (1 << PCINT3); // Set PCINT3 (digital input 11)to trigger an interrupt on state change.

    // Set all the motor control pins to outputs
    pinMode(pwmA, OUTPUT);
    pinMode(pwmB, OUTPUT);
    pinMode(in1A, OUTPUT);
    pinMode(in2A, OUTPUT);
    pinMode(in1B, OUTPUT);
    pinMode(in2B, OUTPUT);

  // ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//  Serial.begin(9600); // Starts the serial communication
}

void loop()
{   
    // Map the reciver inputs of (1000 - 2000) to (0 - 255)
    int val1 = map(receiver_input[3], 1000, 2000, 0, 255); // throttle
    int val2 = map(receiver_input[1], 1000, 2000, 0, 255); // roll (left / right)
    int val3 = map(receiver_input[2], 1000, 2000, 0, 255); // pitch (forward backward)
    int val4 = map(receiver_input[4], 1000, 2000, 0, 255); // rotation in circle

    // Some conditions for vehicle manuevers
    bool val2Right = val2 > 137 && val2 <= 255;
    bool val2Mid = val2 >= 117 && val2 <= 137;
    bool val2Left = val2 >= 0 && val2 < 117;

    bool val3Forward = val3 > 137 && val3 <= 255;
    bool val3Mid = val3 >= 117 && val3 <= 137;
    bool val3Backward = val3 >= 0 && val3 < 117;

    bool val4Clock = val4 > 137 && val4 <= 255;
    bool val4Mid = val4 >= 117 && val4 <= 137;
    bool val4Aclock = val4 >= 0 && val4 < 117;

    // throttle values
    analogWrite(pwmA, val1);
    analogWrite(pwmB, val1);
    int obsDist = obstacleDist();
    int minDist = 15;
//    Serial.println(obsDist);

    if (val3Forward == true && val2Mid == true && val4Mid == true && obsDist>=minDist)
    {
        // move forward
        // Set Motor A forward
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, HIGH);
        // Set Motor B forward
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, HIGH);
    }

    else if (val3Backward == true && val2Mid == true && val4Mid == true)
    {
        // move backward
        // Set Motor A backward
        digitalWrite(in1A, HIGH);
        digitalWrite(in2A, LOW);
        // Set Motor B backward
        digitalWrite(in1B, HIGH);
        digitalWrite(in2B, LOW);
    }

    else if (val2Right == true && val3Mid == true && val4Mid == true)
    {
        // turn right
        // Set Motor A forward
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, HIGH);

        // Stop motor B
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, LOW);
    }

    else if (val2Left == true && val3Mid == true && val4Mid == true)
    {
        // turn left
        // Stop Motor A
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, LOW);

        //Set Motor B forward
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, HIGH);
    }
    else if (val4Clock == true && val3Mid == true && val2Mid == true)
    {
        // rotate clock wise
        // Set Motor A forward
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, HIGH);
        // Set Motor B backward
        digitalWrite(in1B, HIGH);
        digitalWrite(in2B, LOW);
    }

    else if (val4Aclock == true && val3Mid == true && val2Mid == true)
    {
        // rotate anti cock wise
        // Set Motor A backward
        digitalWrite(in1A, HIGH);
        digitalWrite(in2A, LOW);
        // Set Motor B forward
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, HIGH);
    }

    else
    {
        // stop all the motors
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, LOW);
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, LOW);
    }
}


ISR(PCINT0_vect)
{
    current_time = micros();
    // Channel 1=========================================
    if (PINB & B00000001)
    { // Is input 8 high?
        if (last_channel_1 == 0)
        {                           // Input 8 changed from 0 to 1.
            last_channel_1 = 1;     // Remember current input state.
            timer_1 = current_time; // Set timer_1 to current_time.
        }
    }
    else if (last_channel_1 == 1)
    {                                               // Input 8 is not high and changed from 1 to 0.
        last_channel_1 = 0;                         // Remember current input state.
        receiver_input[1] = current_time - timer_1; // Channel 1 is current_time - timer_1.
    }
    // Channel 2=========================================
    if (PINB & B00000010)
    { // Is input 9 high?
        if (last_channel_2 == 0)
        {                           // Input 9 changed from 0 to 1.
            last_channel_2 = 1;     // Remember current input state.
            timer_2 = current_time; // Set timer_2 to current_time.
        }
    }
    else if (last_channel_2 == 1)
    {                                               // Input 9 is not high and changed from 1 to 0.
        last_channel_2 = 0;                         // Remember current input state.
        receiver_input[2] = current_time - timer_2; // Channel 2 is current_time - timer_2.
    }
    // Channel 3=========================================
    if (PINB & B00000100)
    { // Is input 10 high?
        if (last_channel_3 == 0)
        {                           // Input 10 changed from 0 to 1.
            last_channel_3 = 1;     // Remember current input state.
            timer_3 = current_time; // Set timer_3 to current_time.
        }
    }
    else if (last_channel_3 == 1)
    {                                               // Input 10 is not high and changed from 1 to 0.
        last_channel_3 = 0;                         // Remember current input state.
        receiver_input[3] = current_time - timer_3; // Channel 3 is current_time - timer_3.
    }
    // Channel 4=========================================
    if (PINB & B00001000)
    { // Is input 11 high?
        if (last_channel_4 == 0)
        {                           // Input 11 changed from 0 to 1.
            last_channel_4 = 1;     // Remember current input state.
            timer_4 = current_time; // Set timer_4 to current_time.
        }
    }
    else if (last_channel_4 == 1)
    {                                               // Input 11 is not high and changed from 1 to 0.
        last_channel_4 = 0;                         // Remember current input state.
        receiver_input[4] = current_time - timer_4; // Channel 4 is current_time - timer_4.
    }
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
  // Prints the distance on the Serial Monitor
  if(distance >=1000){
    distance = 0;
  }
  return distance;
}
