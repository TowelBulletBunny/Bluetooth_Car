#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// ===== BLUETOOTH =====
SoftwareSerial BT(2, 13);  // RX = 2, TX = 13

// ===== Motor Pins =====
#define ENA 11
#define ENB 3
#define IN1 A1
#define IN2 A4
#define IN3 A5
#define IN4 12

// ===== LCD =====
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Bluetooth Mode");

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopRobot(); // Ensure motors start stopped
}

void loop() {

  // Read Bluetooth
  if (BT.available()) {
    char cmd = BT.read();
    Serial.print("Received: ");
    Serial.println(cmd);
    handleCommand(cmd);
  }
}

// ===========================================
// ============= COMMAND HANDLER =============
// ===========================================
void handleCommand(char cmd) {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BLUETOOTH MODE");

  switch (cmd) {

    case 'F': {
      forward();
      lcd.setCursor(0, 1);
      lcd.print("Forward");
      break;
    }

    case 'B': {
      backward();
      lcd.setCursor(0, 1);
      lcd.print("Backward");
      break;
    }

    case 'L': {
      turnLeft();
      lcd.setCursor(0, 1);
      lcd.print("Left");
      break;
    }

    case 'R': {
      turnRight();
      lcd.setCursor(0, 1);
      lcd.print("Right");
      break;
    }

    case 'S': {
      stopRobot();
      lcd.setCursor(0, 1);
      lcd.print("Stop");
      break;
    }

    default:
      lcd.setCursor(0, 1);
      lcd.print("Unknown cmd");
      break;
  }
}

// ===========================================
// =============== MOTOR CONTROL =============
// ===========================================
void forward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, 130);
  analogWrite(ENB, 160);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, 160);
  analogWrite(ENB, 130);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopRobot() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
