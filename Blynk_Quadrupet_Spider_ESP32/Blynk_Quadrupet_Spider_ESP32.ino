#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

char ssid[] = "   ";
char pass[] = "   ";

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 150
#define SERVOMAX 600
#define SERVO_FREQ 50

// Sudut Menyesuaikan, setiap robot berbeda-beda
// Urutan Array Kaki: [0]=RF, [1]=LF, [2]=RR, [3]=LR
const int COXA_PINS[4]  = {4, 0, 12, 8};
const int FEMUR_PINS[4] = {5, 1, 13, 9};
const int TIBIA_PINS[4] = {6, 2, 14, 10};

// Posisi Melambai
const int MELAMBAI_COXA[4]  = {150,  0, 63,  0};
const int MELAMBAI_FEMUR[4] = {30, 35, 100, 30};

// Posisi Berdiri 
const int BERDIRI_COXA[4]  = {70,  0, 63,  0};
const int BERDIRI_FEMUR[4] = {110, 35, 100, 30};
const int BERDIRI_TIBIA[4] = {145, 70, 85, 125};

// Posisi Menurun
const int MENURUN_COXA[4]  = {10, 60, 0, 60};
const int MENURUN_FEMUR[4] = {50, 100, 30, 90};
const int MENURUN_TIBIA[4] = {145, 70, 85, 125};

// Posisi Tiduran
const int TIDURAN_COXA[4]  = {70, 0, 63, 0};
const int TIDURAN_FEMUR[4] = {50, 100, 30, 90};
const int TIDURAN_TIBIA[4] = {175, 40, 55, 145};

// Posisi Miring Kanan
const int MIRING_KANAN_COXA[4]  = {10, 0, 0, 0};
const int MIRING_KANAN_FEMUR[4] = {50, 35, 30, 30};
const int MIRING_KANAN_TIBIA[4] = {145, 70, 85, 125};

// Posisi Miring Kiri
const int MIRING_KIRI_COXA[4]  = {70, 65, 63, 65};
const int MIRING_KIRI_FEMUR[4] = {110, 100, 100, 90};
const int MIRING_KIRI_TIBIA[4] = {145, 70, 85, 125};

// Posisi Miring Depan
const int MIRING_DEPAN_COXA[4]  = {10, 65, 63, 0};
const int MIRING_DEPAN_FEMUR[4] = {50, 100, 100, 30};
const int MIRING_DEPAN_TIBIA[4] = {145, 70, 85, 125};

// Posisi Miring Belakang
const int MIRING_BELAKANG_COXA[4]  = {70, 0, 0, 65};
const int MIRING_BELAKANG_FEMUR[4] = {110, 35, 30, 90};
const int MIRING_BELAKANG_TIBIA[4] = {145, 70, 85, 125};

// Posisi Siaga
const int SIAGA_COXA[4] = {70, 0, 5, 50};
const int SIAGA_FEMUR[4] = {130, 25, 20, 95};
const int SIAGA_TIBIA[4] = {120, 90, 55, 145};

// Posisi Nungging 
const int NUNGGING_COXA[4] = {70, 0, 63, 0};
const int NUNGGING_FEMUR[4] = {60, 75, 105, 20};
const int NUNGGING_TIBIA[4] = {175, 40, 65, 145};

const int STEP_FORWARD = 18;
const int STEP_BACK    = 12;
const int STEP_LIFT    = 25;
const int TURN_ANGLE = 30;

// Koordinat servo real-time untuk tracking posisi terakhir
int cCoxa[4], cFemur[4], cTibia[4];

// State flags kontrol logika robot
bool isBerdiri = true;   
bool isStandby = false;  
bool isTiduran = false;
bool isSiaga = false;
bool isNungging = false;
bool isMiringKanan = false;
bool isMiringKiri = false;

// State flags untuk deteksi tombol ditahan
bool statusMaju = false;
bool statusMundur = false;
bool statusKiri = false;
bool statusKanan = false;
bool statusMelambai = false;
bool statusDance = false;

void move(int channel, int angle) {
  angle = constrain(angle, 0, 180); 
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(channel, 0, pulse);
}

