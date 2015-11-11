#include <SPI.h>
#include <Wire.h>   
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Using NOKIA 5110 monochrome 84 x 48 pixel display
// pin 9 - Serial clock out (SCLK) CLK:5
// pin 8 - Serial data out (DIN) DIN:4
// pin 7 - Data/Command select (D/C) DC:3
// pin 5 - LCD chip select (CS) CE:2
// pin 6 - LCD reset (RST) RST:1
Adafruit_PCD8544 display = Adafruit_PCD8544(9, 8, 7, 5, 6);

void setup() {
  Wire.begin();
  display.begin(); // Ini8ialize the display
  display.setContrast(58); // Set the contrast
  
// Start device display with ID of sensor
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0); display.print("MPU9250");
  display.setTextSize(1);
  display.setCursor(0, 20); display.print("9-DOF 16-bit");
  display.setCursor(0, 30); display.print("motion sensor");
  display.setCursor(20,40); display.print("60 ug LSB");
  display.display();
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

}
