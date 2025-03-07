#include <Arduino.h>

// Definição dos GPIOs
#define LED_PINS {15,2,0,4,16,17,5,18} // GPIOs para LEDs
#define SW_PINS {35,34}                      // GPIOs para botões

int leds[] = LED_PINS;      // Array de GPIOs para LEDs
int switches[] = SW_PINS;   // Array de GPIOs para botões
uint8_t saida = 0;
int direcao = 0;
static int POTENCIOMETRO = 26;
static int FREQUENCIA = 50;
static int channel = 1;

uint8_t incremento(uint8_t saida) {
  
  if (saida == 255){
    saida = 0;
  }else{
    saida++;
  }
  return saida;
}

uint8_t decremento(uint8_t saida) {
    
if (saida == 0){
    saida = 255;
}
else{
    saida--;
  }
  return saida;
}

void setup() {
  // Configuração dos LEDs como saída
  Serial.begin(9600);

  pinMode(POTENCIOMETRO, INPUT);

  ledcSetup(channel, FREQUENCIA, 12);
  for (int i = 0; i<8; i++){
    ledcAttachPin(leds[i], channel);
  }
  
  //ledcAttachChannel(POTENCIOMETRO, FREQUENCIA, 12, 0);
  // ledcAttach(POTENCIOMETRO, FREQUENCIA, 12);

  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW); // Garante que os LEDs iniciem desligados
  }

  // Configuração dos botões como entrada
  for (int i = 0; i < 2; i++) {
    pinMode(switches[i], INPUT);
  }
}

void loop() {
    analogWriteResolution(8);

  // Leitura do estado dos botões
  uint8_t valorBotao = 0; // Variável para armazenar o valor dos botões
  int dutycycle = analogRead(POTENCIOMETRO);

  // Lê cada botão e define o bit correspondente
  for (int i = 0; i < 2; i++){
    if (digitalRead(switches[i]) == HIGH) valorBotao |= (1 << i); // Botão 0 -> Bit 0
  } 

  Serial.println(dutycycle);

  //Serial.println(saida);

    for (int i = 0; i < 8; i++) {
      if (saida & (1 << i)) {
        //digitalWrite(leds[i], HIGH); // Liga o LED
analogWrite(leds[i], dutycycle);
      } else {
analogWrite(leds[i], 0);

        //digitalWrite(leds[i], LOW);  // Desliga o LED
      }
    }

  delay(300); // Delay para estabilidade
  Serial.println(saida);

  // Ações baseadas no botão pressionado
  switch (valorBotao) {
    case 0:
      saida = incremento(saida);
      break;
    case 1:
      saida = decremento(saida);
      break;
    default:
      break;
  }
}

