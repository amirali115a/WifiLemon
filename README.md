# WifiLemon
Advanced Wifi Deauth Attack Detetctor
# WifiLemon

## Introduction
WifiLemon is an advanced tool for detecting Deauth attacks on Wi-Fi networks. This tool uses specific algorithms to identify attacks and protect your network.

## Features
- Detect Deauth attacks
- LED light turns on when an attack is detected
- Compatible with Arduino and ESP8266
- Display attack details in the terminal using a Python script

## Installation
### Flashing to ESP8266
1. Clone the repository:
    ```bash
    git clone https://github.com/amirali115a/WifiLemon.git
    ```
2. Open the `wifilemon.ino` file in the Arduino IDE and flash it to the ESP8266 board.

### Running CLI
1. Install Python dependencies:
    ```bash
    pip install -r requirements.txt
    ```
2. Run the CLI script:
    ```bash
    python wifilemoncli.py
    ```

## Usage
### Arduino ESP8266
After flashing the board, the LED light will turn on when an attack is detected.

### Terminal
To view attack details in the terminal:
```bash
python wifilemoncli.py
