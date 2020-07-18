#ifndef _SERVO_H_
#define _SERVO_H_

#include "mbed.h"

class Servo
{
public:
    Servo(PinName pin);
    void write(float percent);
    // float read();
    void position(float degrees);
    void calibrate(float range = 0.0005, float degrees = 45.0);

private:
    PwmOut _pwm;
    float _p;
    float _degrees;
    float _range;
};

float clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

Servo::Servo(PinName pin) : _pwm(pin)
{
    calibrate();
    write(0.5);
}

void Servo::write(float percent)
{
    float offset = _range * 2.0 * (percent - 0.5);
    _pwm.pulsewidth(0.0015 + clamp(offset, -_range, _range));
    _p = clamp(percent, 0.0, 1.0);
}

void Servo::position(float degrees)
{
    float offset = _range * (degrees / _degrees);
    _pwm.pulsewidth(0.0015 + clamp(offset, -_range, _range));
}

void Servo::calibrate(float range, float degrees)
{
    _range = range;
    _degrees = degrees;
}

#endif