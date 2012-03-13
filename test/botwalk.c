
// MOTOR PINS
const int LEFT_IN1 = 8;
const int LEFT_IN2 = 9;
const int LEFT_ENA = 10;
const int RIGHT_ENB = 11;
const int RIGHT_IN3 = 12;
const int RIGHT_IN4 = 13;

// SENSOR PINS
const int IR_DISTANCE_FRONT = 0; // Analog

// DISTANCE CONVERSIONS
const int TABLE_ENTRIES = 12;
const int FIRST_ELEMENT = 250;
const int INTERVAL = 250;
static int distance[TABLE_ENTRIES] = {150, 140, 130, 100, 60, 50, 40, 35, 30, 25, 20, 15};

// GLOBAL
int speedClock = 0;
// ...

void setup() 
{
  // MOTORS
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(LEFT_ENA, OUTPUT);
  pinMode(RIGHT_ENB, OUTPUT);
  pinMode(RIGHT_IN3, OUTPUT);
  pinMode(RIGHT_IN4, OUTPUT);
  
  // SENSORS
  // ...
  
  // DEBUG
  Serial.begin(9600);
}

/** Put both motors in forward direction */
void setMoveForward()
{
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  
  digitalWrite(RIGHT_IN3, HIGH);
  digitalWrite(RIGHT_IN4, LOW);
}

void setMoveBackward()
{
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);
  
  digitalWrite(RIGHT_IN3, LOW);
  digitalWrite(RIGHT_IN4, HIGH);
}

void setTurnLeft()
{
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);
  
  digitalWrite(RIGHT_IN3, HIGH);
  digitalWrite(RIGHT_IN4, LOW);
}

void setTurnRight()
{
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  
  digitalWrite(RIGHT_IN3, LOW);
  digitalWrite(RIGHT_IN4, HIGH);
}

/** Run into direction */
void run(int speedValue)
{
  analogWrite(LEFT_ENA, speedValue);
  analogWrite(RIGHT_ENB, speedValue);
}

void halt()
{
  analogWrite(LEFT_ENA, 0);
  analogWrite(RIGHT_ENB, 0);  
}

/** Find a way around a barrier. */
void dodge()
{
  int distance = 1000; // milliseconds meanwhile no distance measuring exists ...
  
  setMoveBackward();
  run(125);
  delay(distance);
  setTurnLeft();
  run(125);
  delay(distance*4);
}  

float getDistanceFront()
{
  int sum = 0;
  int sensorVoltage = 0;
  for (int i = 0; i<20; i++)
  {
    sensorVoltage = analogRead(IR_DISTANCE_FRONT);
    sum = sum + sensorVoltage;
  }
  sensorVoltage = sum / 20;
  return sensorVoltage;
  
  // Distance table does not work, create new for that sensor...
  //sensorVoltage = sensorVoltage * 3.3 / 1024;
  //return calculateDistance(sensorVoltage);
}

int calculateDistance(int mV)
{
  if (mV > INTERVAL * TABLE_ENTRIES - 1)
    return distance[TABLE_ENTRIES - 1];
  else
  {
    int index = mV / INTERVAL;
    float frac = (mV % 250) / (float) INTERVAL;
    return distance[index] - ((distance[index] - distance[index + 1]) * frac);
  }
}  

void selfTest()
{
  setMoveForward();
  run(128);
  delay(1000);
  setMoveBackward();
  run(128);
  delay(1000);
  setTurnLeft();
  run(128);
  delay(1000);
  setTurnRight();
  run(128);
  delay(1000);
}

void loop()
{
  //selfTest();
  
  setMoveForward();
  
  float distanceFront = getDistanceFront();
  Serial.print("DIST ");
  Serial.println(distanceFront);
  
  if (distanceFront <= 200) speedClock = 255;  // Full speed
  if (distanceFront > 200) speedClock = 128; // Half speed
  if (distanceFront > 500) speedClock = 0;

  Serial.print("SPEED ");
  Serial.println(speedClock);

  run(speedClock);
  
  if (distanceFront > 500) dodge();
  
  delay(250); // ms
}
