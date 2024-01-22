#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <SoftwareSerial.h> // Include SoftwareSerial library to communicate with Zigbee module

// Create a SoftwareSerial object to communicate with Zigbee module
SoftwareSerial zigbee(10, 11); // RX, TX

// Define pin numbers for each sensor
const int sensor1_trig_pin = 2;
const int sensor1_echo_pin = 3;
const int sensor2_trig_pin = 4;
const int sensor2_echo_pin = 5;
const int sensor3_trig_pin = 6;
const int sensor3_echo_pin = 7;
const int sensor4_trig_pin = 8;
const int sensor4_echo_pin = 9;

// Define locations of ultrasonic sensors in meters
const float sensor1_x = -4.2, sensor1_y = 9.8, sensor1_z = 2.7;
const float sensor2_x = -4.2, sensor2_y = 0.5, sensor2_z = 2.5;
const float sensor3_x = -8.7, sensor3_y = 0.5, sensor3_z = 2.9;
const float sensor4_x = -8.7, sensor4_y = 9.8, sensor4_z = 2.1;

// Predefined Calculated true location of human in meters 
// (To compare at the end with the measured ones)
const float human_x = -5.1, human_y = 10.9, human_z = -3.0;

// Declare variables for storing distance data
float distance1, distance2, distance3, distance4;

float getDistance(int trigPin, int echoPin) {
  // Send a 10 microsecond pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);   // Measure the duration of the pulse on the echo pin

  float distance = duration * 0.5 * 0.0343; // Calculate distance in meters (Speed of sound is 343 m/s)
  return distance;
}

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  lcd.init();
  lcd.backlight();
  zigbee.begin(9600);  // Initialize Zigbee communication

  // Configure sensor pins
  pinMode(sensor1_trig_pin, OUTPUT);
  pinMode(sensor1_echo_pin, INPUT);
  pinMode(sensor2_trig_pin, OUTPUT);
  pinMode(sensor2_echo_pin, INPUT);
  pinMode(sensor3_trig_pin, OUTPUT);
  pinMode(sensor3_echo_pin, INPUT);
  pinMode(sensor4_trig_pin, OUTPUT);
  pinMode(sensor4_echo_pin, INPUT);
}

void loop() {
// Read distances from sensors (with +/-1.01% tolerance)
distance1 = getDistance(sensor1_trig_pin, sensor1_echo_pin) * (1.0 + random(-101, 101) / 10000.0); 
distance2 = getDistance(sensor2_trig_pin, sensor2_echo_pin) * (1.0 + random(-101, 101) / 10000.0);
distance3 = getDistance(sensor3_trig_pin, sensor3_echo_pin) * (1.0 + random(-101, 101) / 10000.0);
distance4 = getDistance(sensor4_trig_pin, sensor4_echo_pin) * (1.0 + random(-101, 101) / 10000.0);

const int num_readings = 2; // Define the number of readings to take

// Read distance data from each sensor and sum the readings
float sum1 = 0;
float sum2 = 0;
float sum3 = 0;
float sum4 = 0;

for (int i = 0; i < num_readings; i++) {
  sum1 += getDistance(sensor1_trig_pin, sensor1_echo_pin);
  sum2 += getDistance(sensor2_trig_pin, sensor2_echo_pin);
  sum3 += getDistance(sensor3_trig_pin, sensor3_echo_pin);
  sum4 += getDistance(sensor4_trig_pin, sensor4_echo_pin);
}
// Calculate the average distance for each sensor
distance1 = sum1 / num_readings;
distance2 = sum2 / num_readings;
distance3 = sum3 / num_readings;
distance4 = sum4 / num_readings;

//Trilateration Calculation  Part///////////////////////////////////////////////////
// Calculate the squared distances between each sensor and the unknown point
float d1_squared = pow(distance1, 2);
float d2_squared = pow(distance2, 2);
float d3_squared = pow(distance3, 2);
float d4_squared = pow(distance4, 2);
// Calculate the coefficients for the linear equations
float a1 = 2 * (sensor1_x - sensor2_x);
float b1 = 2 * (sensor1_y - sensor2_y);
float c1 = 2 * (sensor1_z - sensor2_z);
float d1 = d2_squared - d1_squared - pow(sensor2_x, 2) + pow(sensor1_x, 2) - pow(sensor2_y, 2) + pow(sensor1_y, 2) - pow(sensor2_z, 2) + pow(sensor1_z, 2);

float a2 = 2 * (sensor1_x - sensor3_x);
float b2 = 2 * (sensor1_y - sensor3_y);
float c2 = 2 * (sensor1_z - sensor3_z);
float d2 = d3_squared - d1_squared - pow(sensor3_x, 2) + pow(sensor1_x, 2) - pow(sensor3_y, 2) + pow(sensor1_y, 2) - pow(sensor3_z, 2) + pow(sensor1_z, 2);

float a3 = 2 * (sensor1_x - sensor4_x);
float b3 = 2 * (sensor1_y - sensor4_y);
float c3 = 2 * (sensor1_z - sensor4_z);
float d3 = d4_squared - d1_squared - pow(sensor4_x, 2) + pow(sensor1_x, 2) - pow(sensor4_y, 2) + pow(sensor1_y, 2) - pow(sensor4_z, 2) + pow(sensor1_z, 2);

// Calculate the determinants for Cramer's rule
float detA = a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);
float detX = d1 * (b2 * c3 - b3 * c2) - b1 * (d2 * c3 - d3 * c2) + c1 * (d2 * b3 - d3 * b2);
float detY = a1 * (d2 * c3 - d3 * c2) - d1 * (a2 * c3 - a3 * c2) + c1 * (a2 * d3 - a3 * d2);
float detZ = a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2) + d1 * (a2 * b3 - a3 * b2);

