# Coordinated 12-DOF Quadruped Robot with Blynk IoT Interface

A professional-grade quadruped (4-legged) robot platform utilizing a **12 Degree of Freedom (DOF)** mechanical configuration. Designed with an embedded system that distributes computational load, the robot features a Wi-Fi-enabled microcontroller (**ESP32** or **ESP8266**) for logical coordination and IoT communications, and an **Adafruit PCA9685** 16-channel 12-bit PWM driver for precise multi-servo actuation.

The robot is controlled in real-time via the **Blynk IoT** mobile application, executing both static posturing and dynamic locomotion (diagonal gait) through an open-loop, time-synchronized control architecture.

---

## 🎥 Robot Demonstration

Below is a comprehensive video demonstration of the 12-DOF Quadruped Robot executing various postures, gait transitions, and active movement routines, managed in real-time using the Blynk IoT mobile dashboard:

https://github.com/user-attachments/assets/33c1f037-f79a-4495-9738-f3045d3acb1c

---

## 📸 Pose & Maneuver Showcase

Below are the operational poses and mechanical configurations executed by the robot, displaying its structural integrity and kinematic capabilities:

|        🦾 Stand Pose (Normal)        |            🧍 Crouch Pose            |          🚨 Alert (Ready) Pose          |              💤 Sleep / Rest Pose               |
| :----------------------------------: | :----------------------------------: | :-------------------------------------: | :---------------------------------------------: |
| ![Stand Pose](Pose/Berdiri-Pose.jpg) |  ![Erect Pose](Pose/Crouch-Pose.jpg)  |   ![Alert Pose](Pose/Siaga-Pose.jpg)    |      ![Sleep Pose](Pose/Tiduran-Pose.jpg)       |
|    **V1 (HIGH)**: Default stance.    | **V1 (LOW)**: Lowered/crouch stance. | **V7 (HIGH)**: Prepared for locomotion. | **V12 (HIGH)**: Low-power state, joints folded. |

|         🙇 Bow / Nudge Pose          |            👈 Lean Left Pose            |            👉 Lean Right Pose             |
| :----------------------------------: | :-------------------------------------: | :---------------------------------------: |
| ![Bow Pose](Pose/Nungging-Pose.jpg)  | ![Lean Left](Pose/Miring-Kiri-Pose.jpg) | ![Lean Right](Pose/Miring-Kanan-Pose.jpg) |
| **V8 (HIGH)**: Low front, high rear. |   **V9 (HIGH)**: Roll movement left.    |   **V10 (HIGH)**: Roll movement right.    |

<details>
<summary><b>🎥 Click to view Pose Demonstration Videos</b></summary>

- **Stand Pose (Normal)**:
  https://github.com/user-attachments/assets/1d478605-c089-45de-a125-60b619f2e742

- **Crouch Pose**:
  https://github.com/user-attachments/assets/4c5a3081-5370-4404-9bbb-77898118aac1

- **Alert (Ready) Pose**:
  https://github.com/user-attachments/assets/3a335829-2f5d-4544-bacd-e058f1fe2eb6

- **Sleep / Rest Pose**:
  https://github.com/user-attachments/assets/f11d5c61-f698-4b54-aeb1-436f1fbffb85

- **Bow / Nudge Pose**:
  https://github.com/user-attachments/assets/862aab0b-3d93-4b0e-8ee4-31507dded152

- **Lean Left Pose**:
  https://github.com/user-attachments/assets/0bff008e-99b4-4d29-90c5-f23f27e07ff3

- **Lean Right Pose**:
  https://github.com/user-attachments/assets/ac0b15eb-119f-4572-bb21-902510a6424b

</details>

---

## 🚶 Locomotion & Dynamic Movement Guide

This section outlines the locomotion patterns and sequential execution phases of the quadruped robot. The robot utilizes a coordinated **Diagonal/Trot Gait** for linear movement and synchronized hip-turning actions for angular rotation.

### 1. Forward Locomotion (Maju)

The forward gait is executed as a synchronized diagonal gait, where diagonal pairs of legs lift and swing forward together while the other pair supports the body and pushes it backward relative to the chassis, resulting in forward momentum.

