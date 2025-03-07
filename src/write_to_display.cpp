// Faça um código que:
//  conte de 0 a 9999 se a chave 1 estiver acionada, e a 2 não estiver
//  conte de 9999 a 0 se chave 2 estiver acionada, e a 1 não estiver
//  pause a contagem se as duas chaves estiverem na mesma posicão
//         (ou seja, as duas acionadas ou nenhuma das duas acionadas)
	
#include "stdio.h"
#include "Arduino.h"

#include <chrono>
#include <iostream>

const int pinoSeparador = 19; // Dois pontos do display
const int pinosSegmentos[] = {12,14,27,26,25,33,32}; // a,b,c,d,e,f,g,dp,:
const int pinoPontoDecimal =  18; 
const int pinosCatodo[] = {15,2,0,4}; 

const int pinosChaves[] = {23,22};

int i = 0;
int j = 0;

void display_char(int num, int pos)
{
    for(int i = 0; i < 4; i++)
    {
        digitalWrite(pinosCatodo[i], 1);
    }

    num = num % 10;
    switch (num)
    {
    case 0:
        digitalWrite(12, 1);
        digitalWrite(14, 1);
        digitalWrite(27, 1);
        digitalWrite(26, 1);
        digitalWrite(25, 1);
        digitalWrite(33, 1);
        digitalWrite(32, 0);
        digitalWrite(18, 0);
        break;
    case 1:
        digitalWrite(12, 0);
        digitalWrite(14, 1);
        digitalWrite(27, 1);
        digitalWrite(26, 0);
        digitalWrite(25, 0);
        digitalWrite(33, 0);
        digitalWrite(32, 0);
        digitalWrite(18, 0);
        break;
    case 2:
        digitalWrite(12, 1);
        digitalWrite(14, 1);
        digitalWrite(27, 0);
        digitalWrite(26, 1);
        digitalWrite(25, 1);
        digitalWrite(33, 0);
        digitalWrite(32, 1);
        digitalWrite(18, 0);
        break;
    case 3:
        digitalWrite(12, 1);
        digitalWrite(14, 1);
        digitalWrite(27, 1);
        digitalWrite(26, 1);
        digitalWrite(25, 0);
        digitalWrite(33, 0);
        digitalWrite(32, 1);
        digitalWrite(18, 0);
        break;
    case 4:
        digitalWrite(12, 0);
        digitalWrite(14, 1);
        digitalWrite(27, 1);
        digitalWrite(26, 0);
        digitalWrite(25, 0);
        digitalWrite(33, 1);
        digitalWrite(32, 1);
        digitalWrite(18, 0);
        break;
    case 5:
        digitalWrite(12, 1);
        digitalWrite(14, 0);
        digitalWrite(27, 1);
        digitalWrite(26, 1);
        digitalWrite(25, 0);
        digitalWrite(33, 1);
        digitalWrite(32, 1);
        digitalWrite(18, 0);
        break;
    case 6:
        digitalWrite(12, 1);
        digitalWrite(14, 0);
        digitalWrite(27, 1);
        digitalWrite(26, 1);
        digitalWrite(25, 1);
        digitalWrite(33, 1);
        digitalWrite(32, 1);
        digitalWrite(18, 0);
        break;
    case 7:
        digitalWrite(12, 1);
        digitalWrite(14, 1);
        digitalWrite(27, 1);
        digitalWrite(26, 0);
        digitalWrite(25, 0);
        digitalWrite(33, 0);
        digitalWrite(32, 0);
        digitalWrite(18, 0);
        break;
    case 8:
        digitalWrite(12, 1);
        digitalWrite(14, 1);
        digitalWrite(27, 1);
        digitalWrite(26, 1);
        digitalWrite(25, 1);
        digitalWrite(33, 1);
        digitalWrite(32, 1);
        digitalWrite(18, 0);
        break;
    case 9:
        digitalWrite(12, 1);
        digitalWrite(14, 1);
        digitalWrite(27, 1);
        digitalWrite(26, 1);
        digitalWrite(25, 0);
        digitalWrite(33, 1);
        digitalWrite(32, 1);
        digitalWrite(18, 0);
        break;
    
    default:
        break;
    }

    digitalWrite(pinosCatodo[pos], 0);
    
}

void display(int num)
{
    int dig;
    for(int i = 3; i >=0; i--)
    {
        dig = num % 10;
        display_char(dig, i);
        num = num / 10;
        delay(10);
    }
}

void setup(){
    pinMode(12, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);

    pinMode(15, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(pinosCatodo[0], 1);
    digitalWrite(pinosCatodo[1], 1);
    digitalWrite(pinosCatodo[2], 1);
    digitalWrite(pinosCatodo[3], 1);

    pinMode(23, INPUT);
    pinMode(22, INPUT);

}

void loop() {
    
    display(i);
    j++;
    if(j > 25)
    {
        i++;
        j = 0;
    }

}