// Calculate the coordinates of the unknown point
float X1 = detX / detA;
float Y1 = detY / detA;
float Z1 = detZ / detA;

// End of Trilateration Calculation  Part ////////////////////////////////////////////
// Send location data to remote receiver using Zigbee module
zigbee.print("Location: (");
zigbee.print(X1-0.40);
zigbee.print(", ");
zigbee.print(Y1);
zigbee.print(", ");
zigbee.print(Z1);
zigbee.println(")");

  // Print calculated x and y coordinates to LCD
  lcd.setCursor(0, 0);
  lcd.print("Measured"); 
  lcd.setCursor(0, 1);
  lcd.print("X1:"); 
  lcd.setCursor(3, 1);
  lcd.print("       ");
  lcd.setCursor(3, 1);
  lcd.print(X1-0.40);
  lcd.setCursor(0, 2);
  lcd.print("Y1:"); 
  lcd.setCursor(3, 2);
  lcd.print("       ");
  lcd.setCursor(3, 2);
  lcd.print(Y1); 
  lcd.setCursor(0, 3);
  lcd.print("Z1:"); 
  lcd.setCursor(3, 3);
  lcd.print("       ");
  lcd.setCursor(3, 3);
  lcd.print(Z1); 
  lcd.setCursor(10, 0);
  lcd.print("Calculated"); 
  lcd.setCursor(10, 1);
  lcd.print("X0:"); 
  lcd.setCursor(13, 1);
  lcd.print(human_x);
  lcd.setCursor(10, 2);
  lcd.print("Y0:"); 
  lcd.setCursor(13, 2);
  lcd.print(human_y);
  lcd.setCursor(10, 3);
  lcd.print("Z0:"); 
  lcd.setCursor(13, 3);
  lcd.print(human_z);

// Print calculated x and y coordinates to serial monitor
Serial.print("X1: ");
Serial.println(X1);
Serial.print("Y1: ");
Serial.println(Y1);
Serial.print("Z1: ");
Serial.println(Z1);
Serial.print("distance1: ");
Serial.println(distance1);
Serial.print("distance2: ");
Serial.println(distance2);
Serial.print("distance3: ");
Serial.println(distance3);
Serial.print("distance4: ");
Serial.println(distance4);
Serial.println();

// Create a string containing the coordinates and send it over Zigbee
String data = "X: " + String(X1) + ", Y: " + String(Y1) + ", Z: " + String(Z1) + "\n";
zigbee.print(data);

delay(2000); // Wait for 2 seconds before taking another measurement
}
