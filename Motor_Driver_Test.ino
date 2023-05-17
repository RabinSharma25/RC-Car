
/*
                         ***************This program is written to test the TB6612FNG dual motor driver module*****************
  We assume that the motor has two polarities (+ve and -ve).
  The connection must be done in such a way that whenever the +ve and -ve terminals of the BO motors are connected to+ve and -ve terminals of the battery respectively it must make a clockwise rotation


  connections:

  Motor driver and motors connection
  MotorA-
  +ve -- A02
  -ve -- A01

  MotorB-
  +ve -- B01
  -ve -- B02

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



   Note: for better visualization of the motor rotations place the MotorA to the left rear and MotorB to the right rear of the frame where both the motors are facing outward.
   This code will do the following rotations

   1. Rotate MotorA forward and MotorB forward

   wait for 10 sec

   2. Rotate MotorA backward and MotorB backward

   wait for 10 sec

   3. Rotate MotorA forward and stop MotorB

   wait for 10 sec

   4. Stop MotorA and rotate MotorB forward

   wait for 10 sec

   5. Rotate MotorA forward and MotorB backward

   wait for 10 sec

   6. Rotate MotorA backward and MotorB forward

*/

// Motor A
int pwmA = 5;
int in1A = 2;
int in2A = 3;

// Motor B
int pwmB = 6;
int in1B = 4;
int in2B = 7;
int del = 10000;

void setup()
{
  // Set all the motor control pins to outputs
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);

  // Rotate MotorA and MotorB forward
  for (int i = 0; i <= 255; i++)
  {
    // accelerator values
    analogWrite(pwmA, i);
    analogWrite(pwmB, i);

    // Set Motor A forward
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);

    // Set Motor B forward
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, HIGH);
    delay(10);
  }

  delay(del);

  // Rotate MotorA and MotorB backward
  for (int i = 0; i <= 255; i++)
  {
    // accelerator values
    analogWrite(pwmA, i);
    analogWrite(pwmB, i);

    // Set Motor A backward
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);

    // Set Motor B backward
    digitalWrite(in1B, HIGH);
    digitalWrite(in2B, LOW);
    delay(10);
  }

  delay(del); // 10 sec delay

  // Rotate MotorA forward and stop MotorB
  for (int i = 0; i <= 255; i++)
  {
    // accelerator values
    analogWrite(pwmA, i);
    analogWrite(pwmB, i);

    // Set Motor A forward
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);

    // Stop motor B
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, LOW);
    delay(10);
  }

  delay(del);

  // Rotate MotorB forward and stop MotorA
  for (int i = 0; i <= 255; i++)
  {
    // accelerator values
    analogWrite(pwmA, i);
    analogWrite(pwmB, i);

    // Stop Motor A
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, LOW);

    //Set Motor B forward
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, HIGH);
    delay(10);
  }

  delay(del);

  // Rotate MotorA forward and MotorB backward
  for (int i = 0; i <= 255; i++)
  {
    // accelerator values
    analogWrite(pwmA, i);
    analogWrite(pwmB, i);

    // Set Motor A forward
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);

    //Set Motor B backward
    digitalWrite(in1B, HIGH);
    digitalWrite(in2B, LOW);
    delay(10);
  }

  delay(del);

  // Rotate MotorB forward and MotorA backward
  for (int i = 0; i <= 255; i++)
  {
    // accelerator values
    analogWrite(pwmA, i);
    analogWrite(pwmB, i);

    // Set MotorA backward
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);

    //Set MotorB forward
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, HIGH);
    delay(10);
  }

  delay(del);

  // stop all the motors
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, LOW);
  digitalWrite(in1B, LOW);
  digitalWrite(in2B, LOW);
}

void loop()
{

}
