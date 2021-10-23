#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>

// Display
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT
#define DHT11_PIN 7
dht DHT;

// Measurement store
int store_temperature = 0;
int store_wind = 0;
int store_humidity = 0;
String store_condition = "";
bool changed = false;

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
}

void print_weather(int temperature, int wind, int humidity, String condition)
{
  lcd.clear();
  lcd.setCursor(0,0);
  String temp_wind = "T:" + String(temperature, DEC) + "C W:" + String(wind, DEC) + "m/s";
  lcd.print(temp_wind);
  lcd.setCursor(0,1);
  String humidity_rain="H:" + String(humidity, DEC) + "% " + condition;
  lcd.print(humidity_rain);
}

void read_DHT()
{
  DHT.read11(DHT11_PIN);
  if (DHT.temperature != store_temperature || 
      DHT.humidity != store_humidity) {
    store_temperature = DHT.temperature;
    store_humidity = DHT.humidity;
    changed = true;
  } else {
    changed = false;
  }
}

void loop()
{
  read_DHT();
  if(changed) print_weather(store_temperature, store_wind, store_humidity, store_condition);
  delay(2000); // delay by 2s otherwise DHT measurement faulty
}
