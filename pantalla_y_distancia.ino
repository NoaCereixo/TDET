#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VL53L0X.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);
Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

int umbral_distancia = 250; //mm

void setup() {

  Serial.begin(9600);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("No se pudo iniciar la pantalla SSD1306"));
    while (1);
  }

  if (!sensor.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  display.clearDisplay();

}

void loop() {
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);

  VL53L0X_RangingMeasurementData_t distancia;

  sensor.rangingTest(&distancia, false);

  if(distancia.RangeMilliMeter < umbral_distancia){
    display.setCursor(10,10);
    display.println(F("PELIGRO ICEBERG!!"));
  }
  else{
    display.setCursor(30,10);
    display.println(F("sin peligro"));
  }

  Serial.println(distancia.RangeMilliMeter*0.1);

  display.display();

  delay(500);

}