#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define LDR_PIN A0

DHT dht(DHTPIN, DHTTYPE);

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 8);

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int lightValue = analogRead(LDR_PIN);

  // Check DHT sensor
  if (isnan(temperature) || isnan(humidity)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Sensor Error");

    Serial.println("DHT22 Sensor Error");
    delay(2000);
    return;
  }

  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("Light Intensity: ");
  Serial.print(lightValue);
  Serial.println(" / 1023");

  Serial.println("----------------");

  // Screen 1: Temperature + Humidity
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);
  lcd.print("%");

  delay(3000);

  // Screen 2: Light Intensity
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Light Intensity");

  lcd.setCursor(0, 1);
  lcd.print(lightValue);
  lcd.print(" / 1023");

  delay(3000);
}
