#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// ==========================================
// 1. ADD YOUR DATA
// ==========================================
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
#define BOT_TOKEN "YOUR_BOT_API_TOKEN"
#define CHAT_ID_AUTORIZZATO "YOUR_PERSONAL_CHAT_ID"

// ==========================================
// 2. BOT & HARDWARE CONFIGURATION
// ==========================================
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

int intervalloControllo = 1000; 
unsigned long ultimoControllo = 0;

const int pinLed = 2; 

// ==========================================
// 3. INCOMING MESSAGES
// ==========================================
void gestisciMessaggi(int numeroNuoviMessaggi) {
  for (int i = 0; i < numeroNuoviMessaggi; i++) {
    String chat_id = bot.messages[i].chat_id;
    String testo = bot.messages[i].text;

    // --- SECURITY CHECK ---
    if (chat_id != CHAT_ID_AUTORIZZATO) {
      bot.sendMessage(chat_id, "Accesso negato. Non sei autorizzato.", "");
      Serial.println("Tentativo di accesso bloccato da ID: " + chat_id);
      continue; 
    }

    Serial.print("Messaggio ricevuto: ");
    Serial.println(testo);
    String tastiera = "[[\"/accendi\", \"/spegni\"]]";

    // --- EXECUTION ---
    if (testo == "/accendi") {
      digitalWrite(pinLed, HIGH);
      bot.sendMessageWithReplyKeyboard(chat_id, "LED acceso! 💡", "", tastiera, true);
    } 
    else if (testo == "/spegni") {
      digitalWrite(pinLed, LOW);
      bot.sendMessageWithReplyKeyboard(chat_id, "LED spento! 🌑", "", tastiera, true);
    } 
    else if (testo == "/start") {
      String benvenuto = "Benvenuto nel tuo ESP32! Scegli un'azione dai pulsanti qui sotto 👇";
      bot.sendMessageWithReplyKeyboard(chat_id, benvenuto, "", tastiera, true);
    }
    else {
      bot.sendMessage(chat_id, "Usa i pulsanti per controllare il LED.", "");
    }
  }
}

// ==========================================
// 4. SETUP
// ==========================================
void setup() {
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW); 
  Serial.print("\nConnessione al WiFi");
  WiFi.begin(ssid, password);

  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connesso! Indirizzo IP: " + WiFi.localIP().toString());
  Serial.println("Bot avviato e in ascolto...");
}

// ==========================================
// 5. PRINCIPAL CYCLE
// ==========================================
void loop() {
  // Controlla la presenza di nuovi messaggi su Telegram in base all'intervallo
  if (millis() - ultimoControllo > intervalloControllo) {
    int nuoviMessaggi = bot.getUpdates(bot.last_message_received + 1);
    
    while (nuoviMessaggi) {
      gestisciMessaggi(nuoviMessaggi);
      nuoviMessaggi = bot.getUpdates(bot.last_message_received + 1);
    }
    ultimoControllo = millis();
  }
  
  // You can add other code
}
