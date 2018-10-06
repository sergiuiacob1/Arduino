#include "ESP8266WiFi.h"
#include "DHT.h"
#include <ESP8266HTTPClient.h>
#include "api.h"
#include "button_presser.h"
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>

#define DHTPIN 2 //D4 on esp board
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClient wifi;

const char WEBSITE[] = "api.thingspeak.com"; //pushingbox API server
const String devid = "vE0CFDB90366C49E"; //device ID from Pushingbox
const char* MY_SSID = "DIGI_6ea2d0";
const char* MY_PWD =  "3ff0915d";
int _targetTemperature = 23;

void getTargetTemp();

void setup()
{
  Serial.begin(115200);
  dht.begin();
  Serial.print("Connecting to " + *MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) //not connected,..waiting to connect
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("Credentials accepted! Connected to wifi\n ");
  Serial.println("");
}

void loop()
{
  postData();
  delay (5000);
  return;

  String request;
  String parameters;

  float humidityData = dht.readHumidity();
  float celData = dht.readTemperature();

  if (isnan(humidityData) || isnan(celData))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //Print to Serial monitor or Terminal of your chocice at 115200 Baud
  Serial.print("Humidity: ");
  Serial.print(humidityData);
  Serial.print(" %\t");
  Serial.print("Temperature in Cel: ");
  Serial.print(celData);
  Serial.println(" *C");

  WiFiClient client;  //Instantiate WiFi object

  //Start or API service using our WiFi Client through PushingBox
  if (client.connect(WEBSITE, 80))
  {
    parameters = "api_key=6OURMUW6NIIMYABB&field1=" + (String) humidityData
                 + "&field2=" + (String) celData;

    request = "GET /update?" + parameters + " HTTP/1.1\r\nHost: " + WEBSITE + "\r\nUser-Agent: ESP8266/1.0\r\nConnection: close\r\n\r\n";
    client.print (request);
    Serial.print (request);

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    // Read all the lines of the reply from server and print them to Serial
    while (client.available() || client.connected()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
  }
  else {
    Serial.println("Push to pushingbox failed");
  }
  delay(60000); //10 seconds, (sampling rate vs. service call quota)
}

void postData() {
  String request;
  float humidityData = dht.readHumidity();
  float celData = dht.readTemperature();
  String response;
  int statusCode = 0;

  request = "/update?api_key=6OURMUW6NIIMYABB&field1=" + (String) humidityData
            + "&field2=" + (String) celData;

  HttpClient client = HttpClient(wifi, "api.thingspeak.com", 80);
  client.get(request);
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}

void getTargetTemp() {
  String response;
  int statusCode = 0;
  HttpClient client = HttpClient(wifi, "api.thingspeak.com", 80);
  client.get("/channels/596590/feeds.json?results=2");
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
