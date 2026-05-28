# NMR Pulse Program Generator — RF Transmitter for Pulsed NMR

A low-cost RF transmitter system designed for pulsed Nuclear Magnetic Resonance (NMR) 
experiments, developed as part of B.Sc. Physics project at M.S. Ramaiah University of 
Applied Sciences, Bengaluru (2026).

## Project Overview

Commercial NMR pulse programmers offer nanosecond precision but are extremely 
expensive. This project investigates whether low-cost microcontroller platforms 
(Raspberry Pi Pico + ESP32) can provide sufficiently stable timing for RF transmitter 
development in a laboratory NMR setup.

The system successfully generates pulse-controlled RF bursts suitable for pulsed NMR 
excitation using only affordable, off-the-shelf hardware.

---

## Objectives

- Generate controlled digital timing pulses using microcontroller hardware
- Test dual-output synchronization for pulse gating
- Combine digital pulse and RF carrier using a Double Balanced Mixer (DBM)
- Observe and validate RF pulse output via oscilloscope
- Evaluate timing stability for NMR instrumentation integration

---

## Hardware Used

| Component | Purpose |
|---|---|
| Raspberry Pi Pico (RP2040) | Initial pulse generation (MicroPython) |
| ESP32 (ESP-WROOM-32) | Final pulse generation with hardware timers (C++) |
| HP 8647A RF Signal Generator | Continuous RF carrier source (~10 MHz) |
| Double Balanced Mixer (DBM) | Converts continuous RF into pulsed RF bursts |
| RF Amplifier | Amplifies pulsed RF output for probe coupling |
| Tektronix Oscilloscope | Waveform validation at each stage |

---

## Software & Languages

- **MicroPython** — Raspberry Pi Pico (PIO state machine based pulse generation)
- **C++ / Arduino IDE** — ESP32 (hardware RMT timer based pulse generation)

---

## System Architecture
PPG (ESP32) → Digital Pulse
↓
RF Generator → [Double Balanced Mixer] → Pulsed RF → [Amplifier] → Probe

The ESP32 generates precise digital timing pulses. These gate the continuous RF 
carrier from the signal generator through the Double Balanced Mixer, 
producing short RF bursts. The bursts are then amplified for NMR probe excitation.

---

## Key Results

### Raspberry Pi Pico (Initial Platform)
- Successfully generated single-channel pulses (1µs–10µs–2µs sequences)
- Dual-channel timing showed jitter and edge displacement
- Insufficient for precise NMR pulse control

### ESP32 (Final Platform)
- Stable pulse width across repeated cycles
- Consistent delay between pulses
- Improved multi-channel synchronization
- Hardware RMT timers eliminated software-induced jitter

### Mixer Output
- RF transmission confirmed exclusively during pulse periods
- Carrier waveform integrity maintained
- System validated as functional RF gate for NMR excitation

---

## How to Run

### ESP32 (Recommended)
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support via Board Manager
3. Open `esp32/sketch_mar16a.ino`
4. Connect ESP32 via USB, select correct COM port
5. Upload and monitor pulse output on oscilloscope

### Raspberry Pi Pico
1. Flash MicroPython firmware onto Pico
2. Open `pico/hahn_echo.py` in Thonny IDE
3. Run and observe output on oscilloscope (single channel recommended)

---

## Pulse Parameters (ESP32)

| Parameter | Value |
|---|---|
| PRE pulse width | 1 µs |
| MAIN pulse width | 1 µs |
| Delay between pulses | 25 µs |
| Repetition period | 1 second |
| RF Carrier Frequency | ~10 MHz (50.339 MHz in full setup) |

This project is open-source for educational and research purposes.  
Feel free to use, modify, and build upon this work with attribution.