void transisiSemua(const int tCoxa[], const int tFemur[], const int tTibia[], int steps, int delayTime) {
  for (int i = 0; i < steps; i++) {
    for (int j = 0; j < 4; j++) {
      cCoxa[j]  = cCoxa[j]  + (tCoxa[j] - cCoxa[j]) / (steps - i);
      cFemur[j] = cFemur[j] + (tFemur[j] - cFemur[j]) / (steps - i);
      cTibia[j] = cTibia[j] + (tTibia[j] - cTibia[j]) / (steps - i);
      
      move(COXA_PINS[j], cCoxa[j]);
      move(FEMUR_PINS[j], cFemur[j]);
      move(TIBIA_PINS[j], cTibia[j]);
    }
    delay(delayTime);
  }
}

void siaga() {
  transisiSemua(SIAGA_COXA, SIAGA_FEMUR, SIAGA_TIBIA, 25, 20);
}

void nungging() {
  transisiSemua(NUNGGING_COXA, NUNGGING_FEMUR, NUNGGING_TIBIA, 25, 20);
}
void tiduran() {
  transisiSemua(TIDURAN_COXA, TIDURAN_FEMUR, TIDURAN_TIBIA, 25, 20);
}

void miringKanan() {
  transisiSemua(MIRING_KANAN_COXA, MIRING_KANAN_FEMUR, MIRING_KANAN_TIBIA, 15, 20);
}
void miringKiri() {
  transisiSemua(MIRING_KIRI_COXA, MIRING_KIRI_FEMUR, MIRING_KIRI_TIBIA, 15, 20);
}

void miringDepan() {
  transisiSemua( MIRING_DEPAN_COXA, MIRING_DEPAN_FEMUR, MIRING_DEPAN_TIBIA, 15, 20);
}

void miringBelakang() {
  transisiSemua( MIRING_BELAKANG_COXA, MIRING_BELAKANG_FEMUR, MIRING_BELAKANG_TIBIA, 15, 20);
}

void berdiri() {
  transisiSemua( BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA, 25, 30);
}

void menurun() {
  transisiSemua(MENURUN_COXA, MENURUN_FEMUR, MENURUN_TIBIA, 25, 30);
}

void melambai() {
  int tarTibia[4];
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  transisiSemua(MELAMBAI_COXA, MELAMBAI_FEMUR, tarTibia, 15, 20);

  for (int i = 0; i < 2; i++) {

    tarTibia[0] -= 30;
    transisiSemua(MELAMBAI_COXA, MELAMBAI_FEMUR, tarTibia, 15, 20);

    tarTibia[0] += 60;
    transisiSemua(MELAMBAI_COXA, MELAMBAI_FEMUR, tarTibia, 15, 20);

    tarTibia[0] -= 30;
    transisiSemua(MELAMBAI_COXA, MELAMBAI_FEMUR, tarTibia, 15, 20);
  }
}

void berjalanMaju() {
  int tarCoxa[4], tarFemur[4], tarTibia[4];

  // FASE 1 RF + LR ANGKAT
  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  // RF
  tarFemur[0] -= STEP_LIFT;

  // LR
  tarFemur[3] += STEP_LIFT;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // FASE 2
  // RF + LR MAJU - LF + RR DORONG

  // RF maju
  tarCoxa[0] += STEP_FORWARD;

  // LR maju
  tarCoxa[3] += STEP_FORWARD;

  // LF dorong
  tarCoxa[1] += STEP_BACK;

  // RR dorong
  tarCoxa[2] += STEP_BACK;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // FASE 3 RF + LR TURUN
  tarFemur[0] = BERDIRI_FEMUR[0];
  tarFemur[3] = BERDIRI_FEMUR[3];

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // FASE 5 LF + RR ANGKAT
  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  // LF
  tarFemur[1] += STEP_LIFT;
  // RR
  tarFemur[2] -= STEP_LIFT;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // FASE 6
  // LF + RR MAJU - RF + LR DORONG
  tarCoxa[1] -= STEP_FORWARD;
  tarCoxa[2] -= STEP_FORWARD;
  tarCoxa[0] += STEP_BACK;
  tarCoxa[3] -= STEP_BACK;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 10, 10);

  // FASE 7 LF + RR TURUN
  tarFemur[1] = BERDIRI_FEMUR[1];
  tarFemur[2] = BERDIRI_FEMUR[2];

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // FASE 8 HOME
  transisiSemua( BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA, 10, 10);
}

