//Convert a pulse length in milliseconds to the equivalent in bits
uint16_t pulseLength_to_bitLength(double pLen){

  double scale = 1000000; //1,000,000 us per second
  scale /= freq;          //scale * Period
  scale /= 4096;          //12 bit resolution: us per bit
  
  pLen *= 1000;           //convert ms input to us

  pLen /= scale;          //convert to bitLength us/(us/bit) = bit
  
  return pLen;
  
}
