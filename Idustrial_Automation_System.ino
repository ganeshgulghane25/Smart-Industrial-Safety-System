#include <DHT.h>
#include <LiquidCrystal.h>

// --- Pin Definitions ---
#define DHTPIN 2
#define DHTTYPE DHT11
#define GAS_PIN A0
#define RELAY_PIN 7
#define BUZZER_PIN 6
#define LED_PIN 5

// --- Objects ---
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// --- Thresholds ---
int gasThreshold = 400;

void setup() {
  pinMode(GAS_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  lcd.begin(16, 2);
  dht.begin();
  lcd.print("Safety System");
  delay(1500);
  lcd.clear();
}

void loop() {
  int gasValue = analogRead(GAS_PIN);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  lcd.setCursor(0, 0);
  lcd.print("Gas:");
  lcd.print(gasValue);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C ");

  if (gasValue > gasThreshold) {
    digitalWrite(RELAY_PIN, HIGH);   // Fan ON
    digitalWrite(BUZZER_PIN, HIGH);  // Buzzer ON
    digitalWrite(LED_PIN, HIGH);     // LED ON
    lcd.print("ALRT");
  } else {
    digitalWrite(RELAY_PIN, LOW);    // Fan OFF
    digitalWrite(BUZZER_PIN, LOW);   // Buzzer OFF
    digitalWrite(LED_PIN, LOW);      // LED OFF
    lcd.print("SAFE");
  }

  delay(1000);
}
