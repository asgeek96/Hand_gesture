# 🤖 Hand Gesture Controlled Car — Arduino & RF Communication

A wireless hand gesture controlled robot car built on Arduino UNO. Hand movements are captured via an accelerometer sensor on a glove and transmitted wirelessly over an RF link to control the car's movement in real time.

---

## 📌 About the Project

This project uses an **ADXL335 accelerometer** mounted on a hand glove to detect hand orientation. The tilt data is processed by an Arduino UNO, encoded, and transmitted wirelessly via an **RF module** to a receiver unit that drives the robot car's motors accordingly.

> A practical demonstration of wireless communication, sensor interfacing, and embedded systems — all without any smartphone or internet dependency.

---

## ⚙️ How It Works

The system is divided into two sections:

### 📡 Transmitter (Worn by user)
```
Hand Gesture → ADXL335 Sensor → Arduino UNO → HT12E Encoder → RF Transmitter
```
1. User wears the glove with the **ADXL335 accelerometer**
2. The sensor detects hand tilt direction (forward, backward, left, right)
3. Arduino reads the sensor data and sends corresponding signals to the **HT12E encoder**
4. The encoder converts parallel data to **serial data**
5. The **RF Transmitter** sends the serial data wirelessly

### 🚗 Receiver (On the car)
```
RF Receiver → HT12D Decoder → L293D Motor Driver → DC Motors → Car Movement
```
1. The **RF Receiver** picks up the transmitted serial data
2. The **HT12D decoder** converts serial data back to parallel
3. The **L293D Motor Driver IC** interprets the signals
4. Motors move the car in the corresponding direction

---

## 🗺️ Direction Mapping

| Hand Gesture | Car Movement |
|-------------|--------------|
| Tilt Forward | Move Forward |
| Tilt Backward | Move Backward |
| Tilt Left | Turn Left |
| Tilt Right | Turn Right |
| Neutral / Flat | Stop |

---

## 🛠️ Components Used

### Transmitter Side
| Component | Purpose |
|-----------|---------|
| Arduino UNO (ATmega328) | Reads sensor data & controls encoder |
| ADXL335 Accelerometer | Detects hand tilt/orientation |
| HT12E Encoder IC | Converts parallel data to serial |
| RF Transmitter Module (433 MHz) | Transmits data wirelessly |
| Breadboard + Jumper Wires | Circuit connections |

### Receiver Side
| Component | Purpose |
|-----------|---------|
| RF Receiver Module (433 MHz) | Receives wireless serial data |
| HT12D Decoder IC | Converts serial data to parallel |
| L293D Motor Driver IC | Drives DC motors based on input |
| DC Motors | Powers the car movement |
| Breadboard + Jumper Wires | Circuit connections |

---

## 📁 Repository Structure

```
Hand_gesture/
│
├── Code/
│   ├── transmitter.ino       # Arduino code for transmitter (glove side)
│   └── receiver.ino          # Arduino code for receiver (car side)
│
├── images/
│   ├── circuit_transmitter.png    # Transmitter circuit diagram
│   ├── circuit_receiver.png       # Receiver circuit diagram
│   └── project_demo.png           # Final assembled project photo
│
├── Presentation.pptx         # Project presentation
├── README.md
└── .gitignore
```

---

## 💡 Applications

- **Remote surveillance robots** — operate in areas unsafe for humans
- **Military robotics** — gesture-controlled unmanned ground vehicles
- **Assistive technology** — wheelchair control for physically challenged individuals
- **Industrial automation** — hands-free machine control

---

## 📸 Circuit Overview

**Transmitter:**
```
ADXL335 → A0, A1, A2 (Analog pins of Arduino)
HT12E   → D0-D3 connected to Arduino digital pins
RF TX   → DATA pin connected to HT12E serial output
```

**Receiver:**
```
RF RX   → DATA pin to HT12D serial input
HT12D   → Output pins to L293D input pins
L293D   → Output pins to DC motors
```

---

## 🚀 How to Upload the Code

1. Install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Open `Code/transmitter.ino` and upload to the **transmitter Arduino**
3. Open `Code/receiver.ino` and upload to the **receiver Arduino**
4. Assemble the circuits as per the diagrams in `images/`
5. Power both units and test hand gestures

---

## 👤 Author

**Anubhav Srivastava**
[GitHub](https://github.com/asgeek96) · [LinkedIn](https://www.linkedin.com/in/asgeek)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
