
void interrupcaodisplay(){
  botao1Flag = true;
}



//----------------------------------------------------Escrevendo status da rede ----------------------------------------------------
void conexaodisplay(){
 lcd.clear();
  lcd.setBacklight(HIGH); //acende a luz de fundo do display
  lcd.setCursor(0,0); 
  lcd.print("IP:");
  lcd.setCursor(4,0); 
  lcd.print(WiFi.localIP());
  lcd.setCursor(0,1); 
  lcd.print("REDE:");
  lcd.setCursor(8,1); 
  lcd.print(statusRede);
  lcd.setCursor(0,2); 
  lcd.print("INTERNET:");
  lcd.setCursor(11,2); 
  lcd.print(statusInternet);
  lcd.setCursor(0,3);
  lcd.print("PING:");
  lcd.setCursor(7,3); 
  lcd.print(avg_time_ms);
}

//----------------------------------------------------Escrevendo as grandezas no display----------------------------------------------------

  void escrever_display(){
      // only toggle the LED if the new button state is HIGH
      if (botaoFlag == true) {
       // hasChanged = true;
        WhichScreen++;   
      }
     //else {
     // hasChanged = false;
    //  }
    if (WhichScreen > 4){
    WhichScreen = 1;
  }

//  if (hasChanged == true) {
  
  switch(WhichScreen) {
    case 1:
    {
      firstScreen();
    }
      break;
   
    case 2:
      {
        secondScreen();
      }
      break;
   
    case 3:
      {
        thirdScreen();
      }
      break;
      
      case 0:
      {
       
      }
      break;
    }
//}
  
      botaoFlag = false;
}
 
 

 
void firstScreen()
  {
  lcd.clear();
  lcd.setBacklight(HIGH); //acende a luz de fundo do display
  lcd.setCursor(0, 0); //posiciona o cursor coluna 7 linha 0
  lcd.print("U:");
  lcd.print(Tensao * M_Tensao);
  lcd.print("V");
  lcd.print(" ");
  lcd.setCursor(11, 0);
  lcd.print("I:");
  lcd.print(Corrente * M_Corrente);
  lcd.print("A");
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(P_Real * M_P_Real);
  lcd.print("W");
  lcd.print(" ");
  lcd.setCursor(13, 1);
  lcd.print("FP:");
  lcd.print(FP * M_FP);
  lcd.print(" ");
  lcd.setCursor(0, 2);
  lcd.print("Q:");
  lcd.print(P_Reativa * M_P_Reativa);
  lcd.print("VAr");
  lcd.print("   ");
  lcd.setCursor(16, 2);
  lcd.print(FP_tipo);
  lcd.setCursor(0, 3);
  lcd.print("S:");
  lcd.print(P_Aparente * M_P_Aparente);
  lcd.print("VA");
  lcd.print("   ");
  }
void secondScreen()
  {
  lcd.clear();
  lcd.setBacklight(HIGH); //acende a luz de fundo do display
  lcd.setCursor(3,0);
  lcd.print("Bancos Ativos:");
    if (b1==1){
    lcd.setCursor(0,2);
    lcd.print("B1");
    }
    else{
    lcd.setCursor(0,2);
    lcd.print("  ");
    }

    if (b2==1){
    lcd.setCursor(3,2);
    lcd.print("B2");
    }
    else{
    lcd.setCursor(3,2);
    lcd.print("  ");
    }
    if (b3==1){
    lcd.setCursor(6,2);
    lcd.print("B3");
    }
    else{
    lcd.setCursor(6,2);
    lcd.print("  ");
    }
  }
void thirdScreen()
  {
   lcd.clear();
   lcd.setBacklight(HIGH); //acende a luz de fundo do display
   lcd.setCursor(0,0); 
              lcd.print("IP:");
              lcd.setCursor(4,0); 
              lcd.print(WiFi.localIP());
              lcd.setCursor(0,1); 
              lcd.print("REDE:");
              lcd.setCursor(8,1); 
              if (statusRede = 1){
              lcd.print("ON");
              }
              else if (statusRede = 0){
              lcd.print("OFF");
              }
              lcd.setCursor(0,2); 
              lcd.print("INTERNET:");
              lcd.setCursor(11,2); 
              if (statusInternet = 1){
              lcd.print("ON");
              }
              else if (statusInternet = 0){
              lcd.print("OFF");
  }
  }
