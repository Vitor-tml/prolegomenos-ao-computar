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
  randomSeed(analogRead(0));
}

void loop()
{
  int tentativa[TAM];
  int resposta[TAM];
  int i;
  
  for(i = 0; i < TAM; i++)
  {
    resposta[i] = random(0, TAM);
    lcd_1.print(resposta[i]);
  }
  mostraSequencia(resposta);
  if(testaSequencia(resposta))
  {
    lcd_1.print("Correto!");
  }
  else
  {
    lcd_1.print("Errado!");
  }
}
int testaSequencia(int *resposta)
{
  int i;
  for(i = 0; i < TAM; i++)
  {
    if(resposta[i] != botaoApertado())
    {
      return 0;
    }
  }
  return 1;
}
void mostraSequencia(int *sequencia)
{
  int i;
  
  for(i = 0; i < TAM; i++)
  {
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequencia[i]], LOW);
  }
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