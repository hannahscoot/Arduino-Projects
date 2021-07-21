#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "arduino_secrets.h"

// Wifi network station credentials
#define WIFI_SSID SECRET_SSID
#define WIFI_PASSWORD SECRET_PASSWORD
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN SECRET_BOT_TOKEN
#define CHAT_ID SECRET_CHAT_ID

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

const int sensor = 27; // PIR Motion Sensor
const int led = 2; //Onboard LED
int state = LOW;
int val = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {
  val = digitalRead(sensor);
  if (val == HIGH) {
    digitalWrite(led, HIGH);
    delay(100);
    if (state == LOW) {
      Serial.println("Motion Detected");
      state = HIGH;
      bot.sendMessage(CHAT_ID, "Motion detected!!", "");
    }
  }
  else {
      digitalWrite(led, LOW);
      delay(200);
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        bot.sendMessage(CHAT_ID, "Motion stopped!!", "");
        state = LOW;
    }
  }
}
