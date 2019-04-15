// Copyright [2019] <Chris GW Green>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <wifi.h>
#include <string.h>
#include <conf.h>

wifiClass::wifiClass() {
  ssid = config::ssid;
  password = config::password;
  host = config::host;
  port = config::port;
}

void wifiClass::init(void (*connectingBlink)()) {
  Serial.print("Connecting to ");
  Serial.println(wifiClass::ssid);

  WiFi.begin(wifiClass::ssid, wifiClass::password);

  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    delay(500);
    Serial.print(".");
    (*connectingBlink) ();
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected");
    ESP.deepSleep(1000000e6);
  } else {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool wifiClass::shutterRelease(bool isReleased) {
  std::string shutterUrl = config::shutterUrl;

  if (isReleased) {
    shutterUrl += "1";
  } else {
    shutterUrl += "0";
  }

  return sendCommand(shutterUrl);
}

bool wifiClass::setVideoMode() {
  return sendCommand(config::modeUrl);
}

bool wifiClass::sendCommand(std::string url) {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return false;
  }

  client.print("GET ");
  client.print(url.c_str());
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close\r\n\r\n");
 
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 15000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return false;
    }
  }

  bool isSuccess = false;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.println(line);  // See response...
    if (line.indexOf("{}") > -1 && !isSuccess) {
      isSuccess = true;
    }
  }

  client.stop();

  return isSuccess;
}