void berjalanMundur() {
  int tarCoxa[4], tarFemur[4], tarTibia[4];

  // FASE 1 RF + LR ANGKAT
  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  tarFemur[0] -= STEP_LIFT; // RF
  tarFemur[3] += STEP_LIFT; // LR

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // RF + LR MUNDUR
  tarCoxa[0] += STEP_FORWARD;
  tarCoxa[3] -= STEP_FORWARD;

  // LF + RR DORONG KE DEPAN
  tarCoxa[1] -= STEP_BACK;
  tarCoxa[2] -= STEP_BACK;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // TURUNKAN RF + LR
  tarFemur[0] = BERDIRI_FEMUR[0];
  tarFemur[3] = BERDIRI_FEMUR[3];

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // FASE 2 LF + RR ANGKAT
  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  tarFemur[1] += STEP_LIFT; // LF
  tarFemur[2] -= STEP_LIFT; // RR

  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // LF + RR MUNDUR
  tarCoxa[1] += STEP_FORWARD;
  tarCoxa[2] += STEP_FORWARD;

  // RF + LR DORONG KE DEPAN
  tarCoxa[0] += STEP_BACK;
  tarCoxa[3] += STEP_BACK;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 10, 10);

  // TURUNKAN LF + RR
  tarFemur[1] = BERDIRI_FEMUR[1];
  tarFemur[2] = BERDIRI_FEMUR[2];
  transisiSemua(tarCoxa, tarFemur, tarTibia, 9, 10);

  // HOME
  transisiSemua(BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA, 10, 10);
}

void belokKiri() {
  int tarCoxa[4], tarFemur[4], tarTibia[4];

  // ==================================
  // FASE 1 : RF + LR ANGKAT
  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  tarFemur[0] -= STEP_LIFT; // RF
  tarFemur[3] += STEP_LIFT; // LR

  // arahkan kaki ke kanan
  tarTibia[0] += TURN_ANGLE;
  tarTibia[3] += TURN_ANGLE;
  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 2 : GERAK PUTAR

  // RF mundur
  tarCoxa[0] -= STEP_FORWARD;
  // LR maju
  tarCoxa[3] -= STEP_FORWARD;
  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 3 : TURUNKAN
  tarFemur[0] = BERDIRI_FEMUR[0];
  tarFemur[3] = BERDIRI_FEMUR[3];

  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 4 : LF + RR ANGKAT
  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  tarFemur[1] += STEP_LIFT; // LF
  tarFemur[2] -= STEP_LIFT; // RR

  // arahkan kaki ke kanan
  tarTibia[1] += TURN_ANGLE;
  tarTibia[2] += TURN_ANGLE;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 5 : GERAK PUTAR

  // LF maju
  tarCoxa[1] -= STEP_FORWARD;
  // RR mundur
  tarCoxa[2] += STEP_FORWARD;
  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 6 : TURUNKAN
  tarFemur[1] = BERDIRI_FEMUR[1];
  tarFemur[2] = BERDIRI_FEMUR[2];

  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 7 : KEMBALI NORMAL
  transisiSemua( BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA, 10, 10);
}
void belokKanan() {
  int tarCoxa[4], tarFemur[4],tarTibia[4];
  // FASE 1 : RF + LR ANGKAT

  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  tarFemur[0] -= STEP_LIFT; // RF
  tarFemur[3] += STEP_LIFT; // LR

  // arahkan kaki ke kiri
  tarTibia[0] -= TURN_ANGLE;
  tarTibia[3] -= TURN_ANGLE;

  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 2 : GERAK PUTAR

  // RF maju
  tarCoxa[0] += STEP_FORWARD;
  // LR mundur
  tarCoxa[3] += STEP_FORWARD;
  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 3 : TURUNKAN
  tarFemur[0] = BERDIRI_FEMUR[0];
  tarFemur[3] = BERDIRI_FEMUR[3];

  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 4 : LF + RR ANGKAT
  memcpy(tarCoxa,  BERDIRI_COXA,  sizeof(BERDIRI_COXA));
  memcpy(tarFemur, BERDIRI_FEMUR, sizeof(BERDIRI_FEMUR));
  memcpy(tarTibia, BERDIRI_TIBIA, sizeof(BERDIRI_TIBIA));

  tarFemur[1] += STEP_LIFT; // LF
  tarFemur[2] -= STEP_LIFT; // RR

  // arahkan kaki ke kiri
  tarTibia[1] -= TURN_ANGLE;
  tarTibia[2] -= TURN_ANGLE;
  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 5 : GERAK PUTAR

  // LF mundur
  tarCoxa[1] += STEP_FORWARD;
  // RR maju
  tarCoxa[2] -= STEP_FORWARD;
  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 6 : TURUNKAN
  tarFemur[1] = BERDIRI_FEMUR[1];
  tarFemur[2] = BERDIRI_FEMUR[2];
  transisiSemua(tarCoxa, tarFemur, tarTibia, 8, 10);

  // FASE 7 : KEMBALI NORMAL
  transisiSemua(BERDIRI_COXA,BERDIRI_FEMUR,BERDIRI_TIBIA,10,10);
}

