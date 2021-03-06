/*
Functions that are responsible for controlling the UFV
*/

#pragma once

#include "Arduino.h"
#include <ESP32Servo.h>
#include "esp32-hal-ledc.h"
#include <string>

#define MOTOR_ENABLE 4
#define MOTOR_A 12
#define MOTOR_B 13
// #define MOTOR_CHANNEL 0
// #define MOTOR_RES 8
// #define MOTOR_FREQ 20000

#define PUMP_ENABLE 3

#define PAN_SERVO_ENABLE 2
#define TILT_SERVO_ENABLE 14

Servo null1;
Servo null2;
Servo panServo;
Servo tiltServo;

void motor_init();
void servo_init();
void pump_init();
void control_motor(String direction, int value);
void control_pump(int value);
void move_servo(String plane, int value);

void motor_init()
{
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    pinMode(MOTOR_ENABLE, OUTPUT);
    // ledcSetup(MOTOR_CHANNEL, MOTOR_FREQ, MOTOR_RES);
    // ledcAttachPin(MOTOR_ENABLE, MOTOR_CHANNEL);
}

void pump_init()
{
    pinMode(PUMP_ENABLE, OUTPUT);
    digitalWrite(PUMP_ENABLE, LOW);
}

void servo_init()
{
    panServo.setPeriodHertz(50);
    tiltServo.setPeriodHertz(50);

    null1.attach(PAN_SERVO_ENABLE, 1000, 2000);
    null2.attach(PAN_SERVO_ENABLE, 1000, 2000);

    // panServo.attach(PAN_SERVO_ENABLE, 1000, 2000);
    panServo.attach(PAN_SERVO_ENABLE);
    panServo.write(90);

    // tiltServo.attach(TILT_SERVO_ENABLE, 1000, 2000);
    tiltServo.attach(TILT_SERVO_ENABLE);
    tiltServo.write(90);
}

void control_motor(String direction, int value)
{
    if (direction == "forward")
    {
        digitalWrite(MOTOR_A, HIGH);
        digitalWrite(MOTOR_B, LOW);
    }
    else if (direction == "backward")
    {
        digitalWrite(MOTOR_B, HIGH);
        digitalWrite(MOTOR_A, LOW);
    }

    digitalWrite(MOTOR_ENABLE, value);
    Serial.printf("Writing %u\n", value); // TODO remove
}

void control_pump(int value)
{
    if (value == 1)
        digitalWrite(PUMP_ENABLE, HIGH);
    else
        digitalWrite(PUMP_ENABLE, LOW);
}

void move_servo(String plane, int value)
{
    if (plane == "pan")
        panServo.write(value);
    else if (plane == "tilt")
        tiltServo.write(value);
}