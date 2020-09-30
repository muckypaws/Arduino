#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5
};

int melody2[] = {
  NOTE_D2, NOTE_F2, NOTE_G2, 
  NOTE_D2, NOTE_F2, NOTE_GS2, NOTE_G2, 0, 
  NOTE_D2, NOTE_F2, NOTE_G2, 0, 
  NOTE_F2, NOTE_D2 , 0
};

int noteDurations2[] = {
  2,2,1,
  2,2,4,1,8,
  2,2,1,16,
  2,1,2,
  0,0,0,0,0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

#define MAX_LIGHTS 14
#define START_LIGHT 2

int lightTrace[MAX_LIGHTS] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0};


// This is the Built In Button of the Maker Uno +
// and needs to be configured as a pull up switch
const int BuiltInButton = 2;

// Global Variable for buttonPressed
boolean buttonPressed = false;



//
//   Play the tones for Shave and Hair Cut
//
void playSong(int which)
{
  int numberOfNotes = which>1?15:8;
  int tempo = which>1?800:1000;
  int noteDuration = 1000;
  int pauseBetweenNotes;
  
   // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < numberOfNotes; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    if(which == 1)
    {
      noteDuration = tempo / noteDurations[thisNote];
    
      tone(8, melody[thisNote], noteDuration);
    }
    else
    {
      noteDuration = tempo / noteDurations2[thisNote];
    
      tone(8, melody2[thisNote], noteDuration);
    }

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}


//
//   Scroll the light display depending on direction
//
void scrollLights(boolean direction)
{
  int temp = 0;
  
  if(direction)
  {
    // Get First Light Status
    temp = lightTrace[MAX_LIGHTS-1];

    if (lightTrace[MAX_LIGHTS-4]>0) buttonPressed=!buttonPressed;

    // Scroll Them Lights
    for (int i = MAX_LIGHTS-1; i>0; i-- ) 
    {
      lightTrace[i] = lightTrace[i-1];
    }
    lightTrace[0] = temp;

    
  }
  else
  {
    // Get First Light Status
    temp = lightTrace[0];

    if (lightTrace[1] > 0)
    {
      buttonPressed=!buttonPressed;
    }

    // Scroll Them Lights
    for (int i = 0; i<MAX_LIGHTS; i++ ) 
    {
      lightTrace[i] = lightTrace[(i+1)];
    }
    
    lightTrace[MAX_LIGHTS-1] = temp;
  }

  
}

//
//   Set the PIN Mode of the inbuilt LEDS and 
//       Force the outputs to LOW (i.e. OFF)
//
void resetLights()
{
   // we're going to use the built in LED
  for (int i=START_LIGHT; i<MAX_LIGHTS; i++) 
  {
    pinMode (i, OUTPUT);
    digitalWrite(i,LOW);  // Set all lights off on Boot
  }
  
  displayLights();
}

//
//   Write the array of lights to the LEDS
//       
//
void displayLights()
{
  for (int i=START_LIGHT; i<MAX_LIGHTS; i++)
  {
    digitalWrite(i,(lightTrace[i-START_LIGHT]>0?HIGH:LOW));
  }
}


//
//   Lets initialise our Maker Plus
//
void setup() 
{

  resetLights();
  
  // The Built In Button on the UNO + needs to be configured as Pull Up
  pinMode (BuiltInButton, INPUT_PULLUP);
  pinMode (3, INPUT);

}


void loop() 
{
 
    scrollLights(buttonPressed);
    displayLights();
    delay(50);


   // boolean val = digitalRead(BuiltInButton);

    if (digitalRead(BuiltInButton)) 
    {
         playSong(1);
    }

    if (digitalRead(3))
    {
      playSong(2);
    }
 
}
