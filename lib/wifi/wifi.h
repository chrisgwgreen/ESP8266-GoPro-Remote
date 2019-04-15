// Copyright [2019] <Chris GW Green>
#include <string>

#ifndef LIB_WIFI_WIFI_H_
#define LIB_WIFI_WIFI_H_

class wifiClass {
 private:
  const char* ssid;
  const char* password;
  const char* host;
  const char* url;
  const char* fingerprint;
  int port;
  bool isSecure;

 public:
  wifiClass();
  void init(void (*ptr)());
  bool shutterRelease(bool isReleased);
  bool setVideoMode();
  bool sendCommand(std::string url);
};

#endif  // LIB_WIFI_WIFI_H_
