/*
 * This example plays every .WAV file it finds on the SD card in a loop
 */
#include <WaveHC.h>
#include <WaveUtil.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

uint8_t dirLevel; // indent level for file/dir names    (for prettyprinting)
dir_t dirBuf;     // buffer for directory reads


int score = 0;
int previousScore = -1;
char l = 'P';
  char a = 'W';
  long int pulseTimes; 
  char lightType;
  int d;
  int expectedScore = 0;
  unsigned long startT;
/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))

// Function definitions (we define them here, but the code is below)
void play(FatReader &dir);

//////////////////////////////////// SETUP
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  putstring_nl("\nWave test!");  // say we woke up!

  pinMode(7,INPUT);
  pinMode(8,INPUT);
   putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(FreeRam());
  pinMode(2, OUTPUT); pinMode(3, OUTPUT); pinMode(4, OUTPUT); pinMode(5, OUTPUT);

  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    error("Card init. failed!");  // Something went wrong, lets print out why
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
  
  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {   // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                           // we found one, lets bail
  }
  if (part == 5) {                     // if we ended up not finding one  :(
    error("No valid FAT partition!");  // Something went wrong, lets print out why
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    error("Can't open root dir!");      // Something went wrong,
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Files found (* = fragmented):");

  // Print out all of the files in all the directories.
  root.ls(LS_R | LS_FLAG_FRAGMENTED);
root.rewind();
play(root);  
}

//////////////////////////////////// LOOP
void loop() {

root.rewind();
play(root);
}

/////////////////////////////////// HELPERS
/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}
/*
 * play recursively - possible stack overflow if subdirectories too nested
 */
