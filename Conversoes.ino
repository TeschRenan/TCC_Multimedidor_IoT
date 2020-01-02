  long MSB_Mask = 0x800000;  

int32_t unsigned2bintype1(int32_t val)
{
  val = val*0.000596046; //Valor decimal =  [ 1 / ( 2^24 - 1) ] x Hexto Dec ( Valor Hexadecimal) 
  return val;                                                      //Valor multiplicado por 10000   
}

int32_t unsigned2bintype2(int32_t val)
{
  val = val*0.00119209303761638; //Valor decimal =  [ 1 / ( 2^23 - 1) ] x Hexto Dec ( Valor Hexadecimal) 
  return val;                                                      //Valor multiplicado por 10000   
}

int32_t signed2binpoint(int32_t val){

int32_t returnvalue;

    if ((val & MSB_Mask) == 0)                  // Verifying if MSB Bit equals Zero
  {
  returnvalue = ((val * 0.00000011920930376)*10000);        // two's complement notation ( 2^23 - 1) = 8388607
  return returnvalue;
  }
  else                                              // if MSB Bit equals One
  {
    returnvalue = val - 0x800000;                   // Remove MSB bit   
    returnvalue = ((returnvalue  * 0.00000011920930376) - 1)*10000 ;  // {[1/(2^23 - 1)] x HexToDec(Value Hexadecimal)} - MSB
    return returnvalue;
  }
}

int32_t signed3binpoint(int32_t val){  //Convert Temperature Register
  long HexaValue;
  float HexaFloat;
  long H_Byte;                 // High Byte 
  int32_t returnvalue;

  String StringHexa = String(val,HEX);        // converts Hexa to String 

  H_Byte = val >> 16;
  HexaFloat = val & 0x00FFFF ;   
  
  if ((val & MSB_Mask) == 0)                                 // Verifying if MSB Bit equals Zero
  {
    returnvalue = H_Byte + (HexaFloat/65535) ;             // two's complement notation ( 2^16 - 1) = 65535
    
    return returnvalue;
  }
  else                                                            // if MSB Bit equals One ( - 128) 
  {
    H_Byte = H_Byte - 128 ;                                      // Remove MSB Bit 
    returnvalue = (H_Byte + (HexaFloat/65535)) - 128 ;    // {[1/(2^16 - 1)] x HexToDec(Value Hexadecimal)} 
    
    return returnvalue;
  }

  }