- **Demonstration Video**:

https://github.com/user-attachments/assets/fc50f5f5-f1f2-4a9b-8522-8e45da42de9c

- **Gait Phase Progression**:
  | 1️⃣ Phase 1: RF & LR Lift & Swing | 2️⃣ Phase 2: LF & RR Lift & Swing |
  | :---: | :---: |
  | ![Forward Phase 1](Movement/Maju_1.jpg) | ![Forward Phase 2](Movement/Maju_2.jpg) |
  | Diagonal Right-Front (RF) and Left-Rear (LR) legs swing forward. | Diagonal Left-Front (LF) and Right-Rear (RR) legs swing forward. |

---

### 2. Backward Locomotion (Mundur)

Similar to forward walking, the backward gait alternates diagonal leg pairs but reverses the direction of the coxa sweep angles to push the chassis backward.

- **Demonstration Video**:

https://github.com/user-attachments/assets/22a0bcbb-a019-4d9a-b82d-9472006d92e3

- **Gait Phase Progression**:
  | 1️⃣ Phase 1: RF & LR Lift & Sweep Back | 2️⃣ Phase 2: LF & RR Lift & Sweep Back |
  | :---: | :---: |
  | ![Backward Phase 1](Movement/mundur_1.jpg) | ![Backward Phase 2](Movement/mundur_2.jpg) |
  | Diagonal Right-Front (RF) and Left-Rear (LR) legs lift and sweep backward. | Diagonal Left-Front (LF) and Right-Rear (RR) legs lift and sweep backward. |

---

### 3. Left Turn Maneuver (Belok Kiri)

To turn left, the robot adjusts the yaw angle using its Coxa joints. The diagonal legs lift and sweep outwards/inwards asymmetrically to generate a counter-clockwise torque.

- **Demonstration Video**:

https://github.com/user-attachments/assets/7c172126-97d5-41d0-a2b9-98a21dbfacc1

- **Step Phase Progression**:
  | 1️⃣ Phase 1: Swing Left Alignment | 2️⃣ Phase 2: Pivot & Ground Sweep |
  | :---: | :---: |
  | ![Turn Left Phase 1](Movement/belok_kiri_1.jpg) | ![Turn Left Phase 2](Movement/belok_kiri_2.jpg) |
  | First diagonal pair lifts and pivots outwards towards the left. | Second diagonal pair lifts, matching orientation to complete the pivot. |

---

### 4. Right Turn Maneuver (Belok Kanan)

The right turn reverses the pivot dynamics of the left turn, generating clockwise yaw torque.

- **Demonstration Video**:

https://github.com/user-attachments/assets/160b379b-c33b-44f2-9617-6cf2e1d9ef62

- **Step Phase Progression**:
  | 1️⃣ Phase 1: Swing Right Alignment | 2️⃣ Phase 2: Pivot & Ground Sweep |
  | :---: | :---: |
  | ![Turn Right Phase 1](Movement/belok_kanan_1.jpg) | ![Turn Right Phase 2](Movement/belok_kanan_2.jpg) |
  | First diagonal pair lifts and pivots outwards towards the right. | Second diagonal pair lifts, matching orientation to complete the pivot. |

---

### 5. Coordinated Dance Routine (Dance Mode)

The dance routine showcases the robot's ability to smoothly shift its center of mass across all axes (Roll and Pitch) sequentially.

- **Demonstration Video**:

https://github.com/user-attachments/assets/8030e06d-8e2b-4a14-a35c-40132f868c27

- **Chassis Orientation Stages**:
  | 1️⃣ Step 1: Tilt Left | 2️⃣ Step 2: Tilt Right | 3️⃣ Step 3: Tilt Forward | 4️⃣ Step 4: Tilt Backward |
  | :---: | :---: | :---: | :---: |
  | ![Dance Stage 1](Movement/Dance_1.jpg) | ![Dance Stage 2](Movement/Dance_2.jpg) | ![Dance Stage 3](Movement/Dance_3.jpg) | ![Dance Stage 4](Movement/Dance_4.png) |
  | Shifts laterally to the left (`miringKiri`). | Shifts laterally to the right (`miringKanan`). | Lowers front limbs (`miringDepan`). | Lowers rear limbs (`miringBelakang`). |

