void interrupcaoWifi(){
  botaoFlag = true;
}

void configwifi(){
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0); 
    lcd.print("Configuracao WIFI");
    launchWeb();
    setupAP();// Setup HotSpot
        while ((WiFi.status() != WL_CONNECTED))
        {
          Serial.print(".");
          delay(100);
          servidor.handleClient();
        }
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0); 
    lcd.print("Configuracao");
    lcd.setCursor(0,1); 
    lcd.print("Concluida");
    lcd.setCursor(0,2); 
    lcd.print("Conectado na Rede");
    lcd.setCursor(0,3); 
    lcd.print(esid);
    botao1Flag = false;
    delay(2000);
  }


void iniciawifi(){
    esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");

  epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);


  WiFi.begin(esid.c_str(), epass.c_str());

    Serial.println("Iniciando a conexão ");
    delay(1000);
    lcd.begin();
    lcd.backlight();
  
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Sem Conexao.....");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    lcd.setCursor(0, 2);
    lcd.print("Ao Iniciar precione");
    lcd.setCursor(0, 3);
    lcd.print("o botao configurar");
    WiFi.begin(esid.c_str(), epass.c_str());
    delay(2000);
    loop();
  }
  else {
    startOTA();
    ArduinoOTA.begin();
    mqttConnect();
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Conectado na Rede");
    lcd.setCursor(0, 1);
    lcd.print(esid.c_str());
    lcd.setCursor(0, 2);
    lcd.print("IP:");
    lcd.setCursor(4, 2);
    lcd.print(WiFi.localIP());
    timeClient.begin();
    timeClient.setTimeOffset(-10800);
    pingstatus = Ping.ping("www.google.com");
    WhichScreen = 1;
  }


}

bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  servidor.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);

    st += ")";
    st += (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("ESP32 Wifi setup", "12345678");//ESP32 Network Name
  Serial.println("softap");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
 {
    servidor.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP32 at ";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      content += "</html>";
      servidor.send(200, "text/html", content);
    });
    servidor.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html>go back";
      servidor.send(200, "text/html", content);
    });

    servidor.on("/setting", []() {
      String qsid = servidor.arg("ssid");
      String qpass = servidor.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");

        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();

        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        ESP.restart();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      servidor.sendHeader("Access-Control-Allow-Origin", "*");
      servidor.send(statusCode, "application/json", content);

    });
  } 
}
