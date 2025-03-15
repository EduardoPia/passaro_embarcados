#include <Arduino.h>

#define DHT_PIN 4

typedef struct SensorData
{
  int32_t umidade;
  int32_t temp;
  int32_t checksum;
} SensorData;

SensorData data;


// put function declarations here:
bool read_sensor(SensorData& data);

bool erro_leitura(int i);

void setup() {
	Serial.begin(9600);
}

void loop() 
{
	delay(5000);
	if(read_sensor(data))
	{
		Serial.println("--------------------------------------------");
		Serial.println("Resposta: ");
		Serial.print("Umidade:");
		Serial.println(data.umidade);
		Serial.print("Temperatura:");
		Serial.println(data.temp);
		Serial.print("Checksum:");
		Serial.println(data.checksum);
	}
}

bool erro_leitura(int i)
{
	Serial.print("Erro: sem resposta do sensor, ");
	Serial.println(i);
	return false;
}

// put function definitions here:
bool read_sensor(SensorData& data)
{
	unsigned long tempo;
	data.temp     = 0;
	data.umidade  = 0;
	data.checksum = 0;

	// Pede a resposta
	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, LOW);
	delay(18);
	digitalWrite(DHT_PIN, HIGH);
	delayMicroseconds(30);
	pinMode(DHT_PIN, INPUT);

	// Etapa de reconhecimento (resposta do DHT)
	// Espera descer
	tempo = micros();
	while(digitalRead(DHT_PIN) == HIGH)
	{
		if((micros() - tempo) > 40)
			return erro_leitura(0);
	}
	// Espera subir
	tempo = micros();
	while(digitalRead(DHT_PIN) == LOW)
	{
		if((micros() - tempo) > 160)
			return erro_leitura(1);
	}
	// Quando descer novamente, começa a etapa de leitura dos dados
	tempo = micros();
	while(digitalRead(DHT_PIN) == LOW)
	{
		if((micros() - tempo) > 160)
			return erro_leitura(2);
	}

	// Leitura dos dados
	for(int i = 0; i < 40; i++)
	{
		int bit;
		// Espera os 50 us de start
		tempo = micros();
		while(digitalRead(DHT_PIN) == LOW)
		{
			if((micros() - tempo) > 100)
				return erro_leitura(3);
		}

		// Conta o tempo em nível alto
		tempo = micros();
		while(digitalRead(DHT_PIN) == HIGH)
		{
			if((micros() - tempo) > 140)
				return erro_leitura(4);
		}

		// associe o tempo ao bit
		unsigned long dt = (micros() - tempo);
		if      ((10 < dt) && (dt < 50))
			bit = 0;
		else if ((50 < dt) && (dt < 100))
			bit = 1;
		else
			return erro_leitura(dt);
		
		// Salva na variável correta
		if(i < 8)
			data.umidade = data.umidade*2 + bit;
		else if((i > 15) && (i < 24))
			data.temp = data.temp*2 + bit;
		else if(i > 31)
			data.checksum = data.checksum*2 + bit;
	}
	return true;
}