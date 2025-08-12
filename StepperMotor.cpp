// StepperMotor.cpp - a custom stepper library by Kiran Sreekumar

#include "StepperMotor.h"

#define PCA9538A_ADDR 0x70
#define PCA9538A_REG_INPUT  0x00
#define PCA9538A_REG_OUTPUT 0x01
#define PCA9538A_REG_POLARITY 0x02
#define PCA9538A_REG_CONFIG 0x03
#define PCA9538A_CONFIG_VALUE 0xF8

#define defaultMaxStepPerSec 16000
#define defaultStepAcceleration 32000

const uint8_t stepModes[] = {0x04, 0x01, 0x06, 0x05, 0x03, 0x07};

StepperMotor::StepperMotor(int dirPin, int stepPin, int enPin, int microStep, float radius, float ratio)
    : dirPin(dirPin), stepPin(stepPin), enPin(enPin), microStepping(microStep), avgRadius(radius), gearRatio(ratio),
      stepper(AccelStepper::DRIVER, stepPin, dirPin) {}

void StepperMotor::pca9538a_write_reg(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(PCA9538A_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t StepperMotor::pca9538a_read_reg(uint8_t reg) {
    Wire.beginTransmission(PCA9538A_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(PCA9538A_ADDR, 1);
    return Wire.available() ? Wire.read() : 0;
}

uint8_t StepperMotor::getStepMode(int microStep) {
    uint8_t index = static_cast<uint8_t>(log(microStep) / log(2));
    return stepModes[index];
}

void StepperMotor::setupPCA9538A() {
    pca9538a_write_reg(PCA9538A_REG_CONFIG, PCA9538A_CONFIG_VALUE);
    delay(10);
    pca9538a_write_reg(PCA9538A_REG_OUTPUT, getStepMode(microStepping));
    delay(10);
}

void StepperMotor::setup() {
    Wire.begin();
    setupPCA9538A();
    pinMode(enPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    disableMotor();
    stepper.setPinsInverted(true, false, false); // Invert direction only
    stepper.setMaxSpeed(defaultMaxStepPerSec);       // current defaults
    stepper.setAcceleration(defaultStepAcceleration);
}

void StepperMotor::enableMotor() {
    digitalWrite(enPin, HIGH);
}

void StepperMotor::disableMotor() {
    digitalWrite(enPin, LOW);
}

void StepperMotor::stop() {
    stepper.stop();  
    stepper.runToPosition();  // force it to stop immediately
}

void StepperMotor::slowStop() {
    stepper.stop();           // Stop the stepper with acceleration (AccelStepper method)
}

long StepperMotor::distanceToGo() {
    return stepper.distanceToGo();
}

long StepperMotor::currentPosition() {
    return stepper.currentPosition();
}

long StepperMotor::isMoving() {
    return (stepper.distanceToGo() != 0);
}

long StepperMotor::calculatePosition(float distance) {
    return round(microStepping * 200.0 * gearRatio * distance / (2.0 * M_PI * avgRadius));
}

void StepperMotor::moveDistance(float distance) {
    long steps = calculatePosition(distance);
    stepper.moveTo(steps);
}

void StepperMotor::updateMicroStepping(int newMicroStep) {
    microStepping = newMicroStep;
    disableMotor();
    setupPCA9538A();
}

void StepperMotor::setSpeedSteps(float speedSteps) {
    stepper.setMaxSpeed(speedSteps);
}

void StepperMotor::setAccelerationSteps(float accelerationSteps) {
    stepper.setAcceleration(accelerationSteps);
}

void StepperMotor::run() {
    stepper.run();
}

void StepperMotor::setSpeed(float mmPerSec) {
    float stepsPerSec = (microStepping * 200.0 * gearRatio * mmPerSec) / (2 * M_PI * avgRadius);
    stepper.setMaxSpeed(stepsPerSec);
}

void StepperMotor::setAcceleration(float mmPerSec2) {
    float stepsPerSec2 = (microStepping * 200.0 * gearRatio * mmPerSec2) / (2 * M_PI * avgRadius);
    stepper.setAcceleration(stepsPerSec2);
}