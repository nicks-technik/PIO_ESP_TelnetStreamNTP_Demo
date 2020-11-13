// Careful with MOBAXTERM. The Terminal settings must be correct (e.g. cygwin with netterm100) or Windows telnet. 

#define LogOn

#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif

#include "secure.h"

#include <NtpClientLib.h>
#include <TelnetStream.h>

#include <WiFiUdp.h>
#include <myGENERAL.h>
#include <myWIFI.h>

#include <myOTA.h>

// const char *_WIFI_SSID = "SSID";         // add your "SSID";
// const char *_WIFI_Password = "PASSWORD"; // add your "WLAN-PASSWORD";

// const char *_CONST_OTA_Hostname = "my_OTA_Hostname"; // add your "my_OTA_Hostname";
// const char *_CONST_OTA_Password = "my_OTA_Password"; // add your "my_OTA_Password";

void FUNC_NTP_Log()
{
  static int _VARL_i = 0;
  TelnetStream.print(_VARL_i++);
  TelnetStream.print(" ");
  TelnetStream.print(NTP.getTimeDateString());
  TelnetStream.print(" ");
  TelnetStream.print("Uptime: ");
  TelnetStream.print(NTP.getUptimeString());
  TelnetStream.print(" since ");
  TelnetStream.println(NTP.getTimeDateString(NTP.getFirstSync()).c_str());
}


void setup()
{
  // put your setup code here, to run once:
#ifdef LogOn
  Serial.begin(115200);
  Serial.println("Logging on");
#endif

  FUNC_WIFI_Setup();

  FUNC_OTA_Setup();

  TelnetStream.begin();
  NTP.begin("pool.ntp.org", 1, false);
}

void loop()
{
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();

  switch (TelnetStream.read())
  {
  case 'R':
    TelnetStream.stop();
    delay(100);
    ESP.reset();
    break;
  case 'C':
    TelnetStream.println("bye bye");
    TelnetStream.flush();
    TelnetStream.stop();
    break;
  }

#ifdef LogOn
  Serial.print("Logged ");
  Serial.println(millis());
  delay(5000);
  FUNC_NTP_Log();
#endif
}





