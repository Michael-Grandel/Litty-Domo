/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

/*
 Darude - Sandstorm
 
 (c) Jordi Agricola 2014
 
 Speaker on port 8
 
 */
 #include "pitches.h"
 
// notes in the melody:
 
// note durations: 4 = quarter note, 8 = eighth note, etc.:
 
 int shortTone = 80;
 int longTone = 200;
 int standardDelay = 50;
 int delayBetweenBars = 50;
 
void setup() {
 
}
 
void loop() {
   tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, longTone);
 delay(longTone);
 noTone(8);
 delay(delayBetweenBars);
 
    tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, longTone);
 delay(longTone);
 noTone(8);
 delay(standardDelay);
 
     tone(8,  NOTE_E4, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,NOTE_E4, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_E4, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_E4, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_E4, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_E4, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_E4, longTone);
 delay(longTone);
 noTone(8);
 delay(standardDelay);
 
 
     tone(8,  NOTE_D4, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,NOTE_D4, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_D4, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_D4, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_D4, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_D4, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_D4, longTone);
 delay(longTone);
 noTone(8);
 delay(standardDelay);
 
tone(8, NOTE_A3, longTone);
delay(longTone);
 noTone(8);
 delay(standardDelay);
 
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, longTone);
 delay(longTone);
 noTone(8);
 delay(delayBetweenBars);
 
    tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, longTone);
 delay(longTone);
 noTone(8);
 delay(standardDelay);
 
 tone(8, NOTE_E4, longTone);
 delay(longTone);
 noTone(8);
 delay(standardDelay);
 
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, longTone);
 delay(longTone);
 noTone(8);
 delay(delayBetweenBars);
 
    tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
   delay(shortTone);
  noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, shortTone);
  delay(shortTone);
 noTone(8);
 delay(standardDelay);
 tone(8,  NOTE_B3, shortTone);
 delay(shortTone);
 noTone(8);
  delay(standardDelay);
tone(8,  NOTE_B3, longTone);
 delay(longTone);
 noTone(8);
 delay(standardDelay);
 
tone(8, NOTE_E4, longTone);
 delay(longTone);
 noTone(8);
 delay(standardDelay);
 
}
