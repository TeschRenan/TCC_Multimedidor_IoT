
int leituras(){ //função que realiza as leituras das grandezas

  unsigned long MSB;
  unsigned long H_Byte;
  unsigned long M_Byte;
  unsigned long L_Byte;
//----------------------------------------------------lendo registradores-------------------------------------------------------
//----------------------------------------------------leitura da tensão RMS----------------------------------------------------

digitalWrite(PINO_CS, LOW);
//delay(2000);
SPI.transfer(LEITURA | (TENSAO_RMS<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

Tensao = unsigned2bintype1(((H_Byte<<16)|(M_Byte<<8)|(L_Byte))); //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 


//----------------------------------------------------leitura do offset da tensão (W)----------------------------------------------------
/*
digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (TENSAO_RMS_OFF<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

uint32_t T_OFF_int = ((H_Byte<<16)|(M_Byte<<8)|(L_Byte)); //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 

T_OFF = signed2float(T_OFF_int)*1000;

Serial.println("T_OFF");
Serial.println(T_OFF);

Serial.println("T_OFF");
Serial.println(T_OFF);
                                 

//----------------------------------------------------leitura do ganho de corrente RMS----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (V_GAIN<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);


//Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal)
uint32_t V_GAIN_int = (H_Byte<<16)|(M_Byte<<8)|(L_Byte); //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 

V_GAIN_DOUBLE = unsigned2float(V_GAIN_int)*1000;

Serial.println("V_GAIN");
Serial.println(V_GAIN_DOUBLE);
                                  
                                                             
//----------------------------------------------------leitura da corrente RMS----------------------------------------------------
*/
digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (CORRENTE_RMS<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

Corrente = unsigned2bintype1(((H_Byte<<16)|(M_Byte<<8)|(L_Byte))); 

//----------------------------------------------------leitura do offset da Corrente (W)----------------------------------------------------
/*
digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (CORRENTE_RMS_OFF<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

uint32_t C_OFF_int = ((H_Byte<<16)|(M_Byte<<8)|(L_Byte)); //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 

C_OFF = signed2float(C_OFF_int)*1000;

Serial.println("C_OFF");
Serial.println(C_OFF);
//----------------------------------------------------leitura do ganho de corrente RMS----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (I_GAIN<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);


//Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal)
uint32_t I_GAIN_int = (H_Byte<<16)|(M_Byte<<8)|(L_Byte); //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 

I_GAIN_DOUBLE = unsigned2float(I_GAIN_int)*1000;

Serial.println("I_GAIN");
Serial.println(I_GAIN_DOUBLE);
   */                                                          
//----------------------------------------------------leitura da potência real (W)----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (POT_REAL<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

P_Real = signed2binpoint((H_Byte<<16)|(M_Byte<<8)|(L_Byte)); //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 


//----------------------------------------------------leitura do offset da potência real (W)----------------------------------------------------
/*
digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (P_REAL_OFF<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

uint32_t P_OFF_int = ((H_Byte<<16)|(M_Byte<<8)|(L_Byte)); //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 

P_OFF = signed2float(P_OFF_int);

Serial.println("P_OFF");
Serial.println(P_OFF);

*/
//----------------------------------------------------leitura da potência reativa----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (POT_REATIVA<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

P_Reativa = unsigned2bintype2(((H_Byte<<16)|(M_Byte<<8)|(L_Byte))); //Valor decimal = [ 1 / ( 2^23 - 1) ] x Hexto Dec ( Valor Hexadecimal) 

if (P_Reativa>19999){
  P_Reativa  = 0;  //Parametro para apenas quando o sistema está sem tensão e corrente onde o mesmo gera uma saida igual a 20000
}
 
//----------------------------------------------------leitura da potência aparente----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (POT_APARENTE<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

 P_Aparente = unsigned2bintype2(((H_Byte<<16)|(M_Byte<<8)|(L_Byte)));
                                                                    
//----------------------------------------------------leitura do fator de potência----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (FATOR_POTENCIA<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

FP = signed2binpoint((H_Byte<<16)|(M_Byte<<8)|(L_Byte)); 

if (FP*M_FP > 1){
  FP = -1;
  FP_tipo = "CAP";
}
else{
  FP_tipo = "IND";
}

//----------------------------------------------------leitura da Temperatura----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (TEMPERATURE<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

Temperatura = signed3binpoint((H_Byte<<16)|(M_Byte<<8)|(L_Byte));

//----------------------------------------------------leitura da Potencia ativa Harmonica ----------------------------------------------------
/*
digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (POTENCIA_ATIVA_HARMONICA<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);


P_Real_Harmonica = (H_Byte<<16)|(M_Byte<<8)|(L_Byte);
MSB = P_Real_Harmonica&0b100000000000000000000000; //mascara para identificar o valor do MSB

if(MSB==0){
  FP = (P_Real_Harmonica*0.00119209303761638); // OBS.: 1/(2^23 - 1) foi multiplicado por 10000
}

else {
  FP = (((P_Real_Harmonica&0b011111111111111111111111)*0.00000011920930376)-1)*10000; //mascara para excluir o bit MSB, 
}

*/

//----------------------------------------------------leitura da Frequencia (Epsilon) ----------------------------------------------------
digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (EPSILON<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);

Freq_Epsilon = signed2binpoint(((H_Byte<<16)|(M_Byte<<8)|(L_Byte)));


//----------------------------------------------------leitura da potência Ativa Fundamental----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (POTENCIA_ATIVA_FUNDAMENTAL<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);


P_Real_Fundamental = (H_Byte<<16)|(M_Byte<<8)|(L_Byte);
MSB = P_Real_Fundamental&0b100000000000000000000000; //mascara para identificar o valor do MSB

if(MSB==0){
  P_Real_Fundamental = (P_Real_Fundamental*0.00119209303761638); // OBS.: 1/(2^23 - 1) foi multiplicado por 10000
}

else {
  P_Real_Fundamental = (((P_Real_Fundamental&0b011111111111111111111111)*0.00000011920930376)-1)*10000; //mascara para excluir o bit MSB, 
}

//----------------------------------------------------leitura da potência Reativa Fundamental----------------------------------------------------

digitalWrite(PINO_CS, LOW);
SPI.transfer(LEITURA | (POTENCIA_REATIVA_FUNDAMENTAL<<1));
H_Byte = SPI.transfer(SYNC1);
M_Byte = SPI.transfer(SYNC1);
L_Byte = SPI.transfer(SYNC1);
delayMicroseconds(10);
digitalWrite(PINO_CS, HIGH);
 

P_Reativa_Fundamental = (H_Byte<<16)|(M_Byte<<8)|(L_Byte);
MSB = P_Reativa_Fundamental&0b100000000000000000000000; //mascara para identificar o valor do MSB

if(MSB==0){
  P_Reativa_Fundamental = (P_Reativa_Fundamental*0.00119209303761638); // OBS.: 1/(2^23 - 1) foi multiplicado por 10000
}

else {
  P_Reativa_Fundamental = (((P_Reativa_Fundamental&0b011111111111111111111111)*0.00000011920930376)-1)*10000; //mascara para excluir o bit MSB, 
}


 tensao_RMS = Tensao*M_Tensao;;
 corrente_RMS = Corrente*M_Corrente;
 potencia_aparente =  P_Aparente*M_P_Aparente;
 potencia_ativa = P_Real*M_P_Real;
 potencia_reativa = P_Reativa*M_P_Reativa;
 fator_potencia = FP*M_FP;
 frequencia = Freq_Epsilon*M_Frequencia;
 temperatura_CI = Temperatura*M_Temperatura;
 potencia_reativa_fundamental = P_Reativa_Fundamental*M_P_Reativa;
 potencia_ativa_fundamental = P_Real_Fundamental*M_P_Real;



}
