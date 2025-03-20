#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>
 
const int rs = 22, en = 23, d4 = 5, d5 = 18, d6 = 19, d7 = 21;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

static const int POT_pin   =  4; // entrada analogica
static const int button_pin   = 13; // leitura digital
static const int SERVO_pin = 12; // pwm
static const int LED_pin   = 14; // saida digital

static const int res       = 12;
static const int freq      = 50;
static const int channel   = 1;
// static const int T_high_ms = 2;
// static const int T_low_ms  = 1;

int POT_value    = 0;
int LDR_value    = 0; 
int period       = 1500; // em ms
int period_blink = 2000;

// static const int max_duty = (T_high_ms * freq * 4095 / 1000); 
// static const int min_duty = (T_low_ms * freq * 4095 / 1000); 
static const int min_duty = 211;
static const int max_duty = 300;

enum FLIGHT_MODE {Auto, Manual};
FLIGHT_MODE mode = Manual; 

enum COMPORTAMENTO {Dormindo, Voando};
COMPORTAMENTO comp = Voando; 

void read_pot();
void read_Button();
void update_servo();
void update_eyes();
void update_LCD();
void receive_command();

// put function declarations here:
void 
setup() 
{
	analogReadResolution(res); // pot
	pinMode(button_pin, INPUT_PULLUP); // ldr
	pinMode(LED_pin, OUTPUT);

	ledcSetup(channel, freq, res); // servo
	ledcAttachPin(SERVO_pin, channel);

	lcd.begin(16,2);

	Serial.begin(115200);
	Serial.println("------------------------");
	Serial.println("Modos: manual ou automatico");
	Serial.print("Digite o modo: ");
}

void 
loop() 
{
	// Sensores
	read_pot();
	read_Button();

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
read_Button() 
{
	LDR_value = digitalRead(button_pin);
	if(LDR_value == HIGH) {
		comp = Voando;
	} else {
		comp = Dormindo;
	}
}

void 
update_servo()
{
	if(mode == Auto)
	{
		const double amplitude = ((double) (max_duty - min_duty))/2;
		const int offset = (min_duty + amplitude);
		if(comp == Voando) {
			double time = millis() % period;
			double omega = 2 * PI / ((double) period);
			double angle = time * omega;
			int duty = offset + amplitude * sin(angle);
			ledcWrite(channel, duty);
		} else {
			ledcWrite(channel, offset);
		}
	} else {
		int duty = map(POT_value, 0, 4095, min_duty, max_duty);
		ledcWrite(channel, duty);
	}
}

void 
update_eyes()
{
	double time = millis() % period_blink;
	if(time < (0.8*period_blink)) {
		digitalWrite(LED_pin, HIGH);
	} else {
		digitalWrite(LED_pin, LOW);
	} 
}


void 
update_LCD()
{
	static FLIGHT_MODE mod_ant = mode;
	static COMPORTAMENTO comp_ant = comp;
	static int need_update = 1;

	if(comp != comp_ant) {
		comp_ant = comp;
		need_update = 1;
	}
	if(mode != mod_ant) {
		mod_ant = mode;
		need_update = 1;
	}
	if(need_update){
		need_update = 0;
		lcd.clear();
		if(comp == Voando) {
			lcd.print("Voando");
		} else {
			lcd.print("Dormindo...");
		}
		lcd.setCursor(0,1);
		if(mode == Manual) {
			lcd.print("Manual");
		} else {
			lcd.print("Automatico");
		}
	}
}

void
receive_command()
{
	static char str[100];
	static int i = 0;
	char c; // variável para o dado recebido
	if (Serial.available() > 0) {
        // lê do buffer o dado recebido:
        c = Serial.read();
		if(c == '\r') {
			// ignora
		} else if(c == '\n') {
			Serial.print(c);
			i = 0;
			if(strcmp(str, "manual") == 0) {
				Serial.println("Modo configurado para manual!");
				mode = Manual;
			} else if (strcmp(str,"automatico") == 0) {
				Serial.println("Modo configurado para automatico!");
				mode = Auto;
			} else {
				Serial.print("Modo ");
				Serial.print(str);
				Serial.println(" incorreto");
			}
			Serial.println("------------------------");
			Serial.println("Modos: manual ou automatico");
			Serial.print("Digite o modo: ");
		} else {
			Serial.print(c);
			str[i] = c;
			str[i+1] = '\0';
			i++;
		}
    }
}