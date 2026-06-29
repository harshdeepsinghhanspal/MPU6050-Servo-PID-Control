#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>

// Object declarations
MPU6050 mpu;
Servo myServo;

// PID Tuning Parameters (Adjust these to tune your system)
double kp = 2.5;   // Proportional gain
double ki = 0.5;   // Integral gain
double kd = 1.2;   // Derivative gain

// PID Variables
double setpoint = 0.0; // The target angle we want to maintain (0 degrees = flat)
double error, lastError, cumError, rateError;
unsigned long lastTime;

// Servo configurations
int servoPin = 9;
int servoHome = 90; // Servo center point

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize MPU6050
  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  
  // Attach Servo
  myServo.attach(servoPin);
  myServo.write(servoHome); 
  
  lastTime = millis();
}

void loop() {
  // 1. Calculate elapsed time
  unsigned long currentTime = millis();
  double elapsedTime = (double)(currentTime - lastTime) / 1000.0; // Convert to seconds
  
  if (elapsedTime >= 0.01) { // Run PID loop every 10ms
    
    // 2. Read sensor data (Getting current Angle from Accelerometer)
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    
    // Calculate pitch angle in degrees using atan2
    double currentAngle = atan2(ay, az) * 180.0 / M_PI;

    // 3. Compute PID components
    error = setpoint - currentAngle;              // Present error
    cumError += error * elapsedTime;              // Past accumulated error
    rateError = (error - lastError) / elapsedTime; // Future predicted error

    // Constrain integral to prevent "windup"
    cumError = constrain(cumError, -50, 50);

    // Combine P, I, and D terms
    double pidOutput = (kp * error) + (ki * cumError) + (kd * rateError);

    // 4. Drive the Servo
    // Move servo relative to its home position based on PID calculation
    int newServoPosition = servoHome + pidOutput;
    newServoPosition = constrain(newServoPosition, 0, 180); // Keep within hardware limits
    
    myServo.write(newServoPosition);

    // 5. Save state for next iteration
    lastError = error;
    lastTime = currentTime;

    // Debugging print
    Serial.print("Angle: "); Serial.print(currentAngle);
    Serial.print(" | Error: "); Serial.print(error);
    Serial.print(" | Servo Output: "); Serial.println(newServoPosition);
  }
}