#include <Arduino.h>

// Definido portas dos LEDs
#define RED 10
#define YELLOW 11
#define GREEN 12
#define BLUE 13

// Definindo portas dos push buttons
#define BRED 4
#define BYELLOW 5
#define BGREEN 6
#define BBLUE 7

// Definindo porta do buzzer
#define BUZZ 3

// Número de LEDs e Pushbuttons
#define TAM 4

// Define tempo do sleep
#define TIME 100

// Esqueleto das funções
void mostraSequencia(int sequencia[TAM], int nivel);
int botaoApertado();
int acertou(int tentativa[TAM], int resposta[TAM]);

// Variáveis globais
int leds[TAM] = {RED, YELLOW, GREEN, BLUE};
int botoes[TAM] = {BRED, BYELLOW, BGREEN, BBLUE};
int nivel = 0;

void setup()
{
  int i;
  // Saídas
  for (i = 0; i < TAM; i++)
    pinMode(leds[i], OUTPUT);
  // Entradas
  for (i = 0; i < TAM; i++)
    pinMode(botoes[i], INPUT);
  // Inicia o gerador de números aleatórios com leitura de estado flutuante da A0
  randomSeed(analogRead(0));
}

void loop()
{
  int sequencia[TAM];
  int tentativa[TAM], tent;
  int i, acertos = 0;;

  // Gera sequência aleatória e pisca os LEDs
  for (i = 0; i < TAM; i++)
    sequencia[i] = random(0, TAM);

  mostraSequencia(sequencia);
  // Lê sequência apertada
  for (i = 0; i < TAM;  i++)
    tentativa[i] = botaoApertado();

  if (acertou(tentativa, sequencia))
    {
      acertos++;
      if (acertos == 3)
        nivel++;

    }


}

// Implementação das funções

int botaoApertado()
{
  int i, jogada = 0;

  while (!jogada)
  {
    for (i = 0; i < TAM; i++)
      if (digitalRead(botoes[i]))
      {
        jogada = 1;
        return i;
      }
  }
}

int acertou(int tentativa[TAM], int resposta[TAM])
{
  int i;
  for (i = 0; i < TAM; i++)
    if (tentativa[i] != resposta[i])
      return 0;
  return 1;
}

void mostraSequencia(int sequencia[TAM])
{
  int i;

  for (i = 0; i < TAM; i++)
  {
    pinMode(leds[sequencia[i]], HIGH);
    delay(TIME * (5 - nivel));
    pinMode(leds[sequencia[i]], LOW);
  }
}
