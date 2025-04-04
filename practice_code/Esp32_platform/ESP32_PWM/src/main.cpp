#include <Arduino.h>

const int ledPin = 2;  // Pin connected to LED
const int potPin = 34;  // Pin connected to potentiometer

// PWM configuration
const int freq = 10000;      // 10kHz PWM frequency
const int pwmChannel = 0;    // PWM channel
const int resolution = 12;   // 12-bit resolution (max for ESP32)

// Variables to store the potentiometer reading and duty cycle
int potValue = 0;  
int dutyCycle = 0;

void setup() {
  Serial.begin(9600);
  
  // Set up PWM on ledPin
  ledcSetup(pwmChannel, freq, resolution);  
  ledcAttachPin(ledPin, pwmChannel);

  Serial.println("PWM LED control using Potentiometer");
}

void loop() {
  // Read potentiometer value (0-4095 for 12-bit ADC)
  potValue = analogRead(potPin);
  
  // Convert potValue to PWM duty cycle (0-4095)
  dutyCycle = map(potValue, 0, 4095, 0, 4095);
  
  // Update PWM duty cycle
  ledcWrite(pwmChannel, dutyCycle);
  
  // Print the duty cycle
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print("\tPWM Duty Cycle: ");
  Serial.println(dutyCycle);
  
  delay(100);  // Wait for 1 second before next reading
}