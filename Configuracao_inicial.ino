void iniciacs(){

  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); //Configura parametros SPI (clock 1MHz, transferência pelo bit mais significativo e modo de SPI)


  //Run a Hardware Reset of the CS5463
  digitalWrite(PINO_CS, LOW);

  digitalWrite(RESET_PIN, LOW);
  delay (10);
  digitalWrite(RESET_PIN, HIGH);
  delay (10);

  //Inicia a porta serial
  digitalWrite(PINO_CS, LOW); //Aciona o CI
  SPI.transfer(SYNC1);
  SPI.transfer(SYNC1);
  SPI.transfer(SYNC1);
  SPI.transfer(SYNC0);
  digitalWrite(PINO_CS, HIGH);

  //delay(100);

  //--------------------------------------Escrevendo nos registradores de configuraÃ§Ã£o--------------------------------------
  // Registrador CONFIGURAÇÃO

  digitalWrite(PINO_CS, LOW);
  SPI.transfer(ESCREVER | (CONFIGURACAO << 1)); //Configura o 1º byte, |0100 0000| define comando de escrita e o endereço do registrador
  SPI.transfer(0x00); //Configura os bits do 2º byte |0000 0000| . |PC6 PC5 PC4 PC3 PC2 PC1 PC0 Igain| PC[6:0] define atraso na relação V e I. Igain define ganho do amplificador de I
  SPI.transfer(0x00); // Configura os bits do 3º byte |0000 0000| . |EWA - - IMODE IINV - - -| EWA Configura Pinos E1 e E2, IMODE e IINV Configura o Pino INT,
  SPI.transfer(0x01); //Configura os bits do 4º byte |0000 0001| . |- - - iCPU K3 K2 K1 K0| iCPU inverte a saida CPUCLK, K divisor do clock
  digitalWrite(PINO_CS, HIGH);


  //  REGISTRADOR MODO

  digitalWrite(PINO_CS, LOW);
  SPI.transfer(ESCREVER | (MODO << 1)); //Configura o 1º byte, |0110 0100| define comando de escrita e o endereço do registrador
  SPI.transfer(0x00); //Configura os bits do 2º byte, não utilizado neste registrador
  SPI.transfer(0x00); //Configura os bits do 3º byte |0000 0000| . |- - - -  - - E2MODE XVDEL| E2MODE Configura o modo de saida do pino E2
  SPI.transfer(0x61); //Configura os bits do 4º byte |0110 0001| Configura varios parametros
  digitalWrite(PINO_CS, HIGH);


  //registrador CONTROL

  digitalWrite(PINO_CS, LOW);
  SPI.transfer(ESCREVER | (CONTROL << 1)); //Configura o 1º byte, |0111 1000| define comando de escrita e o endereço do registrador
  SPI.transfer(0x00); //Configura os bits do 2º byte, não utilizado neste registrador
  SPI.transfer(0x00); //Configura os bits do 3º byte |0000 0000| . |- - - -  - - - STOP| STOP configura a sequencia de auto-boot
  SPI.transfer(0x04); //Configura os bits do 4º byte |0000 0100| . |- - - INTOD  - NOCPU NOOSC - | INTOD Configura o modo de saida do pino INT, NOCPU desativa o pino CPUCLK, NOOSC desativa o oscilador a cristal
  digitalWrite(PINO_CS, HIGH);


  //inicia os conversores ADC em modo contínuo

  digitalWrite(PINO_CS, LOW);
  SPI.transfer(INICIA_ADC);
  digitalWrite(PINO_CS, HIGH);

  digitalWrite(PINO_CS, LOW);
  SPI.transfer(ESCREVER | (P_REAL_OFF << 1)); 
  SPI.transfer(0x00); //// Escrevo o ganho de 0 na potencia ativa.
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  digitalWrite(PINO_CS, HIGH);

  
  digitalWrite(PINO_CS, LOW);
  SPI.transfer(ESCREVER | (V_GAIN<< 1)); // Escrevo o ganho de 1 na tensão.
  SPI.transfer(0x40); 
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  digitalWrite(PINO_CS, HIGH);


  
}
