#include <ESP32Ping.h>// https://github.com/marian-craciunescu/ESP32Ping
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ArduinoOTA.h>
#include <SPI.h> //biblioteca para comunicação SPI
#include <EEPROM.h>
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient/releases/tag/v2.3
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson/releases/tag/v5.0.7
#include "Esp32MQTTClient.h"
#include <HTTPClient.h>
#include <WebServer.h>
#include <math.h>
#include <stdint.h>
//--------------------------------------------------------
//-------- Conexão IBM-ESP32 -----------
#define ORG "tulv25" // seis primeiros caracteres do servidor 
#define DEVICE_TYPE "MULTIMEDIDOR" // Nome dado ao componente no servidor Watson
#define DEVICE_ID "RFT2019" // ID dado ao componente no servidor Watson
#define TOKEN "ymeA+_3hiEaf1CNZvX" // Insira a Chave API

//-------- Comunicação IOT --------
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
const char eventTopic[] = "iot-2/evt/status/fmt/json";
const char cmdTopic[] = "iot-2/cmd/led/fmt/json";

//----Variaveis aux para criar senha na EEPROM -----------
String tmp;
String esid;
String epass;
//--------------------------------------------------------

//----------------- Ponteiro char SSID e Senha -----------
const char* ssid = "text";
const char* passphrase = "text";
//--------------------------------------------------------

//----Variaveis usadas pela API de escrita EEPROM---------
void writeString(char add, String data);
String read_String(char add);
//--------------------------------------------------------

//----Variaveis função Millis para chamada do envio ------
unsigned long  tempo_atual = 0; //Variavel utilizada para armazenar o tempo de execucao atual do codigo
long ultimo_tempo = 0; //Variavel utilizada para armazenar o ultimo valor armazenado na variavel tempo_atual
long ultimo_tempo2 = 0;
long ultimo_tempo3 = 0;
long ultimo_tempo4 = 0;
//long desliga = 86400000‬;

//--------------------------------------------------------

//----Variaveis status da Rede ---------------------------
int statusRede;
int statusInternet;
int avg_time_ms;
bool pingstatus;

//--------------------------------------------------------
int resetpormqtt = 0;
//--------Variaveis  NTP --------------------------------
String dataNTP;
char isotime[20];
//--------------------------------------------------------
//Variaveis configuração Wifi
int i = 0;
int statusCode;
String st;
String content;
//Funções  configuração Wifi
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
//--------------------------------------------------------

enum REGS_CS5463 { //Define os endereços dos registradores do CS5463, endereços de acordo com o datasheet do componente

  //Registradores página 0 do datasheet
  CONFIGURACAO = 0, //Config
  POT_REAL = 10, // W potencia real ou ativa
  P_REAL_OFF = 14,
  TENSAO_RMS_OFF = 17,
  CORRENTE_RMS_OFF = 16,
  I_GAIN = 2,
  V_GAIN =4,
  CORRENTE_RMS = 11, //Irms
  TENSAO_RMS = 12, //Vrms
  MODO = 18, //configuração da saida E3
  POT_REATIVA = 24, //Var
  FATOR_POTENCIA = 25,
  POT_APARENTE = 27, //VA
  CONTROL = 28,
  TEMPERATURE = 19,  // Temperatura
  POTENCIA_ATIVA_HARMONICA = 29,  //Potência ativa harmônica
  EPSILON =  13, // Taxa de frequência de linha para taxa de palavra de saída (OWR)
  POTENCIA_ATIVA_FUNDAMENTAL = 30,  //Potência ativa Fundamental
  POTENCIA_REATIVA_FUNDAMENTAL = 31,  //Potência reativa Fundamental
  //Comandos
  LEITURA = 0,
  ESCREVER = 64,
  SYNC0 = 254,
  SYNC1 = 255,
  INICIA_ADC = 232, //1110 1000 Inicia os conversores ADC em modo continuo
};

int PINO_CS = 5; //define o pino 5 como seleçãoo do CI (chip select)
const int RESET_PIN = 4; 

