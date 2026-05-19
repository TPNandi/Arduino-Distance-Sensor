#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// HC-SR04 Pins
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  Serial.begin(9600);

  // Initialize the OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 10);
  display.print("Distance Meter");
  display.display();
  delay(2000);

  // Set up sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration;
  int distance;

  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by sending a 10 microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (speed of sound is 0.034 cm/us)
  distance = duration * 0.034 / 2;

  // Update the OLED Display
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Current Distance:");

  display.setTextSize(2); // Make the number bigger
  display.setCursor(0, 15);
  display.print(distance);
  display.print(" cm");

  display.display(); // Push everything to the screen

  // Log to Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(250); // Small delay so the screen doesn't flicker too much
}