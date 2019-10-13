#include "pitches.h"
#include "button.h"
#include "buzzer.h"

#define PIN_BUZZER 6
#define PIN_BUTTON 5

Button button(PIN_BUTTON);
Buzzer buzzer(PIN_BUZZER);

#define R_OUT 9
#define G_OUT 7
#define B_OUT 8

int notes[] = {NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE};
double durations[] = {1, 1, 1, 1, 1, 1, 1, 1};
int melodyLength = 8;
int red = 255;
bool isBrightRed = true;


void setup()
{
    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);

    buzzer.setMelody(notes, durations, melodyLength);
    buzzer.turnSoundOn();
}

void loop() 
{
    if (buzzer.isMelodyEnd())
    {
        buzzer.turnSoundOff();
        set_rgb_led(0, 0, 0);
    }
    else
    {
        if (isBrightRed)
        {
            set_rgb_led(red, 0, 0);
            isBrightRed = false;
        }
        else
        {
            set_rgb_led(red-200, 0, 0);
            isBrightRed = true;
        }
    }
    
    if (button.wasPressed())
    {
        buzzer.turnSoundOn();
    }
    buzzer.playSound();
}

void set_rgb_led(int r, int g, int b)
{
    analogWrite(R_OUT, 255 - r);
    analogWrite(G_OUT, 255 - g);
    analogWrite(B_OUT, 255 - b);
}
