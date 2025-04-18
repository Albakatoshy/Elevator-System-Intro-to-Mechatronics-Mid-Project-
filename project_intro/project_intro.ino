#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int BUTTON_1 = 2;
const int BUTTON_2 = 3;
const int BUTTON_3 = 4;
const int IR_SENSOR = 5;
const int BUZZER = 6;
const int DC_IN1 = 10;
const int DC_IN2 = 12;
const int DC_ENA = 11;
int dc_motor_speed = 125;

const int servo = 13;

int currentFloor = 1;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;
bool doorOpen = false;

Servo doorServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 7-segment display setup (for common anode)
const int segmentPins[7] = {A0, A1, A2, 7, 8, 9, 10};
const byte digits[10][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}  // 9
};

void setup() {
  lcd.init();
  lcd.backlight();
  doorServo.attach(servo);
  closeDoor();
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(IR_SENSOR, INPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(DC_ENA, OUTPUT);
  pinMode(DC_IN1, OUTPUT);
  pinMode(DC_IN2, OUTPUT);

  analogWrite(DC_ENA, dc_motor_speed);
  displayFloor(currentFloor);
}

void loop() {
  int IR_detect = digitalRead(IR_SENSOR);

  if (IR_detect == LOW) {
    if (!doorOpen) {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Welcome");
      openDoor();
      delay(1000);
    }

    if (millis() - lastDebounceTime > debounceDelay) {
      if (digitalRead(BUTTON_1) == LOW ) {
        shobep();
        moveToFloor(1);
      }
      else if (digitalRead(BUTTON_2) == LOW ) {
        shobep();
        moveToFloor(2);
      }
      else if (digitalRead(BUTTON_3) == LOW ) {
        shobep();
        moveToFloor(3);
      }
      lastDebounceTime = millis();
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Elevator is ");
    lcd.setCursor(0, 1);
    lcd.print("Closed");

    closeDoor();
  }
}

void moveToFloor(int targetFloor) {
  int floorsToMove = targetFloor - currentFloor;

  if (floorsToMove == 0) return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moving to Floor");

  delay(500);

  if (floorsToMove > 0){
    MoveUp();
  } 
  else {
    MoveDown();
  }

  delay(abs(floorsToMove) * 2000); // Simulate moving

  Stop();
  currentFloor = targetFloor;

  displayFloor(currentFloor);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arrived at Floor");
  buzz(200);

  openDoor();
  delay(1000);
  closeDoor();
}

void displayFloor(int num) {
  if (num >= 0 && num <= 9) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], digits[num][i] == 0 ? LOW : HIGH); // LOW = ON (common anode)
    }
  }
}

void openDoor() {
  doorServo.write(90);
  doorOpen = true;
  buzz(300);
}

void closeDoor() {
  doorServo.write(0);
  doorOpen = false;
}

void MoveUp() {
  digitalWrite(DC_IN1, LOW);
  digitalWrite(DC_IN2, HIGH);
  analogWrite(DC_ENA, dc_motor_speed);
}

void MoveDown() {
  digitalWrite(DC_IN1, HIGH);
  digitalWrite(DC_IN2, LOW);
  analogWrite(DC_ENA, dc_motor_speed);
}

void Stop() {
  analogWrite(DC_ENA, 0);
  digitalWrite(DC_IN1, LOW);
  digitalWrite(DC_IN2, LOW);
}
void buzz(int duration) {
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
}
void shobep() {
  digitalWrite(BUZZER, HIGH);
  delay(100);  // Short 'teet'
  digitalWrite(BUZZER, LOW);
}
