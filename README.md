# ESP32-S3 Telegram Bot Controller

This project allows you to remotely control the built-in LED of an ESP32-S3 microcontroller using a custom Telegram Bot. 

By leveraging the Telegram API, you can send commands directly from your smartphone from anywhere in the world, without needing to open ports on your home router or set up dedicated web servers. The bot features an ID-based security check, so it only responds to the authorised owner.

## 🛠️ Hardware Requirements
* **ESP32-S3 Development Board**
* LED
* 220 /sigma Resistor
* USB-C Cable for programming.
* A 2.4GHz Wi-Fi connection.

## 📚 Software & Libraries
To compile and upload the code, you need the [Arduino IDE](https://www.arduino.cc/en/software). Make sure you have the ESP32 board package installed.

You will also need to install the following libraries via the Arduino Library Manager:
1. **UniversalTelegramBot** by Brian Lough (Handles communication with the Telegram API)
2. **ArduinoJson** by Benoit Blanchon (Required by the Telegram bot library to parse messages, use version 6.x)

## 🚀 Setup Instructions

### 1. Create your Telegram Bot
1. Open Telegram and search for **@BotFather**.
2. Send the `/newbot` command and follow the instructions to get your **Bot API Token**.
3. Search for **@userinfobot** and start a chat to find your personal **Chat ID**.

### 2. Configure the Code
Open the `.ino` sketch in Arduino IDE and update the following lines with your credentials:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
#define BOT_TOKEN "YOUR_BOT_API_TOKEN"
#define CHAT_ID_AUTORIZZATO "YOUR_PERSONAL_CHAT_ID"
```
### 3.🔌 Wiring
You need a wire to connect to the LED from the second pin. Don't forget the resistor for the LED
