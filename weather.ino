#include <dummy.h>

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL69qcV8NtH"
#define BLYNK_TEMPLATE_NAME "humid"
#define BLYNK_AUTH_TOKEN "bjNT3YyVd_sdu0zF3qv-gTkZcJwpqhm1"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "telsuko";
char pass[] = "9030602705";

// Define the DHT sensor type and the pin it’s connected to
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN D1       // Pin which is connected to the DHT sensor

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("Temperature: ");
  Serial.println(temperature);
  Serial.println(" °C, Humidity: ");
  Serial.println(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V0, humidity);
  Blynk.virtualWrite(V1, temperature);

  delay(3000); // Update every 3 seconds
}