void dance() {
  miringKiri(); 
  delay(200);
  transisiSemua( BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA, 10, 15);

  miringKanan(); 
  delay(200);
  transisiSemua(BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA, 10, 15);

  miringDepan(); 
  delay(200);
  transisiSemua( BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA, 10,15);

  miringBelakang(); 
  delay(200);
  transisiSemua( BERDIRI_COXA, BERDIRI_FEMUR, BERDIRI_TIBIA,10,15);
}

// === KONTROL BLYNK ===

// V1: Switch Berdiri (1) / Menurun (0)
BLYNK_WRITE(V1) {
  if (isStandby) return; 

  int posisiSwitch = param.asInt();
  if (posisiSwitch == 1) {
    Serial.println("Perintah: BERDIRI");
    berdiri();
    isBerdiri = true;
    isSiaga = false;
    isNungging = false;
    isMiringKiri = false;
    isMiringKanan = false;
  } else{
    Serial.println("Perintah: MENURUN");
    menurun();
    isBerdiri = false;
    isSiaga   = false;
    isNungging   = false;
    isMiringKiri = false;
    isMiringKanan = false;
  }
}

// V2: Button Maju (Push Mode)
BLYNK_WRITE(V2) {
  int tekan = param.asInt();
  if (tekan == 1) {
    statusMaju = true;  // Tombol mulai ditekan
  } else {
    statusMaju = false; // Tombol dilepas
  }
}

// V3: Button Belok Kiri (Push Mode)
BLYNK_WRITE(V3) {
  int tekan = param.asInt();
  if (tekan == 1) {
    statusKiri = true;  // Tombol mulai ditekan
  } else {
    statusKiri = false; // Tombol dilepas
  }
}

// V4: Switch Standby Lock
BLYNK_WRITE(V4) {
  int statusKunci = param.asInt();
  if (statusKunci == 1) {
    isStandby = true;
    statusMaju = false;      
    statusMundur = false;   // Matikan semua pergerakan aktif saat dikunci
    statusKiri = false;
    statusKanan = false;
    statusMelambai = false;
    isSiaga = false;
    isNungging = false;
    isMiringKanan = false;
    isMiringKiri = false;

    Serial.println("SISTEM STANDBY: Posisi terkunci.");
  } else {
    isStandby = false;
    Serial.println("SISTEM AKTIF: Kunci dibuka.");
  }
}
// V5: Button Mundur (Push Mode)
BLYNK_WRITE(V5) {
  int tekan = param.asInt();
  if (tekan == 1) {
    statusMundur = true;  // Tombol mulai ditekan
  } else {
    statusMundur = false; // Tombol dilepas
  }
}
// V3: Button Putar Kanan (Push Mode)
BLYNK_WRITE(V6) {
  int tekan = param.asInt();
  if (tekan == 1) {
    statusKanan = true;  // Tombol mulai ditekan
  } else {
    statusKanan = false; // Tombol dilepas
  }
}
BLYNK_WRITE(V7) {
  int posisiSwitch = param.asInt();

  if (posisiSwitch == 1) {
    Serial.println("Perintah: DUDUK");
    siaga();
    isBerdiri = false;
    isSiaga = true;
    isNungging = false;
    isMiringKiri = false;
    isMiringKanan = false;
  } else {
    Serial.println("Perintah: BERDIRI");
    berdiri();
    isBerdiri = true;
    isSiaga = false;
    isNungging = false;
    isMiringKiri = false;
    isMiringKanan = false;
  }
}

