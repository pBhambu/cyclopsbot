#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

// --- OLED Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int EYE_X = 64;
const int EYE_Y = 32;

// --- ESP32 GPIO Pin Assignments ---
const int PIN_R1 = 13; // Hip Front Right
const int PIN_R2 = 12; // Hip Back Right
const int PIN_L1 = 27; // Hip Front Left
const int PIN_L2 = 14; // Hip Back Left

const int PIN_R3 = 26; // Lift Front Right
const int PIN_R4 = 25; // Lift Back Right
const int PIN_L3 = 33; // Lift Front Left
const int PIN_L4 = 32; // Lift Back Left

// --- Servo Objects ---
Servo servoR1, servoR2, servoL1, servoL2;
Servo servoR3, servoR4, servoL3, servoL4;

// --- Controller Instance ---
XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

// --- Gait Parameters ---
int stepState = 0;
unsigned long lastStepTime = 0;
const int STEP_DELAY = 120; // Step speed (ms)
bool isStanding = true;

// --- OLED Cyclops Eye Renderer ---
void drawCyclopsEye(int pupilOffsetX = 0, int pupilOffsetY = 0) {
  display.clearDisplay();

  // Outer Eye White Area (Sclera)
  display.fillCircle(EYE_X, EYE_Y, 28, SSD1306_WHITE);

  // Eyelid Cutouts
  display.fillRect(EYE_X - 40, EYE_Y - 45, 80, 25, SSD1306_BLACK);
  display.fillRect(EYE_X - 40, EYE_Y + 20, 80, 25, SSD1306_BLACK);

  // Eyelid Outlines
  display.drawFastHLine(EYE_X - 30, EYE_Y - 18, 60, SSD1306_BLACK);
  display.drawFastHLine(EYE_X - 30, EYE_Y + 18, 60, SSD1306_BLACK);

  // Iris Outer Ring
  display.fillCircle(EYE_X + pupilOffsetX, EYE_Y + pupilOffsetY, 16, SSD1306_BLACK);
  display.drawCircle(EYE_X + pupilOffsetX, EYE_Y + pupilOffsetY, 17, SSD1306_WHITE);

  // Pupil Center
  display.fillCircle(EYE_X + pupilOffsetX, EYE_Y + pupilOffsetY, 10, SSD1306_WHITE);
  display.fillCircle(EYE_X + pupilOffsetX, EYE_Y + pupilOffsetY, 8, SSD1306_BLACK);

  // Catchlight Glint
  display.fillRect(EYE_X + pupilOffsetX - 4, EYE_Y + pupilOffsetY - 5, 3, 3, SSD1306_WHITE);

  display.display();
}

// --- Default Stances ---
void standUp() {
  // Hips to Neutral (Side - 90°)
  servoR1.write(90);
  servoR2.write(90);
  servoL1.write(90);
  servoL2.write(90);

  // Lifts facing DOWN
  servoR3.write(180); // R3 Down
  servoR4.write(0);   // R4 Down
  servoL3.write(0);   // L3 Down
  servoL4.write(180); // L4 Down
  
  isStanding = true;
  drawCyclopsEye(0, 0);
}

void layDown() {
  // Lift legs UP flat
  servoR3.write(0);   // R3 Up
  servoR4.write(180); // R4 Up
  servoL3.write(180); // L3 Up
  servoL4.write(0);   // L4 Up

  isStanding = false;
  drawCyclopsEye(0, 4); // Eye looks down when laying down
}

// --- Action & Emote Routines ---
void performWave() {
  // Raise Front Right Lift Leg
  servoR3.write(0); 
  drawCyclopsEye(6, -4);
  delay(200);

  // Wave Front Right Hip back and forth
  for (int i = 0; i < 3; i++) {
    servoR1.write(135);
    delay(150);
    servoR1.write(45);
    delay(150);
  }

  // Return to Stand
  standUp();
}

void performDiagonalDance() { // Button X
  for (int i = 0; i < 2; i++) {
    // Step 1: Front Right (R3) & Back Left (L4) spin UP
    servoR3.write(0);   
    servoL4.write(0);   
    drawCyclopsEye(-6, -4);
    delay(200);

    // Return to Down
    servoR3.write(180); 
    servoL4.write(180); 
    delay(200);

    // Step 2: Front Left (L3) & Back Right (R4) spin UP
    servoL3.write(180); 
    servoR4.write(180); 
    drawCyclopsEye(6, -4);
    delay(200);

    // Return to Down
    servoL3.write(0);   
    servoR4.write(0);   
    delay(200);
  }
  standUp();
}

