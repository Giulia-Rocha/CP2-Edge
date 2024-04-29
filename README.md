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

## 🧩 Como Montar o circuito

- Conecte o sensor DHT11 ao Arduino:
  - Conecte o pino de dados do sensor DHT11 ao pino digital 13 do Arduino.
  - Conecte o pino de alimentação (VCC) do sensor ao pino 5V do Arduino.
  - Conecte o pino de terra (GND) do sensor ao pino GND do Arduino.
- Conecte o sensor LDR ao Arduino:
  - Conecte um terminal do LDR a uma porta analógica (A0) do Arduino.
  - Conecte o outro terminal do LDR a uma resistência de pull-down de 10kΩ.
  - Conecte o lado da resistência de pull-down ao GND do Arduino.
- Conecte o display LCD ao Arduino:
  - Conecte o pino VSS do LCD ao GND do Arduino.
  - Conecte o pino VDD do LCD ao 5V do Arduino.
  - Conecte o pino V0 do LCD a um potenciômetro para ajuste de contraste.
  - Conecte os pinos RS, RW e E do LCD aos pinos 7, 6 e 5 do Arduino, respectivamente.
  - Conecte os pinos D4 a D7 do LCD aos pinos 4 a 3 do Arduino, respectivamente.
- Conecte os LEDs e o Buzzer ao Arduino:
  - Conecte os LEDs verde, amarelo e vermelho aos pinos 8, 9 e 10 do Arduino, respectivamente.
  - Conecte o Buzzer ao pino 12 do Arduino.
- Monte o circuito em uma protoboard seguindo o esquemático fornecido.
- Utilize a imagem a seguir para facilitar a montagem:
  <details>
    <summary>Imagem do circuito:</summary>
    <img src="Circuito_CP2"  />
  </details>
  
 ## 💻 Como Instalar e Executar o Código
### Opção 1: Instalação da IDE do Arduino (Para quem possui o Arduino fisicamente)
  - Baixe e instale a IDE do Arduino em seu computador a partir do site oficial (https://www.arduino.cc/en/software), seguindo as instruções de instalação para o seu sistema operacional.
  - Abra a IDE do Arduino após a instalação.
  - Crie um novo projeto na IDE do Arduino.
  - Copie o [código fornecido](codigo-fonte.cpp) neste projeto e cole na janela do editor da IDE.
  - Conecte o Arduino ao seu computador usando um cabo USB.
  - Selecione o tipo de placa Arduino e a porta serial correta na IDE do Arduino.
  - Compile o código clicando em "Verificar" (ícone de visto) na barra de ferramentas da IDE.
  - Faça o upload do código para o Arduino clicando em "Carregar" (ícone de seta para a direita) na barra de ferramentas da IDE.
  - Após o upload, você verá as leituras de temperatura, umidade e luminosidade sendo exibidas no display LCD e os LEDs e o buzzer indicando as condições ambientais.
### Opção 2: Utilização do WOKWI para Montagem Online (Para quem deseja simular o projeto sem possuir o Arduino fisicamente)
  - Acesse o site do WOKWI em https://wokwi.com/arduino.
  - Crie uma conta gratuita no WOKWI ou faça login, se já tiver uma conta.
  - Na interface do WOKWI, clique em "Create New Project" para criar um novo projeto.
  - Cole o [código fornecido](codigo-fonte.cpp) neste projeto na área de edição do código.
  - Arraste e solte os componentes necessários (Arduino Uno, DHT22, LDR, LCD, LEDs, Buzzer) da biblioteca de componentes do WOKWI para a área de trabalho.
  - Será necessário mudar para DHT22, pois a plataforma não disponibiliza o DHT11, porém, a unica mudança é a precisão na leitura.
  - Conecte os pinos dos componentes de acordo com o esquemático fornecido neste projeto.
  - Simule o projeto clicando no botão "Start Simulation" na barra de ferramentas do WOKWI.
  - Após a simulação, você verá as leituras de temperatura, umidade e luminosidade sendo exibidas na simulação, juntamente com a indicação dos LEDs e do buzzer conforme as condições ambientais.

## 🖋️ Autores
[Giulia Rocha](https://github.com/Giulia-Rocha)
[Leonardo Rocha]()
[Gustavo Viega]()
