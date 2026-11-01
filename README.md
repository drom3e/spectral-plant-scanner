# spectral-plant-scanner
Phone attached spectral scanner that detects plant stress via chlorophyll levels using an ESP32 and AS7341 sensor. Achieved 3rd place at UNSW's Buildathon competition!

# Spectral Plant Scanner

A phone-attached scanner that detects plant stress by measuring chlorophyll levels based on light reflectance. Built over the course of 6 weeks for the UNSW Buildathon 2026 in a team of 6, where it placed **3rd out of 60+ teams** in the Opens Division. 

## The problem
Plant stress is usually noticed only after visible damage. The competition theme was using robotics to address the sustainability crisis to help monitor the environment in novel ways, so we built a cheap tool that flags plant stress in a more accessible way. 

## How it works
1. The AS7341 spectral sensor reads light reflected from a leaf across multiple wavelength bands.
2. An ESP32 reads the sensor over I2C and processes the readings (firmware in C++).
3. The readings are compared against reference data for healthy plants to estimate chlorophyll levels.
4. The phone app displays the result and flags the plant if it looks stressed.

## Hardware
- ESP32 microcontroller
- AS7341 11-channel spectral sensor
- Power source, USB from phone
- Custom enclosure,3D-printed in PLA, designed in Onshape.

## Software
- Firmware: C++ (Arduino framework)
- Communication: Bluetooth over the ESP-32 directly to the phone. 

## Build and run
1. Install the Arduino IDE (or PlatformIO) and ESP32 board support.
2. Install the Adafruit AS7341 library.
3. Open `firmware/[filename].ino`, select your ESP32 board, and upload.