---

### 6. Wave Gesture (Melambai)

The wave gesture coordinates the Front-Right (RF) leg to execute a waving motion in the air while the other three legs support the body weight and maintain dynamic balance.

- **Demonstration Video**:

https://github.com/user-attachments/assets/2216210f-3dde-4dad-980f-ef7e99f90a07

- **Gesture Pose**:
  <p align="center">
    <img src="Pose/Melambai-Pose.jpg" alt="Wave Gesture Pose" width="300">
  </p>

---

## 📱 Blynk Control Interface & Virtual Pin Mapping

The robot is controlled in real-time using a customized Blynk IoT dashboard interface. Below is the visual layout of the control panel:

<p align="center">
  <img src="Blynk_Control.jpg" alt="Blynk Control Dashboard" width="600">
</p>

### Virtual Pin Mapping Details

The robot utilizes Virtual Pins (V1 - V13) to receive commands from the Blynk dashboard.

| Virtual Pin | Dashboard Widget     |  Mode  | System Action / Triggered Function                                           |
| :---------: | :------------------- | :----: | :--------------------------------------------------------------------------- |
|   **V1**    | Stand / Lower Switch | Switch | Toggles stance height between **Stand** (1) and **Lower** (0).               |
|   **V2**    | Forward Button       |  Push  | Executes the coordinated diagonal forward walking gait.                      |
|   **V3**    | Turn Left Button     |  Push  | Executes rotational steering to the left.                                    |
|   **V4**    | Standby Lock         | Switch | **System Lock (E-Stop)**: Disables all inputs, resets flags, locks position. |
|   **V5**    | Backward Button      |  Push  | Executes coordinated diagonal backward walking gait.                         |
|   **V6**    | Turn Right Button    |  Push  | Executes rotational steering to the right.                                   |
|   **V7**    | Alert / Siaga Switch | Switch | Transitions into an outer-stance alert position ready for movement.          |
|   **V8**    | Bow / Sujud Switch   | Switch | Depresses front legs while raising the rear legs.                            |
|   **V9**    | Lean Left Switch     | Switch | Shifts the robot's center of mass laterally to the left.                     |
|   **V10**   | Lean Right Switch    | Switch | Shifts the robot's center of mass laterally to the right.                    |
|   **V11**   | Dance Mode Switch    | Switch | Initiates an automated movement routine (dance sequence).                    |
|   **V12**   | Sleep Stance Switch  | Switch | Folds all joint limbs flat (resting/low-stress position).                    |
|   **V13**   | Wave Gesture Switch  | Switch | Wavy gesture using the Front-Right (RF) leg.                                 |

---

## 🛠️ System Architecture & Specifications

The robot distributes workload between logical control and actuation, minimizing latency and preventing CPU overhead during coordinated motion.

```
       [ Blynk Mobile App ]
                │
                ▼ (Wi-Fi 2.4GHz)
      [ ESP32 / ESP8266 MCU ]  <--- Powered by USB/5S (Logic)
                │
                ▼ (I2C Bus: SDA/SCL)
    [ PCA9685 12-Bit PWM Driver ] <--- Powered by 7.4V Battery (Inductive Load)
                │
                ├─► 3 Servos (Coxa, Femur, Tibia) ──► Right Front (RF) Leg
                ├─► 3 Servos (Coxa, Femur, Tibia) ──► Left Front (LF) Leg
                ├─► 3 Servos (Coxa, Femur, Tibia) ──► Right Rear (RR) Leg
                └─► 3 Servos (Coxa, Femur, Tibia) ──► Left Rear (LR) Leg
```

### 1. Hardware Specifications

- **MCU Support**:
  - **ESP32** (e.g., ESP32 DevKit V1) - Integrated dual-core Xtensa 32-bit MCU with 2.4 GHz Wi-Fi.
  - **ESP8266** (e.g., NodeMCU V3) - Single-core Tensilica 32-bit MCU with 2.4 GHz Wi-Fi.
