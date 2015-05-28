/**
  * Sifirdan 9'a kadar rakamlari tanimlayalim.
  * 8 bitlik sayinin her biti bir ledi isaret edecek
  */
const byte rakamlar[11] = {
   B1111110,  // 0
   B0110000,  // 1
   B1101101,  // 2
   B1111001,  // 3
   B0110011,  // 4
   B1011011,  // 5
   B1011111,  // 6
   B1110000,  // 7
   B1111111,  // 8
   B1110011,  // 9
   B0000000,   // bos
   };

/**
  * ledi bagladigimiz pinleri tamilayalim
  */
                    // g,f,e,d,c,b,a    
const int pinler[7] = {8,7,6,5,4,3,2}; 

//pinleri cikisa yonlendirelim
void setup() {
  for(int i=2;i<=9;i++)
    pinMode(i, OUTPUT);  
}

/*
 * dongu sifirdan 9'a kadar rakamlari dongu icinde gosterelim.
 */
void loop() {
  for (int i = 0; i <= 10; i++) {
   delay(1000);
   showDigit(i); 
  }
  delay(4000);
}

void showDigit(int n) {
  boolean bitVal;
  //Gosterilecek rakamin segmentlerini dongu icinde kontrol edelim.
  for (int segment=0 ; segment<7; segment++) {
    //Segment bit degerini alalim.  
    bitVal = bitRead(rakamlar[n],segment);
    //Bit degerine gore segmenti yakalim.
    digitalWrite(pinler[segment],bitVal);
  }
}