void play(FatReader &dir) {
  FatReader file;
  while (dir.readDir(dirBuf) > 0) {    // Read every file in the directory one at a time
  
    // Skip it if not a subdirectory and not a .WAV file
    if (!DIR_IS_SUBDIR(dirBuf)
         && strncmp_P((char *)&dirBuf.name[8], PSTR("WAV"), 3)) {
      continue;
    }

    Serial.println();            // clear out a new line
    
    for (uint8_t i = 0; i < dirLevel; i++) {
       Serial.write(' ');       // this is for prettyprinting, put spaces in front
    }
    if (!file.open(vol, dirBuf)) {        // open the file in the directory
      error("file.open failed");          // something went wrong
    }
    
    if (file.isDir()) {                   // check if we opened a new directory
      putstring("Subdir: ");
      printEntryName(dirBuf);
      Serial.println();
      dirLevel += 2;                      // add more spaces
      // play files in subdirectory
      play(file);                         // recursive!
      dirLevel -= 2;    
    }
    else {
      // Aha! we found a file that isnt a directory
      putstring("Playing ");
      printEntryName(dirBuf);              // print it out
      if (!wave.create(file)) {            // Figure out, is it a WAV proper?
        putstring(" Not a valid WAV");     // ok skip it
      } else {
        Serial.println();                  // Hooray it IS a WAV proper!

                
        uint32_t nextColor = strip.Color(0,0,255);
        int colorRotation = 0;
        boolean prevClicked;

        while(digitalRead(7)==LOW && digitalRead(8) == LOW)
        {
          file.rewind();
          wave.play();
          
            for(int i  = 0; i<strip.numPixels(); i++)
            {
              strip.setPixelColor(i,nextColor);
            }
            
            switch(colorRotation%6)
            {
              case 0:
              case 2:
              case 4:
                  nextColor = strip.Color(0,0,0);
                  colorRotation++;
                  break;
              case 1:
                  nextColor = strip.Color(255,40,255);
                  colorRotation++;
                  break;
              case 3:
                  nextColor = strip.Color(255,255,255);
                  colorRotation++;
                  break;
              case 5:
                  nextColor = strip.Color(255,40,255);
                  colorRotation++;
                  break;
            }
            strip.show();
            delay(108);
        }
        unsigned long t2 = millis();
        
        file.rewind();
        wave.play();// make some noise!

        
        for(int i = strip.numPixels()-1; i>=0; i--)
        {
            strip.setPixelColor(i,strip.Color(0,0,0));
        }

        strip.show();
        nextColor = strip.Color(255,40,255);

        while(wave.isplaying)
        {
          //Color Pulse
          boolean easyMode = false;
          boolean mediumMode = false;
          boolean hardMode = false;
          boolean expertMode = false;
          


        /* Now score checking. There are 3 possibile outcomes. Case 1: If it is a color,
         *  the user clicks on the colored button and scores a point. Then, if
         *  the user clicks on the button again, he loses a point - for however 
         *  many times user clicks. Case 2: the user clicks the wrong color
         *  Case 3: The user clicks on a color when there is no color
         *  If the user did not click, then user neither gains or loses a point
         */

         boolean missClick = false;
         boolean clicked = false;
         unsigned long t = millis();

         if(t<24470+t2+startT)
         {
          easyMode = true;
          d = 430;
         }

         else if(t>22470+t2 && t<39150+t2)
         {
          mediumMode = true;
          d=430;
         }

         else if(t<80000 +t2)
         {
          hardMode = true;
          d=215;
         }

         else 
         {
          expertMode = true;
          d=108;
         }
         
        if(easyMode) {
          
          for(int i = strip.numPixels()-1; i>=0; i--)
          {
            colorMove(i,strip.getPixelColor(i));
          }

          strip.setPixelColor(0,nextColor);

          if(strip.getPixelColor(1) == strip.Color(0,0,0))
              nextColor = strip.Color(0,0,0);
          else if(strip.getPixelColor(1) == strip.Color(255,255,255))
              nextColor = strip.Color(255,40,255);
          else
              nextColor = strip.Color(255,255,255);

          strip.show();
        }

        else if(mediumMode){
          
          for(int i = strip.numPixels()-1; i>=0; i--)
          {
            colorMove(i,strip.getPixelColor(i));
          }

          strip.setPixelColor(0,nextColor);

          int c = random(1,3);
          
          if(strip.getPixelColor(0)!=strip.Color(0,0,0))
            nextColor = strip.Color(0,0,0);
          else if(c==1)
            nextColor = strip.Color(255,40,255);
          else
            nextColor = strip.Color(255,255,255);

          strip.show();
          }

        else if(hardMode)
        {
           for(int i = strip.numPixels()-1; i>=0; i--)
          {
            colorMove(i,strip.getPixelColor(i));
          }

          strip.setPixelColor(0,nextColor);
         
          int c = random(1,3);
          
          if(strip.getPixelColor(0)!=strip.Color(0,0,0))
            nextColor = strip.Color(0,0,0);
          else if(c==1)
            nextColor = strip.Color(255,40,255);
          else
            nextColor = strip.Color(255,255,255);

          strip.show();
          
        }

        else if(expertMode)
        {
           for(int i = strip.numPixels()-1; i>=0; i--)
          {
            colorMove(i,strip.getPixelColor(i));
          }

          strip.setPixelColor(0,nextColor);
         
          int c = random(1,3);
          
          if(strip.getPixelColor(0)!=strip.Color(0,0,0))
            nextColor = strip.Color(0,0,0);
          else if(c==1)
            nextColor = strip.Color(255,40,255);
          else
            nextColor = strip.Color(255,255,255);

          strip.show();
          
        }
// Case 1: Blue

         if(strip.getPixelColor(29)!=strip.Color(0,0,0))
            expectedScore++;
            
         while((strip.getPixelColor(29)==strip.Color(255,40,255)) && (millis()-t<d))
         {
           if(digitalRead(8) == HIGH)
              missClick = true;

           if(digitalRead(7) == HIGH)
              clicked = true;
              
         }
// Case 2: White 
         while((strip.getPixelColor(29)==strip.Color(255,255,255)) && (millis()-t<d))
         {
           if(digitalRead(7) == HIGH)
              missClick = true;

           if(digitalRead(8) == HIGH)
              clicked = true;
              
         }       
          
// Case 3: No Light - Remove Elements inside if want to make it easier

         while((strip.getPixelColor(29)==strip.Color(0,0,0)) && (millis()-t<d))
         {
          
           //if(!prevClicked && (digitalRead(7) == HIGH || digitalRead(8) == HIGH))
              //missClick = true;
         }       
          
          

        // Now score interpreter

        if(missClick)
          score--;

        if(clicked)
          score++;

         prevClicked = clicked;

         

        // At the end, print the percentage of score complete and display that much light as green!
        }

        int numPix = ((score*30)/expectedScore);
        Serial.println(score);
        Serial.println(numPix);
        for(int i = 0; i<30; i++)
        {
          strip.setPixelColor(i,strip.Color(0,0,0));
        }

        strip.show();

        
        for(int a = 0; a<numPix; a++)
        {
          strip.setPixelColor(a,strip.Color(255,40,255));
          strip.show();
          delay(50);
        }

        for(int x = 0; x<40; x++)
        {
          for(int a = 0; a<numPix; a++)
          {
            
            strip.setPixelColor(a,strip.Color(255,255,255));
            strip.setPixelColor(a-1,strip.Color(255,40,255));
            strip.show();
            if(a>numPix)
            {
              strip.setPixelColor(a,strip.Color(0,0,0));
            }
            
            delay(30);
          }
          
          strip.show();
        }

        
        sdErrorCheck();                    // everything OK?
        // if (wave.errors)Serial.println(wave.errors);     // wave decoding errors
      }
    }
  }
}


// Color Shifting Pattern
void colorMove(int i, uint32_t c)
{
  strip.setPixelColor(i+1,c);
}