- **PWM Driver**: Adafruit PCA9685 (16-channel, 12-bit resolution PWM, controlled via I2C at address `0x40`).
- **Actuators**: 12x Micro Servos (SG90 / MG90S metal gear recommended for Femur/Tibia due to torque load).
- **Power Source**: 7.4V DC Lithium battery (2S Li-ion/Li-Po) to supply high current demands of the servo array.
- **Chassis**: Custom 3D-printed PLA/PETG structural elements.

---

## 🔌 Wiring & Pinout Guide

### 1. Logic Interconnections (I2C Bus)

The PCA9685 communicates with the MCU using the standard I2C interface. Connect SDA and SCL pins based on your selected MCU:

| PCA9685 Pin |  ESP32 Pin  | ESP8266 (NodeMCU) Pin |       Description       |
| :---------: | :---------: | :-------------------: | :---------------------: |
|   **SDA**   | **GPIO 18** |    **D4 (GPIO 2)**    |      I2C Data Line      |
|   **SCL**   | **GPIO 23** |   **D5 (GPIO 14)**    |     I2C Clock Line      |
|   **VCC**   |  **3.3V**   |       **3.3V**        | Logic Power (MCU side)  |
|   **GND**   |   **GND**   |        **GND**        | Common Ground Reference |

### 2. Servo Actuator Mapping (PCA9685 Output Channels)

To maintain alignment in the firmware, plug the servos into the PCA9685 channels in the exact order detailed below:

```
                  ┌────────────────────────┐
                  │       FRONT SIDE       │
                  │                        │
  [LF Leg]        │                        │        [RF Leg]
  Coxa: Ch 0 ────►│ (LF)              (RF) │◄──── Coxa: Ch 4
  Femur: Ch 1 ───►│                        │◄──── Femur: Ch 5
  Tibia: Ch 2 ───►│                        │◄──── Tibia: Ch 6
                  │                        │
                  │                        │
  [LR Leg]        │                        │        [RR Leg]
  Coxa: Ch 8 ────►│ (LR)              (RR) │◄──── Coxa: Ch 12
  Femur: Ch 9 ───►│                        │◄──── Femur: Ch 13
  Tibia: Ch 10 ──►│                        │◄──── Tibia: Ch 14
                  │                        │
                  └────────────────────────┘
```

| Leg Designation      | Coxa (Hip) Channel | Femur (Knee) Channel | Tibia (Ankle) Channel |
| :------------------- | :----------------: | :------------------: | :-------------------: |
| **Left Front (LF)**  |        `0`         |         `1`          |          `2`          |
| **Right Front (RF)** |        `4`         |         `5`          |          `6`          |
| **Left Rear (LR)**   |        `8`         |         `9`          |         `10`          |
| **Right Rear (RR)**  |        `12`        |         `13`         |         `14`          |

> [!WARNING]
> Do **NOT** power the PCA9685 servo terminals (V+ and GND screw terminals) using the MCU's 3.3V/5V pins. The 12 servos can pull peak currents exceeding 2.0A, which will instantly damage or trigger brownout resets on the microcontroller. Always use an external 7.4V battery connected directly to the PCA9685 power input terminals.

---

## 🔧 Assembly & Calibration Instructions

### 1. Mechanical Balance & Center of Mass (CoM)

- **Chassis Distribution**: Mount the ESP32 and PCA9685 modules directly in the center of the main body chassis to guarantee even weight distribution across all four legs.
- **Battery Placement**: Anchor the heavy 7.4V battery pack beneath the main chassis plate. This lowers the Center of Gravity (CoG), preventing the robot from tipping over during dynamic gait cycles.

### 2. Physical & Software Calibration

Before writing final angles, calibrate the servo horns to ensure structural symmetry:

1. Burn a sketch initializing all PCA9685 channels to a default $90^\circ$ signal.
2. Manually press the physical servo horns onto the gears such that:
   - **Coxa** joints align perpendicular ($90^\circ$) to the main chassis axis.
   - **Femur** joints sit parallel to the horizontal plane.
   - **Tibia** joints stand perpendicular to the femur.