//variáveis de leitura
unsigned long resut;
double  Tensao;
double  Corrente;
double P_Real;
double P_Reativa;
double  P_Aparente;
double FP;
double P_OFF;
double T_OFF;
double C_OFF;
double I_GAIN_DOUBLE;
double V_GAIN_DOUBLE;
unsigned long Temperatura;
unsigned long P_Real_Harmonica;
signed long Freq_Epsilon;
signed long P_Real_Fundamental;
signed long P_Reativa_Fundamental;
String FP_tipo;
//variáveis para o display, botão e SD
int contador = 0;
int var_aux_botao = 0;
int var_aux_botao1 = 0;
int var_aux_botao2 = 0;
int layer = 0;
int limpar = 0;
int botao = 14;
int botao1 = 27;
volatile bool botaoFlag = false;
volatile bool botao1Flag = false;
int LED = 2;                // Led D2 do ESP32

int WhichScreen =1;   // This variable stores the current Screen number
boolean hasChanged = true;

//variáveis dos relés
int banco1 = 25;//verde
int banco2 = 32;// Amarelo 
int banco3 = 33;// Laranja
int b1 = 1;
int b2 = 1;
int b3 = 1;

//Variaveis para postagem

String tensao_RMS;
String corrente_RMS;
String potencia_ativa;
String potencia_reativa;
String potencia_aparente;
String fator_potencia;
String frequencia;
String temperatura_CI;
String potencia_reativa_fundamental;
String potencia_ativa_fundamental;
//Tempo entre Post
float tmppost = 5000;
double millis_aciona_bancos;

//----------------Valores de Calibração---------------------------------

#define M_Tensao 0.041855129
#define M_Corrente 0.0174392936
#define M_P_Real 9.047619048
#define M_P_Reativa 9.047619048
#define M_P_Aparente 9.047619048
#define M_FP 0.0001
#define M_Temperatura 1 // 0.00001070665988815460
#define M_P_Real_Harmonica 0.001
#define M_Frequencia 0.392156862
//---------------------------------------Construtores------------------------------------------
WebServer servidor(80);
WiFiClient wifiClient; 
void callback(char* topic, byte* payload, unsigned int payloadLength);
PubSubClient client(server, 1883, callback, wifiClient); 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", 0, 5000);
// (UDp, poolServerName, timeOffset,tempo de atualização em ml
//https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
LiquidCrystal_I2C lcd(0x27, 20, 4);
//---------------------------------------------------------------------------------------------

void setup() {

  //Inicia o WiFi

  WiFi.mode(WIFI_STA);
  client.setCallback(callback);
  
  pinMode(LED, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);  //initalize the RESET pin;
  pinMode (PINO_CS, OUTPUT); //Define o pino 5 como saída para selecionar o CI
  pinMode(botao, INPUT); // botão que configura Wifi 
  pinMode(botao1, INPUT);// botão que muda o menu 
  pinMode(banco1, OUTPUT);
  pinMode(banco2, OUTPUT);
  pinMode(banco3, OUTPUT);
  digitalWrite (PINO_CS, HIGH); //Define o pino 10 como nível alto para manter CI desativado
  digitalWrite(banco1, HIGH);
  digitalWrite(banco2, HIGH);
  digitalWrite(banco3, HIGH);

  millis_aciona_bancos = 0;
  /*
  Define quando a interrupção será acionada.
  Abaixo seguem as constantes predefinidas:
  LOW : aciona a interrupção sempre que o pino estiver baixo.
  CHANGE: aciona a interrupção sempre que o pino muda de estado.
  RISING: aciona a interrupção quando o pino vai de baixo para alto (LOW > HIGH).
  FALLING: para acionar a interrupção quando o pino vai de alto para baixo (HIGH > LOW)
  HIGH : aciona a interrupção sempre que o pino estiver alto.
  */
  attachInterrupt(botao, interrupcaoWifi,FALLING);
  attachInterrupt(botao1, interrupcaodisplay,FALLING);

  
  Serial.begin(115200);
  Serial.println("Multimedidor de Energia IoT");

  iniciacs();

  EEPROM.begin(512);
 
  iniciawifi();

}


void loop() {

    if (botaoFlag) {
        escrever_display();
    }


    if (botao1Flag) {
        configwifi();
    }

  ArduinoOTA.handle();

  VerificaModo();
  /*
  Serial.print("tempo em millis ");
  Serial.print(tempo_atual);
  if(tempo_atual > desliga ){

    ESP.restart(); //Reinicia a cada 24 horas para limpar as variveis. 
  }
*/
}
