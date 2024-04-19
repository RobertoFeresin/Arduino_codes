#include <HCSR04.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

const int pino_trigger = D6;
const int pino_echo = D5;
const int buzzer = D1;
const int pinoLDR = A0;
const int pino_dht = D4;

UltraSonicDistanceSensor distanceSensor(pino_trigger, pino_echo);
DHT dht(pino_dht, DHT11);

void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(pinoLDR, INPUT);
  dht.begin();
  WiFi.begin("IP", "SSWD");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  float distance = distanceSensor.measureDistanceCm();
  float lightIntensity = analogRead(pinoLDR) * (5.0 / 1024.0);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Distance(cm): ");
  Serial.print(distance);
  Serial.print("\tLight Intensity(V): ");
  Serial.print(lightIntensity);
  Serial.print("\tTemperature(C): ");
  Serial.print(temperature);
  Serial.print("\tHumidity(%): ");
  Serial.println(humidity);

  // Optional: Send the data to Serial Plotter
  Serial.print(distance);
  Serial.print(",");
  Serial.print(lightIntensity);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(humidity);

  delay(1000); // Adjust delay as needed for Serial Plotter visualization
}
