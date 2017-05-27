
/*
 Demo code of EB - I2C_1602_LCD 
 by maker studio 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * 5V to Arduino 5V pin
 * GND to Arduino GND pin
 * CLK to Analog #5
 * DAT to Analog #4
 
*/

// include the library code:
#include <Wire.h>
#include "LiquidCrystal.h"
#include <TimerOne.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);

//int centesimo=0;
volatile int decimo=0;
volatile int segundo=0;
volatile int minuto=0;
volatile int hora=0; 

volatile int unsigned long tempoEntreInterrupcoes;

// define pin button is attached to
int pin=2;

// define chrometer states
int s_zeroed=0;
int s_running=1;
int s_stopped=2;

int state = s_zeroed;

void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);

  lcd.setBacklight(HIGH);

  lcd.setCursor(0, 0);
  lcd.print("Cronometro");

  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), pushButton, RISING);//once button been pushed, function pushButton() will be executed

  Timer1.initialize(100000); // set a decisecond period
  Timer1.attachInterrupt(incrementaTempo);
}

void loop() {
  lcd.setCursor(0, 1);
  if (hora<10)
  {
    lcd.print("0");
  }
  lcd.print(hora);
  lcd.print(":");
  if (minuto<10)
  {
    lcd.print("0");
  }
  lcd.print(minuto);
  lcd.print(":");
  if (segundo<10)
  {
    lcd.print("0");
  }
  lcd.print(segundo);
  lcd.print(",");
  lcd.print(decimo);

  delay(50);
}

void pushButton()
{
  if ( (millis() - tempoEntreInterrupcoes) > 300)
  {
    tempoEntreInterrupcoes = millis();
    
    if(state==s_zeroed)
    {
      state = s_running;
    } else {
      if(state==s_running){
        state=s_stopped;
      } else {
        if(state==s_stopped){
          state=s_zeroed;
          decimo=0;
          segundo=0;
          minuto=0;
          hora=0; 
        }
      }
    }
  }
}


void incrementaTempo()
{
  if(state==s_running)
  {
    decimo=decimo+1;
    if (decimo>=10)
    {
      segundo=segundo+1;
      decimo=0;
    }
    if (segundo>=60)
    {
      minuto=minuto+1;
      segundo=0;
    }
    if (minuto>=60)
    {
      hora=hora+1;
      minuto=0;
    }
  }
}
