# ESP8266 Plant Signals to Audio

A simple DIY experiment to read small electrical signal variations from a mint plant using homemade electrodes,
Here The video  of electrodes: https://studio.youtube.com/video/zhUo6wgOafc/edit

an ADS1115 analog-to-digital converter, and an ESP8266.  
The signal is then converted into an audible frequency on GPIO14.

## Description

This project is an experimental test to transform the electrical variations of a plant into sound.

Two homemade electrodes are placed on two different points of a mint plant leaf or stem. These electrodes are connected to the 
differential inputs A0 and A1 of an ADS1115 module. The ADS1115 is connected to an ESP8266 through I2C.

The ESP8266 reads the differential signal, filters it, maps it to an audio frequency, and generates a simple square wave output on GPIO14.

The result is not a professional bioelectric measurement system, but a simple and working experiment for converting plant signal variations into audible sound.

## Hardware Used

- ESP8266 board, such as NodeMCU or Wemos D1 Mini
- ADS1115 16-bit ADC module
- Two homemade electrodes
- Mint plant
- Passive buzzer or small audio amplifier
- Jumper wires
- Optional: small magnets, clips, or conductive material to hold the electrodes on the plant

## Wiring

### ADS1115 to ESP8266

| ADS1115 | ESP8266 |
|--------|---------|
| VCC | 3.3V |
| GND | GND |
| SDA | D2 / GPIO4 |
| SCL | D1 / GPIO5 |

### Plant Electrodes

| Electrode | ADS1115 |
|----------|---------|
| Electrode 1 on leaf/stem | A0 |
| Electrode 2 on leaf/stem | A1 |

For Youtube Video : https://www.youtube.com/watch?v=PfegsxzqUrs

```cpp
ads.readADC_Differential_0_1();
