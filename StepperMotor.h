// StepperMotor.h - Header file for StepperMotor library


#pragma once
#include <Wire.h>
#include <AccelStepper.h>

class StepperMotor {
public:
    StepperMotor(int dirPin, int stepPin, int enPin, int microStep, float radius, float ratio);
    void setup();
    void enableMotor();
    void disableMotor();
    void moveDistance(float distance);
    void updateMicroStepping(int newMicroStep);
    void setSpeedSteps(float speedSteps);
    void setAccelerationSteps(float accelerationSteps);
    void run();
    long distanceToGo();
    long currentPosition();
    long calculatePosition(float distance);
    long isMoving();
    void setSpeed(float mmPerSec);
    void setAcceleration(float mmPerSec2);
    void stop();
    void slowStop();

private:
    int dirPin, stepPin, enPin;
    int microStepping;
    float avgRadius;
    float gearRatio;
    AccelStepper stepper;
    void setupPCA9538A();
    void pca9538a_write_reg(uint8_t reg, uint8_t value);
    uint8_t pca9538a_read_reg(uint8_t reg);
    uint8_t getStepMode(int microStep);
};