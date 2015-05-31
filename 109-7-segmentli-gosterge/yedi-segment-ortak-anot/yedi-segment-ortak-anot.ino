/////////////////////////////////////////////////////////////////////////
// 7 Segmentli Gosterge kod ornegi
// 
// wizofwor - Mayis 2015
// https://github.com/wizofwor/arduino
//
/////////////////////////////////////////////////////////////////////////

/**
  * Sifirdan 9'a kadar rakamlari tanimlayalim.
  * 8 bitlik sayinin her biti bir ledi isaret edecek
  */
const byte rakamlar[11] = {
   B0000001,  // 0
   B1001111,  // 1
   B0010010,  // 2
   B0000110,  // 3
   B1001100,  // 4
   B0100100,  // 5
   B0100000,  // 6
   B0001111,  // 7
   B0000000,  // 8
   B0001100,  // 9
   B1111111,   // bos
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
