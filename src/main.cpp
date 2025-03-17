#include <Arduino.h>
// #include <LiquidCrystal.h>

// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

static const int POT_pin   = 4;
static const int LDR_pin   = 18;
static const int SERVO_pin = 27;
static const int LED_pin   = 14;

static const int res = 12;
static const int freq = 50;
static const int channel = 1;
static const int max_duty = -1;
static const int min_duty = -1;

int POT_value = 0;
int LDR_value = 0;
int period    = -1;
int period_blink = -1;

enum FLIGHT_MODE {Auto, Manual};
FLIGHT_MODE mode = Manual; 

enum DAY_TIME {Day, NightFall, Night};
DAY_TIME day_time = Day; 

void read_pot();
void read_LDR();
void update_servo();
void update_eyes();
void update_LCD();
void receive_command();

// put function declarations here:
void 
setup() 
{
	analogReadResolution(res); // pot
	pinMode(LDR_pin, INPUT_PULLUP); // ldr
	pinMode(LED_pin, OUTPUT);

	ledcSetup(channel, freq, res); // servo
	ledcAttachPin(SERVO_pin, channel);

	// lcd.begin(16, 2);
	// lcd.print("Time to FLY!");

	Serial.begin(9600);
}

void 
loop() 
{
	// Sensores
	read_pot();
	read_LDR();

	// Cargas
	update_servo();
	update_eyes();

	// User
	update_LCD();
	receive_command();
}

// put function definitions here:
void 
read_pot() 
{
	POT_value = analogRead(POT_pin);
}

void 
read_LDR() 
{
	LDR_value = digitalRead(LDR_pin);
}

void 
update_servo()
{
	if(mode == Auto)
	{
		double time = millis() % period;
		double omega = 2 * PI / period;
		double angle = time * omega;
		double amplitude = (max_duty - min_duty)/2;
		int duty = (min_duty + amplitude) + amplitude * sin(angle);
		ledcWrite(channel, duty);
	} else {
		int duty = map(POT_value, 0, 4095, min_duty, max_duty);
		ledcWrite(channel, duty);
	}
}

void 
update_eyes()
{
	digitalWrite(LED_pin, HIGH);
	// double time = millis() % period_blink;
	// if(time < (0.8*period_blink)) {
	// 	digitalWrite(LED_pin,HIGH);
	// } else {
	// 	digitalWrite(LED_pin,LOW);
	// } 

}


void 
update_LCD()
{
	// if (day_time == Day) {
	// 	lcd.setCursor(0,0);
	// 	lcd.print("Dia: Voando");

	// } else if (day_time == NightFall) {
	// 	lcd.setCursor(0,0);
	// 	lcd.print("Noite: Fugindo");
	// } else {
	// 	lcd.setCursor(0,0);
	// 	lcd.print("Noite: Dormindo");
	// }

	// if(mode == Manual) {
	// 	lcd.setCursor(0,1);
	// 	lcd.print("Modo: Manual");
	// } else {
	// 	lcd.setCursor(0,1);
	// 	lcd.print("Modo: Auto");
	// }
}

void
receive_command()
{
	String command; // variável para o dado recebido
	if (Serial.available() > 0) {
        // lê do buffer o dado recebido:
        command = Serial.readString();

        // responde com o dado recebido:
        Serial.print("I received: ");
        Serial.println(command);
      }
}