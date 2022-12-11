//#include <Arduino.h>

#include <Adafruit_LiquidCrystal.h>

// DEfinindo portas dos LEDs
#define RED 10
#define YELLOW 11
#define GREEN 12
#define BLUE 13

// Definindo portas dos pushbuttons
#define BRED 4
#define BYELLOW 5
#define BGREEN 6
#define BBLUE 7

// Definindo saida do buzzer
#define BUZZ 3
// Tefine tons
#define LA 440
// Quantidade de LEDs e botões
#define TAM 4

// Variáveis globais
int leds[TAM] = {RED, YELLOW, GREEN, BLUE};
int botoes[TAM] = {BRED, BYELLOW, BGREEN, BBLUE};

Adafruit_LiquidCrystal lcd_1(0);
int botaoApertado();

void setup()
{
  lcd_1.begin(16, 2);

  int i;
  
  for(i = 0; i < TAM; i++)
  {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT);
  }
  pinMode(BUZZ, OUTPUT);
}

void loop()
{
}

int botaoApertado()
{
  int i = 0;

  while(1)
  {
    for(i = 0; i < TAM; i ++)
    {
      if(digitalRead(botoes[i]) == HIGH)
      {
        while(digitalRead(botoes[i]) == HIGH)
        {
          tone(BUZZ, LA, 100);
        }
        
        return i;
      }
    }
  }

}