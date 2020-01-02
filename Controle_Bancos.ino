void controle_bancos(){
//Verificação para manter os bancos ligados
     if ((Corrente * M_Corrente) < 1 ){
      digitalWrite(banco1, HIGH);
      digitalWrite(banco2, HIGH);
      digitalWrite(banco3, HIGH);
      Serial.println("Banco de capacitores desativado corrente baixa");
  
     }
    
    if (((Corrente * M_Corrente) > 1 ) && (millis_aciona_bancos + 10000) < millis()){
       
       millis_aciona_bancos = millis();


      if(((FP*M_FP)>=0.92)&& b3 == 1){
      digitalWrite(banco1, HIGH);
      digitalWrite(banco2, HIGH);
      digitalWrite(banco3, LOW);
      Serial.println("Desativa Banco 3");
      b1 = 0;
      b2 = 0;
      b3 = 1;
    }
     else if(((FP*M_FP)>=0.92)&& b2 == 1){
      digitalWrite(banco1, HIGH);
      digitalWrite(banco2, LOW);
      digitalWrite(banco3, HIGH);
      Serial.println("Desativa Banco 2");
      b1 = 0;
      b2 = 1;
      b3 = 0;
    }
     else if(((FP*M_FP)>=0.92)&& b1 == 1){
      digitalWrite(banco1, LOW);
      digitalWrite(banco2, HIGH);
      digitalWrite(banco3, HIGH);
      Serial.println("Desativa Banco 1");
      b1 = 1;
      b2 = 0;
      b3 = 0;
    }
    else{
      aciona_bancos();
      
    }  
        
      Serial.println("Bancos Ativos:");
      Serial.println(b1);
      Serial.println(b2);
      Serial.println(b3);
    
}
   

}


int aciona_bancos(){

  Serial.print("Logica de controle de FP");

      if(((FP*M_FP)>=0.92)){
      digitalWrite(banco1, HIGH);
      digitalWrite(banco2, HIGH);
      digitalWrite(banco3, HIGH);
      Serial.println("Bancos desativado");
      b1 = 0;
      b2 = 0;
      b3 = 0;
    }

    if(((FP*M_FP)<0.92) &&  ((FP*M_FP)>=0.87)){
      digitalWrite(banco1, LOW);
      digitalWrite(banco2, HIGH);
      digitalWrite(banco3, HIGH);
      Serial.println("Ativa Banco 1");
      b1 = 1;
      b2 = 0;
      b3 = 0;
    }

    if(((FP*M_FP)<0.87) &&  ((FP*M_FP)>=0.8)){
      digitalWrite(banco1, HIGH);
      digitalWrite(banco2, LOW);
      digitalWrite(banco3, HIGH);
      Serial.println("Ativa Banco 2");
      b1 = 0;
      b2 = 1;
      b3 = 0;
    }
        if(((FP*M_FP)<0.8)){
      digitalWrite(banco1, HIGH);
      digitalWrite(banco2, HIGH);
      digitalWrite(banco3, LOW);
      Serial.println("Ativa Banco 3");
      b1 = 0;
      b2 = 0;
      b3 = 1;
    }  
     
   }
