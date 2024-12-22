#include <BluetoothSerial.h>
#include <ESP32Servo.h>

// Create Bluetooth and Servo objects
BluetoothSerial SerialBT;
Servo finger1Servo, finger2Servo, finger3Servo, finger4Servo, finger5Servo;

// Servo pin assignments
const int finger1 = 25;
const int finger2 = 33;
const int finger3 = 32;
const int finger4 = 26;
const int finger5 = 27;

// Sensor pin
const int sensorOn = 12;
const int sensorOff = 13;

// Initial positions for all fingers
int finger1Position = 0;
int finger2Position = 0;
int finger3Position = 0;
int finger4Position = 0;
int finger5Position = 0;

void setup() {
  Serial.begin(115200); // Start Serial Monitor
  SerialBT.begin("ESP32_Voice"); // Bluetooth device name
  Serial.println("Bluetooth Started! Waiting for commands...");

// Attach servos to respective pins
  finger1Servo.attach(finger1);
  finger2Servo.attach(finger2);
  finger3Servo.attach(finger3);
  finger4Servo.attach(finger4);
  finger5Servo.attach(finger5);

  // Set initial positions
  setAllFingers(0);

  // Configure sensor pin as input
  pinMode(sensorOn, INPUT);
  pinMode(sensorOff, INPUT);
}

void loop() {
  // Check sensor input
  if (digitalRead(sensorOn) == HIGH) {
    setAllFingers(180);
  } else if (digitalRead(sensorOff) == HIGH){
    setAllFingers(0);
  }

  // Check if Bluetooth has received data
  if (SerialBT.available()) {
    String command = SerialBT.readString(); // Read incoming string
    command.trim(); // Remove any extra spaces or newlines

    Serial.println("Command received: " + command);

    // Handle commands
    if (command.equalsIgnoreCase("One")) {
      setFingers(180, 0, 0, 0, 0);
    } else if (command.equalsIgnoreCase("Two")) {
      setFingers(180, 180, 0, 0, 0);
    } else if (command.equalsIgnoreCase("Three")) {
      setFingers(180, 180, 180, 0, 0);
    } else if (command.equalsIgnoreCase("Four")) {
      setFingers(180, 180, 180, 180, 0);
    } else if (command.equalsIgnoreCase("Five")) {
      setFingers(180, 180, 180, 180, 180);
    } else if (command.equalsIgnoreCase("Zero")) {
      setAllFingers(0);
    } else {
      Serial.println("Unknown command");
    }
  }
}

// Function to set all fingers to the same position
void setAllFingers(int position) {
  finger1Servo.write(position);
  finger2Servo.write(position);
  finger3Servo.write(position);
  finger4Servo.write(position);
  finger5Servo.write(position);
  Serial.println("All fingers set to: " + String(position) + " degrees");
}

// Function to set individual finger positions
void setFingers(int pos1, int pos2, int pos3, int pos4, int pos5) {
  finger1Servo.write(pos1);
  finger2Servo.write(pos2);
  finger3Servo.write(pos3);
  finger4Servo.write(pos4);
  finger5Servo.write(pos5);
  Serial.println("Finger positions set to: " + String(pos1) + ", " + String(pos2) + ", " + String(pos3) + ", " + String(pos4) + ", " + String(pos5));
}
