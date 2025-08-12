MultiStepperClickEsp32-driver-library
A lightweight Arduino/ESP32 library to control up to two stepper motors via the Multi Stepper Click (TB62269) Click board from MikroElektronika using ESP32’s I²C interface.

Key Features
Initialize and configure up to two independent stepper motor channels

Set microstepping resolution, direction, and step angle for each motor

Control speed (steps per second) and acceleration

Perform precise step moves or continuous rotations

Enable or disable motor drivers to conserve power

Query current step counter and driver fault status

Table of Contents
Hardware Requirements

Wiring Diagram

Installation

Usage

Include Library

Initialize Driver

Configure Motor Parameters

Move Motor

Continuous Rotation

Stop and Disable

Status and Diagnostics

API Reference

License

Hardware Requirements
ESP32 development board (NodeMCU-32S, WROOM, etc.)

MikroElektronika Multi Stepper Click (TB62269) board

Two bipolar stepper motors

I²C pull-up resistors (4.7 kΩ) if not already present on your click board or ESP32 dev board

Wiring Diagram
Multi Stepper Click Pin	ESP32 Pin
SCL	GPIO 22 (I2C SCL)
SDA	GPIO 21 (I2C SDA)
RST	Not used (optional reset)
EN	Not used (enabled via I²C)
VIN	3.3 V
GND	GND
Ensure common ground between ESP32 and click board. Use 5 V motor supply on VIN if your board supports it, and adjust logic voltage selector accordingly.

Installation
Download or clone this repository into your Arduino libraries folder:
~/Arduino/libraries/MultiStepperClickEsp32-driver-library

Restart the Arduino IDE.

In your sketch, select Sketch → Include Library → MultiStepperClickEsp32.

Usage
Include Library
cpp
#include <Wire.h>
#include <MultiStepperClickEsp32.h>
Initialize Driver
cpp
// Create instance on I2C bus Wire, address 0x60 (default)
MultiStepperClickEsp32 stepper(&Wire, 0x60);

void setup() {
  Wire.begin(21, 22);           // SDA, SCL pins
  stepper.begin();              // Initialize driver
}
Configure Motor Parameters
cpp
// channel: 0 or 1
// stepAngle: in thousandths of a degree (e.g., 176 for 1.8° step)
// microstep: 1, 2, 4, 8, 16
// dir: 0 = forward, 1 = reverse
stepper.setStepperParams(0, 176, 16, 0);
stepper.setStepperParams(1, 176, 16, 1);
Move Motor
cpp
// channel, targetSteps, speed in steps/sec, acceleration in steps/sec²
stepper.moveSteps(0, 200, 400, 800);
Continuous Rotation
cpp
// channel, speed (positive = forward, negative = reverse)
stepper.moveContinuous(1, -300);
Stop and Disable
cpp
stepper.stop(0);         // Gracefully decelerate and stop
stepper.disable(1);      // Immediately disable driver (coast)
Status and Diagnostics
cpp
long current = stepper.getCurrentSteps(0);     // Retrieve internal step count
bool fault   = stepper.getFaultStatus(0);      // true if driver fault present
stepper.resetSteps(0);                         // Zero internal counter
API Reference
Constructor
MultiStepperClickEsp32(TwoWire* i2cBus, uint8_t address = 0x60)

i2cBus: Pointer to Wire or custom I²C.

address: 7-bit I²C address (default 0x60).

begin()
cpp
bool begin();
Initializes I²C and verifies device presence.

Returns true on success.

setStepperParams()
cpp
void setStepperParams(uint8_t channel,
                      uint16_t stepAngle,
                      uint8_t microstep,
                      uint8_t direction);
channel: 0 or 1.

stepAngle: Motor step angle × 1000 (e.g., 1.8° → 1800).

microstep: 1, 2, 4, 8, or 16.

direction: 0 = forward, 1 = reverse.

enable()/disable()
cpp
void enable(uint8_t channel);
void disable(uint8_t channel);
enable: Powers motor driver.

disable: Coasts motor (no torque).

moveSteps()
cpp
bool moveSteps(uint8_t channel,
               long targetSteps,
               uint16_t speed,
               uint16_t acceleration);
targetSteps: Desired absolute or relative steps (signed).

speed: Max speed in steps/sec.

acceleration: Acceleration in steps/sec².

Returns true on command acceptance.

moveContinuous()
cpp
bool moveContinuous(uint8_t channel, int16_t speed);
speed: Steps/sec (signed).

Returns true on acceptance.

stop()
cpp
void stop(uint8_t channel);
Soft deceleration to immediate stop.

getCurrentSteps()
cpp
long getCurrentSteps(uint8_t channel);
Returns current internal counter.

getFaultStatus()
cpp
bool getFaultStatus(uint8_t channel);
Returns true if overcurrent, thermal shutdown, or undervoltage.

resetSteps()
cpp
void resetSteps(uint8_t channel);
Clears internal step counter to zero.

License
This project is released under the MIT License.
See LICENSE for details.
