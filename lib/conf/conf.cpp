// Copyright [2019] <Chris GW Green>
namespace config {
// Serial
int serialbaudrate = 115200;

// Network
const char* ssid = "goprohero";
const char* password = "goprohero";

// GoPro 
const char* host = "10.5.5.9";
int port = 8080;
const char* shutterUrl = "/gp/gpControl/command/shutter?p=";
const char* modeUrl = "/gp/gpControl/command/mode?p=0";

// Pins
int ledPin = 0;
int buttonPin = 2;
}  // namespace config
