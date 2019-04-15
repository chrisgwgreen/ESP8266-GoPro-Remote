// Copyright [2019] <Chris GW Green>
#ifndef LIB_CONF_CONF_H_
#define LIB_CONF_CONF_H_

namespace config {
// Serial
extern int serialbaudrate;
// Network
extern const char* ssid;
extern const char* password;
extern const char* host;
extern const char* shutterUrl;
extern const char* modeUrl;
extern int port;
// Pins
extern int ledPin;
extern int buttonPin;
};  // namespace config

#endif  // LIB_CONF_CONF_H_
