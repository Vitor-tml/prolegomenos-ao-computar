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

// Define tons
#define DO 130
#define RE 146
#define MI 164
#define FA 174
#define LA 220

// Quantidade de LEDs e botões
#define TAM 4

// Variáveis globais
int leds[TAM] = {RED, YELLOW, GREEN, BLUE};
int botoes[TAM] = {BRED, BYELLOW, BGREEN, BBLUE};
int notas[TAM] = {DO, RE, MI, FA};
int rodada = 0;
Adafruit_LiquidCrystal lcd_1(0);
// Protótipo das funções
int botaoApertado();
int testaSequencia(int *resposta);
void mostraSequencia(int *sequencia, int rodada);

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
  lcd_1.clear();
  // Gera sequencia aleatoria
  for(i = 0; i < TAM; i++)
  {
    resposta[i] = random(0, TAM);
  }
  mostraSequencia(resposta, rodada);
  if(testaSequencia(resposta))
  {
    lcd_1.print("Correto!");
    rodada++;
  }
  else
  {
    lcd_1.print("Errado!");
    derrota();
    delay(500);
    rodada = 0;
  }
  if(rodada == 3)
  {
    vitoria();
    rodada = 0;
    lcd_1.print("Voce venceu!!!");
  }
  
  delay(700);
  
}
// Recebe sequência e lê resposta, retorna 1 caso a resposta for correta
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

// Recebe sequência resposta e acende os LEDs nessa sequência
void mostraSequencia(int *sequencia, int rodada)
{
  int i;
  
  for(i = 0; i < TAM; i++)
  {
    digitalWrite(leds[sequencia[i]], HIGH);
    tone(BUZZ, notas[sequencia[i]], 200);
    delay(500 - (100 * rodada));
    digitalWrite(leds[sequencia[i]], LOW);
  }
}

// Fica checando os botões em loop, retorna o primeiro botão apertado
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
          tone(BUZZ, notas[i], 100);
          digitalWrite(leds[i], HIGH);
        }
        digitalWrite(leds[i], LOW);
        return i;
      }
    }
  }
}

// Som da derrota
void derrota()
{
  tone(BUZZ, 80, 1500);
  delay(1500);
}
void vitoria()
{
  tone(BUZZ, 293, 300);
  delay(350);
  tone(BUZZ, 293, 300);
  delay(350);
  tone(BUZZ, 329, 400);
  delay(450);
  tone(BUZZ, 293, 550);
  delay(600);
  
}