void performTwistWiggle() { // Button Y
  // Twist hips left and right while keeping lifts grounded
  for (int i = 0; i < 3; i++) {
    // Twist body Left
    servoR1.write(120);
    servoR2.write(120);
    servoL1.write(120);
    servoL2.write(120);
    drawCyclopsEye(-8, 0);
    delay(150);

    // Twist body Right
    servoR1.write(60);
    servoR2.write(60);
    servoL1.write(60);
    servoL2.write(60);
    drawCyclopsEye(8, 0);
    delay(150);
  }
  standUp();
}

void walkForwardStep() {
  switch (stepState) {
    case 0:
      servoR3.write(45);  
      servoL4.write(45);  
      break;
    case 1:
      servoR1.write(135); 
      servoL2.write(45);   
      servoL1.write(135);  
      servoR2.write(45);  
      break;
    case 2:
      servoR3.write(180);  
      servoL4.write(180);  
      break;
    case 3:
      servoR4.write(135); 
      servoL3.write(135); 
      break;
    case 4:
      servoL1.write(45);  
      servoR2.write(135);  
      servoR1.write(45);  
      servoL2.write(135); 
      break;
    case 5:
      servoR4.write(0);  
      servoL3.write(0);  
      break;
  }
  stepState = (stepState + 1) % 6;
}

void setup() {
  Serial.begin(115200);

  // Initialize OLED
  Wire.begin(21, 22);
  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    drawCyclopsEye(0, 0);
  }

  // Attach Servos
  servoR1.attach(PIN_R1, 500, 2400);
  servoR2.attach(PIN_R2, 500, 2400);
  servoL1.attach(PIN_L1, 500, 2400);
  servoL2.attach(PIN_L2, 500, 2400);

  servoR3.attach(PIN_R3, 500, 2400);
  servoR4.attach(PIN_R4, 500, 2400);
  servoL3.attach(PIN_L3, 500, 2400);
  servoL4.attach(PIN_L4, 500, 2400);

  standUp();
  xboxController.begin();
}

void loop() {
  xboxController.onLoop();

  if (xboxController.isConnected()) {
    // Reading Inputs
    uint16_t joyY = xboxController.xboxNotif.joyLVert;
    bool btnA = xboxController.xboxNotif.btnA;
    bool btnB = xboxController.xboxNotif.btnB;
    bool btnX = xboxController.xboxNotif.btnX;
    bool btnY = xboxController.xboxNotif.btnY;

    bool trigRT = xboxController.xboxNotif.trigRT > 100;
    bool trigLT = xboxController.xboxNotif.trigLT > 100;
    bool btnRB  = xboxController.xboxNotif.btnRB;
    bool btnLB  = xboxController.xboxNotif.btnLB;

    // --- Button Actions ---
    if (btnA) {
      if (!isStanding) {
        standUp();
      } else {
        performWave();
      }
      delay(300);
    } 
    else if (btnB) {
      if (isStanding) {
        layDown();
      } else {
        // Rotate legs up and down once if already down
        servoR3.write(180); servoR4.write(0); servoL3.write(0); servoL4.write(180);
        delay(300);
        layDown();
      }
      delay(300);
    } 
    else if (btnX) {
      performDiagonalDance();
      delay(300);
    } 
    else if (btnY) {
      performTwistWiggle();
      delay(300);
    }

    // --- Manual Individual Leg Rotation Triggers ---
    else if (trigRT) { servoR1.write(135); } // Rotate Front Right Hip
    else if (trigLT) { servoL1.write(45);  } // Rotate Front Left Hip
    else if (btnRB)  { servoR2.write(135); } // Rotate Back Right Hip
    else if (btnLB)  { servoL2.write(45);  } // Rotate Back Left Hip

    // --- Walking Gait Control ---
    else if (joyY > 40000) {
      if (millis() - lastStepTime > STEP_DELAY) {
        walkForwardStep();
        drawCyclopsEye(0, -4);
        lastStepTime = millis();
      }
    } 
    else {
      // Auto Reset to Stand Stance when idle
      if (stepState != 0) {
        standUp();
        stepState = 0;
      }
    }
  }

  vTaskDelay(10 / portTICK_PERIOD_MS);
}