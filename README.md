# Sistema de Monitoramento para Vinharia Angello 🍷

## 📝Descrição

Este projeto visa criar um dispositivo preciso para o monitoramento da temperatura 🌡️, umidade 💧 e luminosidade ☀️ do ambiente, a fim de garantir a qualidade do vinho. 

O sistema utiliza sensores DHT11 para medir a temperatura e a umidade, e um sensor LDR para medir a luminosidade. 

Através do controle desses parâmetros, é possível criar um ambiente ideal para a produção e armazenamento de vinho, assegurando condições ótimas que promovam o desenvolvimento adequado da bebida.

## 🛠️ Materiais Necessários

| Quantidade| Componente | 
|---------- |----------|
| 1         | Arduino Uno R3   |
|1          | DHT 11            |
| 1         | LCD 16x2        |
| 1    | LDR (Fotorresistor)   | 
|1     | Resistor de 10 kOhm|
|5     | Resistores de 220 Ohm|
|1     | LED Vermelho |
|1     |LED Amarelo|
|1     |LED Verde|
|1     |Buzzer (Buzina)|
|      |Fios (Jumpers)|
|1     |Protoboard|


## 📌  Funcionamento do Projeto

O projeto consiste em ler continuamente as leituras dos sensores DHT11 e LDR e calcular a média das últimas 5 leituras para temperatura, umidade e luminosidade. Com base nas leituras médias, o Arduino toma as seguintes ações:

### Indicação no Display LCD:
- Exibe a temperatura, umidade e luminosidade no display LCD.

- Mostra mensagens indicando se as condições de temperatura, umidade e luminosidade estão dentro dos limites ideais.
  
### Controle dos LEDs e Buzzer:
- Se a temperatura estiver entre 10°C e 15°C, a umidade estiver entre 50% e 70% e a luminosidade estiver abaixo de 25, o LED verde é aceso para indicar condições ideais.
  
- Se a temperatura estiver fora da faixa de 10°C a 15°C ou a luminosidade estiver entre  25 e 50, o LED amarelo é aceso e o buzzer é acionado.
  
-Se a umidade estiver fora da faixa de 30% a 90% ou a luminosidade estiver acima de 50, o LED vermelho é aceso e o buzzer é acionado.

## Como Montar o circuito

Conecte o sensor DHT11 ao Arduino:
Conecte o pino de dados do sensor DHT11 ao pino digital 13 do Arduino.
Conecte o pino de alimentação (VCC) do sensor ao pino 5V do Arduino.
Conecte o pino de terra (GND) do sensor ao pino GND do Arduino.
Conecte o sensor LDR ao Arduino:
Conecte um terminal do LDR a uma porta analógica (A0) do Arduino.
Conecte o outro terminal do LDR a uma resistência de pull-down de 10kΩ.
Conecte o lado da resistência de pull-down ao GND do Arduino.
Conecte o display LCD ao Arduino:
Conecte o pino VSS do LCD ao GND do Arduino.
Conecte o pino VDD do LCD ao 5V do Arduino.
Conecte o pino V0 do LCD a um potenciômetro para ajuste de contraste.
Conecte os pinos RS, RW e E do LCD aos pinos 7, 6 e 5 do Arduino, respectivamente.
Conecte os pinos D4 a D7 do LCD aos pinos 4 a 3 do Arduino, respectivamente.
Conecte os LEDs e o Buzzer ao Arduino:
Conecte os LEDs verde, amarelo e vermelho aos pinos 8, 9 e 10 do Arduino, respectivamente.
Conecte o Buzzer ao pino 12 do Arduino.
Monte o circuito em uma protoboard seguindo o esquemático fornecido.
