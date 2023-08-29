// Library untuk mengirimkan pesan ke telegram
#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotDefines.h>
#include <CTBotInlineKeyboard.h>
#include <CTBotReplyKeyboard.h>
#include <CTBotSecureConnection.h>
#include <CTBotStatusPin.h>
#include <CTBotWifiSetup.h>
#include <Utilities.h>
#include <ArduinoJson.h>

// Library untuk WiFi
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <WiFiClient.h>

// Library untuk mengatur konfigurasi Blynk
#define BLYNK_TEMPLATE_ID "TMPLwYVDMM-7"
#define BLYNK_DEVICE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "Ev2B1iO-h22FT_3Y6xVJ6MiiXxmVwoFO"


#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Mendefinisikan token dan id dari telegram 
#define BOTtoken "2144730313:AAGo1sW__4ULdHUL4x-HF3JN8wPIBmlNZA0"
#define CHAT_ID 872190346

// Memanggil library untuk berhubungan dengan telegram
CTBot myBot;
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Elektronika";
char pass[] = "";


#define DHTPIN 15    

#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timerBlynk;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (t > 40.1 && h < 41.1) {
    myBot.sendMessage(CHAT_ID, "FIRE FIRE");

  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  // Debug console

  Serial.begin(9600);
  myBot.wifiConnect("Elektronika", "");
  myBot.setTelegramToken(BOTtoken);


  Blynk.begin(auth, ssid, pass);
  Blynk.notify("Device Started");
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();
  
  Serial.println("CLEARDATA");        //This string is defined as a 
                                      // commmand for the Excel VBA 
                                      // to clear all the rows and columns
  Serial.println("LABEL,WAKTU,TEMPERATUR,KELEMBAPAN");

  // Setup a function to be called every second
  timerBlynk.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  timerBlynk.run();
  Serial.print("DATA,TIME,");
  Serial.print(t);
  Serial.print(",");
  Serial.println(h);
  
  delay(1000);
}
