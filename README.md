# passaro_embarcados

Esse repositório está sendo usado para guardar os códigos para o projeto de embarcados 1, em que será feito um passaro de papelão cujas asas movem utilizando um servomotor.

## Planejamento

- Uma carga simples acionada por saída digital. -> Leds para os olhos

- Uma carga controlada por PWM. -> Servo para controlar as asas

- Um sensor analógico ou digital com protocolo serial (como o DHT11, utilizado em sala de aula). -> Potênciometro que controla as asas

- Um sensor digital simples. -> Sensor de luz (quando chegar a noite voar para lugar seguro)

- Uma interface gráfica, como um display LCD. -> Avisar se luz insuficiente e modo atual

- Além disso, devem existir comandos inseridos pelo usuário (por exemplo, por monitor serial, por um 
aplicativo ou por uma plataforma web). -> Serial controla se o modo é manual ou automático