
 void VerificaModo(){
  
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(esid.c_str(), epass.c_str());
    statusRede = 0;
    statusInternet = 0;
    delay(2000);
  }
  else {
    statusRede = 1;
  }
   if (statusRede == 0){
   ModoOff();
   }
  if (statusRede == 1){
      if (tempo_atual - ultimo_tempo4 >= 10000 ) //verifica o ping a cada 60 segundos
    {
       ultimo_tempo4 = tempo_atual;
       pingstatus = Ping.ping("www.google.com");
     }
  
  if (!pingstatus) 
  {
    
    ModoOff();
    statusInternet = 0;


  }
  if (pingstatus) 
  {
   
    //Fluxo Online.
    ArduinoOTA.handle();
    ModoOn();
    statusInternet = 1;

  }

  }
  tempo_atual = millis();
}


void ModoOn(){   

    if (tempo_atual - ultimo_tempo >= 1000) //Verifica se o tempo é  maior que 2 segundos, referenciado com o ultimo tempo salvo e chama as funções de leitura do CI e Impressão.
    {
       ultimo_tempo = tempo_atual;//5000

       leituras();
       escrever_display();
       //controle_bancos();
       //imprimirserial();

    }
             
    if (tempo_atual - ultimo_tempo2 >= tmppost ) //Verifica se o tempo é  maior que 20 segundos, referenciado com o ultimo tempo salvo e chama a função envio.
    {
       ultimo_tempo2 = tempo_atual;//5000
       envia();
       
     }
}

void ModoOff(){    
    if (tempo_atual - ultimo_tempo >= 2000) //Verifica se o tempo é  maior que 2 segundos, referenciado com o ultimo tempo salvo e chama as funções de leitura do CI e Impressão.
    {
       ultimo_tempo = tempo_atual;//5000

       leituras();
       escrever_display();
       //controle_bancos();
     //  imprimirserial();

    }
}