BLYNK_WRITE(V8) {
  int posisiSwitch = param.asInt();
  if (posisiSwitch == 1) {
    Serial.println("Perintah: Sujud");
    nungging();
    isBerdiri = false;
    isSiaga = false;
    isNungging = true;
    isMiringKiri = false;
    isMiringKanan = false;
  } else {
    Serial.println("Perintah: BERDIRI");
    berdiri();
    isBerdiri = true;
    isSiaga = false;
    isNungging = false;
    isMiringKiri = false;
    isMiringKanan = false;
  }
}

BLYNK_WRITE(V9) {
  int posisiSwitch = param.asInt();
  if (posisiSwitch == 1) {
    Serial.println("Perintah: Miring KIRI");
    miringKiri();
  } else {
    Serial.println("Perintah: BERDIRI");
    berdiri();
    isBerdiri = false;
    isSiaga = false;
    isNungging = false;
    isMiringKiri = true;
    isMiringKanan = false;
  }
}
BLYNK_WRITE(V10) {
  int posisiSwitch = param.asInt();
  if (posisiSwitch == 1) {
    Serial.println("Perintah: Miring Kanan");
    miringKanan();
  } else {
    Serial.println("Perintah: BERDIRI");
    berdiri();
    isBerdiri = true;
    isSiaga = false;
    isNungging = false;
    isMiringKiri = false;
    isMiringKanan = false;
  }
}
BLYNK_WRITE(V11) {
  int tekan = param.asInt();

  if (tekan == 1) {
    statusDance = true;
    Serial.println("Dance Mode ON");
  } else {
    statusDance = false;
    Serial.println("Dance Mode OFF");
    berdiri();

  }
}
BLYNK_WRITE(V12) {
  int posisiSwitch = param.asInt();
  if (posisiSwitch == 1) {
    Serial.println("Perintah: Miring Kanan");
    tiduran();
  } else {
    Serial.println("Perintah: BERDIRI");
    berdiri();
    isBerdiri = true;
    isSiaga = false;
    isNungging = false;
    isMiringKiri = false;
    isMiringKanan = false;
  }
}

BLYNK_WRITE(V13)
{
  statusMelambai = param.asInt();
  if (!statusMelambai) {
    berdiri();
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(18, 23);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(1000);

  for (int i = 0; i < 4; i++) {
    cCoxa[i]  = BERDIRI_COXA[i];
    cFemur[i] = BERDIRI_FEMUR[i];
    cTibia[i] = BERDIRI_TIBIA[i];
    
    move(COXA_PINS[i], cCoxa[i]);
    move(FEMUR_PINS[i], cFemur[i]);
    move(TIBIA_PINS[i], cTibia[i]);
  }
  delay(1000);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // Eksekusi pergerakan berulang selama tombol ditekan & syarat terpenuhi
  if (!isStandby) {
    if (statusDance) {
      dance();
    }
    if (isBerdiri){
      if (statusMelambai) {
        melambai();
      }
      else if (statusMaju) {
        Serial.println("Looping Gerakan: Maju");
        berjalanMaju();
      } 
      else if (statusMundur) {
        Serial.println("Looping Gerakan: Mundur");
        berjalanMundur();
      }
      else if (statusKiri) {
        Serial.println("Looping Gerakan: BELOK Kanan");
        belokKiri();
      }
      else if (statusKanan) {
        Serial.println("Looping Gerakan: BELOK Kanan");
        belokKanan();
      }
    }
  }
}