3. Secure the horns with screws.
4. Fine-tune the initial positions in the firmware (`BERDIRI_COXA`, `BERDIRI_FEMUR`, `BERDIRI_TIBIA`) to compensate for minor mechanical alignment offsets.

---

## 🚀 Uploading & Running the Firmware

### Library Dependencies

Ensure you have installed the following libraries via the Arduino Library Manager:

- `Blynk` (by Volodymyr Shymanskyy)
- `Adafruit PWM Servo Driver Library` (by Adafruit)

### Configuration

1. Open the code matching your hardware:
   - Use [Blynk_Quadrupet_Spider_ESP32.ino](file:///mnt/SStorage/Materi-Kuliah/KP/Quadrupped-Robot/Blynk_Quadrupet_Spider_ESP32/Blynk_Quadrupet_Spider_ESP32.ino) for ESP32.
   - Use [Blynk_Quadrupet_Spider_ESP8266.ino](file:///mnt/SStorage/Materi-Kuliah/KP/Quadrupped-Robot/Blynk_Quadrupet_Spider_ESP8266/Blynk_Quadrupet_Spider_ESP8266.ino) for ESP8266.
2. Insert your Blynk Template credentials at the top of the file:
   ```cpp
   #define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
   #define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
   #define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
   ```
3. Update Wi-Fi network parameters:
   ```cpp
   char ssid[] = "YOUR_WIFI_SSID";
   char pass[] = "YOUR_WIFI_PASSWORD";
   ```
4. Set the target board in Arduino IDE (`Tools -> Board -> ESP32 Arduino` or `ESP8266 Boards`) and upload the sketch.

---

## 🛡️ Operational Safety & Maintenance

### 1. Thermal Management (Servo Duty Limit)

Continuous hold torque draws significant current and generates heat inside the micro servos.

- **Operational Limit**: Restrict active runs to **15-20 minutes** at a time.
- **Cooling Action**: Turn off the power immediately if the servo casings feel hot to the touch. Let them cool down completely before restarting.

### 2. Startup and Shutdown Protocols

To protect the gear train from high-torque mechanical shock (jerk) when powering up:

1. **Startup**: Place the robot on a flat, unobstructed surface with legs folded symmetrically. Connect the power. The MCU will perform soft-start sweeps to initial angles.
2. **Shutdown**: Through the Blynk app, command the robot into the **Sleep Stance (V12)** to lower the chassis flat to the ground. This unloads gravity-induced forces from the joints. Disconnect the 7.4V battery pack.

---

## 🔍 Troubleshooting Guide

| Issue                                           | Root Cause                                                                                                                       | Corrective Action                                                                                                                      |
| :---------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------- |
| **Robot does not respond to Blynk commands.**   | ESP32 failed to associate with local Wi-Fi, or Blynk authentication token is incorrect.                                          | Open Serial Monitor at `115200` baud. Verify connection status. Check Blynk token validity and app online indicator.                   |
| **Servos jitter violently under load.**         | Voltage drop/instability. External battery voltage has dropped below the threshold required to drive 12 servos ($<6.0\text{V}$). | Recharge the 7.4V Lithium battery pack using a balance charger. Ensure connection lines use adequate wire gauge.                       |
| **MCU resets spontaneously during walk cycle.** | High peak currents drawn by multiple servos exceed battery discharge rate or trigger local regulator brownout.                   | Install a large decoupling capacitor (e.g., $1000\mu\text{F}$, $10\text{V}$ or higher) across the V+ and GND terminals of the PCA9685. |
| **Gait is asymmetric or robot walks crooked.**  | Physical displacement of a servo horn, stripped gears, or uncalibrated software array offset.                                    | Visually inspect the 3D-printed joints. Readjust the physical servo horn at $90^\circ$ or update the angle array values in the code.   |

---

## 👨‍💻 Credits & Creator Statement

This robot is designed, assembled, wired, calibrated, and programmed **exclusively** by the creator. All components, mechanical linkages, power regulation, and firmware integrations were compiled and executed independently as a single-developer robotics engineering project.
