/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #07.2 - Muzik1
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
// SparkFun Inventor's Kit - Example sketch 11'de faydalanarak yapilmistir
// Orjinal yazar: D. Cuartielles 
//
// Sparkfun SIK Exprimant Guide for Arduino - V3.2
// Experiment11:Using a Piezo Buzzer
//
// https://learn.sparkfun.com/tutorials/
//
/////////////////////////////////////////////////////////////////////////


const int buzzerPin = 9;

//calacagim parcanin kac notadan olustugunu tanimyliyorum.

const int uzunluk = 18;


// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

char notes[] = "cdfda ag cdfdg gf "; // a space represents a rest


// Beats is an array of values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.

int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 150;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}



void loop() {
  int i, duration;
  for (i = 0; i < uzunluk; i++) {// step through the song array
    duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')  {        // is this a rest? 
      delay(duration);            // then pause for a moment
    }

    else {                         // otherwise, play the note
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }

  // We only want to play the song once, so we'll pause forever:
  while(true){}
  // If you'd like your song to play over and over,
  // remove the above statement
}


/**
 * Bu fonksiyon notayi adini alip
 * frekansini donduruyor
 */
int frequency(char note) 
{
  /**
    * Notalar icin bir lookup tablosu olusturmam lazim.
    * Nota adlarini ve karsilik gelen frekans degerlerini birer
    * dizi olarak giriyorum
    */
  char notalar[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frekanslar[] = {262, 294, 330, 349, 392, 440, 494, 523};
  /**
    * Boylece ilk diziden nata adini bulup
    * ikinci diziden frekans degerini cekebilirim.
    */
  for (int i = 0; i < 8; i++) { // Butun notalari tariyorum
    if (notalar[i] == note)       // aradigim notayi buldugumda
      return(frekanslar[i]);     // frekans degerini donduruyorum
  }
  //eger hic bir sey bulamamissam, 0 degerini donduruyorum.
  return(0);  
}
