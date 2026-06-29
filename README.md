# Servo MPU6050 PID Controller

A simple Arduino project that uses an **MPU6050 IMU** and a **Servo Motor** to maintain a desired angle using a **PID (Proportional-Integral-Derivative) controller**.

## Features

* Reads tilt angle from the MPU6050 accelerometer
* Calculates pitch using `atan2()`
* Implements a basic PID control algorithm
* Controls a servo motor to maintain the target angle
* Outputs live debugging information through the Serial Monitor

## Components Required

* Arduino Uno/Nano (or compatible)
* MPU6050 Sensor
* Servo Motor (SG90/MG90S or similar)
* Jumper wires
* Breadboard (optional)

## Libraries Used

Install the following Arduino libraries before uploading the code:

* Wire
* Servo
* MPU6050

## Connections

### MPU6050

| MPU6050 | Arduino       |
| ------- | ------------- |
| VCC     | 5V            |
| GND     | GND           |
| SDA     | A4 (Uno/Nano) |
| SCL     | A5 (Uno/Nano) |

### Servo

| Servo  | Arduino                          |
| ------ | -------------------------------- |
| Signal | D9                               |
| VCC    | 5V (External supply recommended) |
| GND    | GND                              |

> **Note:** For larger servos, use an external 5V power supply and connect its ground to the Arduino ground.

## PID Parameters

The default tuning values are:

```cpp
kp = 2.5
ki = 0.5
kd = 1.2
```

These values may need adjustment depending on your servo and mechanical setup.

## How It Works

1. Initialize the MPU6050 and servo.
2. Read accelerometer data.
3. Calculate the current pitch angle.
4. Compute the PID output.
5. Move the servo according to the PID correction.
6. Repeat every 10 ms.

## Serial Output

The Serial Monitor displays:

* Current Angle
* PID Error
* Servo Position

Example:

```
Angle: -5.62 | Error: 5.62 | Servo Output: 104
```

## Upload Instructions

1. Install the required libraries.
2. Connect the hardware as shown above.
3. Select the correct Arduino board and COM port.
4. Upload the sketch.
5. Open the Serial Monitor at **115200 baud**.

## Notes

* The controller attempts to keep the sensor at **0° (horizontal)** by default.
* The integral term is constrained to reduce integral windup.
* Servo output is limited between **0° and 180°** for safe operation.

## License

This project is available for educational and personal use.
