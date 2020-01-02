
//----Callback do NODE-RED ------
void callback(char* topic, byte* payload, unsigned int payloadLength)
{ // Função de retorno, para controlar o ESP32 por meio da plataforma NODE-RED
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if ((char)payload[0] == '0')
  { // Se receber o caractere 0
    digitalWrite(LED, LOW);   // Desliga o LED
    Serial.println("LOW");
  }
  if ((char)payload[0] == '1')
  { // Se receber o caracter 1
    digitalWrite(LED, HIGH);  // Liga LED
    Serial.println("HIGH");
  }
}

void envia() {

 // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
     WiFi.begin(esid.c_str(), epass.c_str());  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(1000); 
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Sem Conexao......");
      lcd.setCursor(0,1); 
      lcd.print("IP:");
      lcd.setCursor(4,1); 
      lcd.print(WiFi.localIP());
    } 
      Serial.println("\nConnected.");
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print(" Reconectado ");
      lcd.setCursor(0,1); 
      lcd.print("IP:");
      lcd.setCursor(4,1); 
      lcd.print(WiFi.localIP());
      delay(2000);
  }


  timeClient.update();;//Função que executa a chamada do NTP

  if (!client.loop())
  {
    mqttConnect();      // Retorna ao inicio.
  }

  
  // ----- As String abaixo serão responsáveis por enviar mensagens ao servidor ------
  String payload = /*"{\"d\":*/"{\"ten\":";                    // Inicia Payload
  payload += tensao_RMS;                              
  payload +=",\"cor\":";
  payload += corrente_RMS;  
  payload += ",\"pat\":";  
  payload += potencia_ativa;          
  payload += ",\"pap\":";
  payload += potencia_aparente;  
  payload += ",\"pre\":";
  payload += potencia_reativa;  
  payload += ",\"fpt\":";
  payload += fator_potencia;
  payload += ",\"frq\":";
  payload += frequencia;
  payload += ",\"tmp\":";
  payload += temperatura_CI;
  payload += ",\"RSSI\":";
  payload += WiFi.RSSI();
  payload += ",\"b1\":";
  payload += b1;
  payload += ",\"b2\":";
  payload += b2;
  payload += ",\"b3\":";
  payload += b3;
  payload += ",\"tis\":\""; 
  payload += timeClient.getFormattedDate();  
  payload += "\"}"; 
 
  Serial.print("String completa: "); Serial.println(payload); // Escreve o valor no monitor serial
 client.publish(eventTopic, (char*) payload.c_str() );// Publica Payload
  //delay(100); // Aguarda 100 milissegundos
/*
 String payload1 = "{\"t\":{\"tmp\":";                 // Inicia Payload          
  payload1 += temperatura_CI;
  payload1 += "}}";  
 
  Serial.print("String Temp: "); Serial.println(payload1); // Escreve o valor no monitor serial
  client.publish(eventTopic, (char*) payload1.c_str() );// Publica Payload
 // delay(100); // Aguarda 100 milissegundos
  */                                      
}

void mqttConnect()
{ // Funções para conectar ao servidor
  if (!!!client.connected())
  { // Se não houver conexão com o servidor
    Serial.print("Reconectando ao servidor:");
    Serial.println(server);      // Indica o endereço do servidor
    
    while (!!!client.connect(clientId, authMethod, token) )
    {
      Serial.print(".");
      delay(500);
      resetpormqtt++;
      if (resetpormqtt >= 20){

        ESP.restart();
      }

      
    } 
  
    if (client.subscribe(cmdTopic))
    { // Se conseguir se Conectar ao cmdTopic
      Serial.println("OK");   // Escreve OK no monitor serial
    }
    else
    {
      Serial.println("Erro"); // Escreve erro no monitor serial
    }
  }
}
