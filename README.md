# MultiStepperClickEsp32-driver-library

A lightweight Arduino/ESP32 library to control up to two stepper motors via the Multi Stepper Click (TB62269) Click board from MikroElektronika using ESP32’s I²C interface.

***

## Key Features

- **Dual-channel support**: Control two independent stepper motors  
- **Microstepping & direction**: Configure resolution, direction, and step angle  
- **Speed & acceleration**: Precise control over motion parameters  
- **Motion modes**: Discrete steps or continuous rotation  
- **Power management**: Enable/disable drivers to save power  
- **Diagnostics**: Monitor step counter and fault status  

***

## Table of Contents

1. [Hardware Requirements](#hardware-requirements)  
2. [Wiring Diagram](#wiring-diagram)  
3. [Installation](#installation)  
4. [Usage](#usage)  
   1. [Include Library](#include-library)  
   2. [Initialize Driver](#initialize-driver)  
   3. [Configure Motor Parameters](#configure-motor-parameters)  
   4. [Move Motor](#move-motor)  
   5. [Continuous Rotation](#continuous-rotation)  
   6. [Stop and Disable](#stop-and-disable)  
   7. [Status and Diagnostics](#status-and-diagnostics)  
5. [API Reference](#api-reference)  
6. [License](#license)  

***

## Hardware Requirements

- ESP32 development board (NodeMCU-32S, WROOM, etc.)  
- MikroElektronika Multi Stepper Click (TB62269) board  
- Two bipolar stepper motors  
- I²C pull-up resistors (4.7 kΩ) if not present on the boards  

***

## Wiring Diagram

| Multi Stepper Click Pin | ESP32 Pin           |
|-------------------------|---------------------|
| **SCL**                 | GPIO 22 (I²C SCL)   |
| **SDA**                 | GPIO 21 (I²C SDA)   |
| **RST**                 | Not used (optional) |
| **EN**                  | Not used (I²C)      |
| **VIN**                 | 3.3 V or 5 V        |
| **GND**                 | GND                 |

> Ensure a common ground between ESP32 and the click board.

***

## Installation

```bash
cd ~/Arduino/libraries
git clone https://github.com/EvilChangIndia/MultiStepperClickEsp32-driver-library.git
```

1. Restart the Arduino IDE.  
2. In your sketch: **Sketch → Include Library → MultiStepperClickEsp32**.  

***

## Usage

### Include Library

```cpp
#include 
#include 
```

### Initialize Driver

```cpp
MultiStepperClickEsp32 stepper(&Wire, 0x60);

void setup() {
  Wire.begin(21, 22);
  if (!stepper.begin()) {
    Serial.println("Stepper driver not found");
    while (1);
  }
}
```

### Configure Motor Parameters

```cpp
// channel: 0 or 1
// stepAngle: thousandths of a degree (e.g., 1800 for 1.8°)
// microstep: 1, 2, 4, 8, 16
// direction: 0 = forward, 1 = reverse
stepper.setStepperParams(0, 1800, 16, 0);
stepper.setStepperParams(1, 1800, 16, 1);
```

### Move Motor

```cpp
// channel, targetSteps, speed (steps/sec), acceleration (steps/sec²)
stepper.moveSteps(0, 200, 400, 800);
```

### Continuous Rotation

```cpp
// channel, speed (signed steps/sec)
stepper.moveContinuous(1, -300);
```

### Stop and Disable

```cpp
stepper.stop(0);     // Soft stop
stepper.disable(1);  // Driver coast
```

### Status and Diagnostics

```cpp
long current = stepper.getCurrentSteps(0);
bool fault   = stepper.getFaultStatus(0);
stepper.resetSteps(0);
```

***

## API Reference

- **Constructor**  
  `MultiStepperClickEsp32(TwoWire* i2cBus, uint8_t address = 0x60)`

- **begin()**  
  `bool begin();`

- **setStepperParams()**  
  `void setStepperParams(uint8_t channel, uint16_t stepAngle, uint8_t microstep, uint8_t direction);`

- **enable()/disable()**  
  `void enable(uint8_t channel);`  
  `void disable(uint8_t channel);`

- **moveSteps()**  
  `bool moveSteps(uint8_t channel, long targetSteps, uint16_t speed, uint16_t acceleration);`

- **moveContinuous()**  
  `bool moveContinuous(uint8_t channel, int16_t speed);`

- **stop()**  
  `void stop(uint8_t channel);`

- **getCurrentSteps()**  
  `long getCurrentSteps(uint8_t channel);`

- **getFaultStatus()**  
  `bool getFaultStatus(uint8_t channel);`

- **resetSteps()**  
  `void resetSteps(uint8_t channel);`

***

## License

Released under the **MIT License**. See [LICENSE](LICENSE) for details.
