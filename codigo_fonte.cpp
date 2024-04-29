#include <Wire.h>  // Inclui a biblioteca Wire para comunicação I2C
#include <DHT.h>  // Inclui a biblioteca DHT para o sensor de temperatura e umidade
#include <LiquidCrystal.h>  // Inclui a biblioteca LiquidCrystal para o controle do LCD
#include <Adafruit_RGBLCDShield.h>  // Inclui a biblioteca Adafruit_RGBLCDShield para o controle do shield LCD RGB
#include <utility/Adafruit_MCP23017.h>  // Inclui a biblioteca Adafruit_MCP23017 para a expansão de pinos I2C

Adafruit_RGBLCDShield Lcd = Adafruit_RGBLCDShield();  // Cria um objeto para controlar o LCD RGB

#define DHTPIN 13      // Define o pino digital ao qual o sensor DHT está conectado
//Para usar DHT 22, como no WOKWI, é só mudar para DHT22
#define DHTTYPE DHT11  // Define o tipo de sensor DHT (DHT 11)

DHT dht(DHTPIN, DHTTYPE);  // Cria um objeto para controlar o sensor DHT
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // Cria um objeto para controlar o LCD

// Definições de caracteres personalizados para o LCD
byte thermometerSymbol[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

byte humiditySymbol[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
  B00000
};

byte sun[8] = {
  B00100,
  B10101,
  B11111,
  B01110,
  B11111,
  B10101,
  B00100
};

byte logo[8][8] = {
  { B11111, B11111, B11111, B11110, B11110, B11100, B11000, B00000 },
  { B00001, B00011, B00111, B01111, B11000, B11000, B11111, B11111 },
  { B11111, B11111, B11111, B11111, B00000, B00000, B10011, B10011 },
  { B10000, B11000, B11100, B11110, B00011, B00011, B11111, B11111 },
  { B11111, B11111, B11111, B11111, B01111, B00111, B00011, B00000 },
  { B10011, B10011, B10011, B10001, B11000, B11111, B11111, B00000 }
};

int redPin = 10;  // Define o pino conectado ao LED vermelho
int yellowPin = 9;  // Define o pino conectado ao LED amarelo
int greenPin = 8;  // Define o pino conectado ao LED verde
int buzzerPin = 12;  // Define o pino conectado ao buzzer
int ldrPin = A0;  // Define o pino conectado ao sensor de luminosidade
float mediaTemp, mediaUmid, mediaLuz;  // Declara as variáveis para armazenar as médias de temperatura, umidade e luminosidade

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial com uma taxa de 9600 bps
  pinMode(redPin, OUTPUT);  // Configura o pino do LED vermelho como saída
  pinMode(yellowPin, OUTPUT);  // Configura o pino do LED amarelo como saída
  pinMode(greenPin, OUTPUT);  // Configura o pino do LED verde como saída
  pinMode(buzzerPin, OUTPUT);  // Configura o pino do buzzer como saída

  lcd.begin(16, 2);  // Inicializa o LCD com 16 colunas e 2 linhas

  // Carrega caracteres personalizados na memória do LCD
  for (int i = 0; i < 6; i++) {
    lcd.createChar(i, logo[i]);
  }

  displayLogo();  // Exibe o logo animado no LCD
  lcd.clear();  // Limpa o LCD

  // Define caracteres personalizados para o LCD
  lcd.createChar(0, thermometerSymbol);  // Caractere personalizado para o termômetro
  lcd.createChar(1, humiditySymbol);  // Caractere personalizado para a umidade
  lcd.createChar(2, sun);  // Caractere personalizado para o sol

  dht.begin();  // Inicializa o sensor DHT
}

void loop() {
  LerVariaveis();  // Lê as variáveis do sensor DHT e do sensor de luminosidade
  Serial.println(mediaLuz);  // Imprime a média da luminosidade no monitor serial
  verifica(mediaTemp, mediaUmid, mediaLuz);  // Verifica as condições do ambiente
  mostrarTempUmid();  // Mostra as informações de temperatura e umidade no LCD
}

void displayLogo() {
  // Limpa o LCD
  lcd.clear();

  // Exibe o logo animado
  lcd.setCursor(0, 0);
  lcd.print("Tech Nova");  // Mostra o nome da empresa
  lcd.setCursor(1, 5);
  lcd.print("Solutions");

  // Exibe os caracteres personalizados na tela
  lcd.setCursor(15, 1);
  lcd.write(byte(0));
  lcd.setCursor(13, 0);
  lcd.write(byte(1));
  lcd.setCursor(14, 0);
  lcd.write(byte(2));
  lcd.setCursor(15, 0);
  lcd.write(byte(3));
  lcd.setCursor(13, 1);
  lcd.write(byte(4));
  lcd.setCursor(14, 1);
  lcd.write(byte(5));

  delay(3000);  // Aguarda 3 segundos para exibir o logo
}

void LerVariaveis() {
  float somaTemp = 0, somaUmid = 0, somaLuz = 0;  // Variáveis para somar as leituras
  float temp[5], umid[5], luz[5];  // Arrays para armazenar as leituras dos sensores

  // Realiza leituras dos sensores e calcula a média
  for (int i = 0; i < 5; i++) {
    temp[i] = dht.readTemperature();  // Lê a temperatura
    umid[i] = dht.readHumidity();  // Lê a umidade
    luz[i] = map(analogRead(ldrPin), 1023, 0, 0, 100);  // Lê a luminosidade
  }

  // Calcula a soma das leituras
  for (int i = 0; i < 5; i++) {
    somaTemp += temp[i];
    somaUmid += umid[i];
    somaLuz += luz[i];
  }

  // Calcula a média das leituras
  mediaTemp = somaTemp / 5;
  mediaUmid = somaUmid / 5;
  mediaLuz = somaLuz / 5;

  delay(5000);  // Aguarda 5 segundos
}

void verifica(float mediaTemp, float mediaUmid, float mediaLuz) {
  // Verifica as condições do ambiente e controla os LEDs e o buzzer
  if (mediaLuz <= 25 && mediaTemp >= 10 && mediaTemp <= 15 && mediaUmid >= 50 && mediaUmid <= 70) {
    digitalWrite(greenPin, HIGH);  // Liga o LED verde
    digitalWrite(yellowPin, LOW);  // Desliga o LED amarelo
    digitalWrite(redPin, LOW);  // Desliga o LED vermelho
    noTone(buzzerPin);  // Desativa o buzzer
  } else if (mediaLuz > 50 || mediaUmid < 30 || mediaUmid > 90) {
    digitalWrite(greenPin, LOW);  // Desliga o LED verde
    digitalWrite(yellowPin, LOW);  // Desliga o LED amarelo
    digitalWrite(redPin, HIGH);  // Liga o LED vermelho
    tone(buzzerPin, 1000);  // Ativa o buzzer com uma frequência de 1000 Hz
  } else if (mediaTemp < 10 || mediaTemp > 15) {
    digitalWrite(greenPin, LOW);  // Desliga o LED verde
    digitalWrite(yellowPin, HIGH);  // Liga o LED amarelo
    digitalWrite(redPin, LOW);  // Desliga o LED vermelho
    tone(buzzerPin, 1000);  // Ativa o buzzer com uma frequência de 1000 Hz
  } else {
    digitalWrite(greenPin, LOW);  // Desliga o LED verde
    digitalWrite(yellowPin, HIGH);  // Liga o LED amarelo
    digitalWrite(redPin, LOW);  // Desliga o LED vermelho
    noTone(buzzerPin);  // Desativa o buzzer
  }
}

void mostrarTempUmid() {
  // Exibe as informações de temperatura, umidade e luminosidade no LCD

  // Exibe os símbolos de temperatura, umidade e luminosidade no LCD
  lcd.setCursor(0, 0);
  lcd.write(byte(0));  // Exibe o símbolo do termômetro
  lcd.print(mediaTemp);

  lcd.setCursor(0, 1);
  lcd.write(byte(1));  // Exibe o símbolo de umidade
  lcd.print(mediaUmid);

  lcd.setCursor(10, 0);
  lcd.write(byte(2));  // Exibe o símbolo do sol
  lcd.print(mediaLuz);
  delay(3000);  // Aguarda 3 segundos

  lcd.clear();  // Limpa o LCD

  // Exibe mensagens de acordo com as condições do ambiente
  if (mediaTemp >= 10 && mediaTemp <= 15) {
    lcd.setCursor(0, 0);
    lcd.print("Temp OK ");
    lcd.setCursor(1, 1);
    lcd.print(mediaTemp);
    lcd.write(0xDF);  // Exibe o símbolo de grau Celsius
    lcd.print("C");
  } else if (mediaTemp > 15) {
    lcd.setCursor(0, 0);
    lcd.print("Temp Alta ");
    lcd.setCursor(1, 1);
    lcd.print(mediaTemp);
    lcd.write(0xDF);  // Exibe o símbolo de grau Celsius
    lcd.print("C");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp Baixa ");
    lcd.setCursor(1, 1);
    lcd.print(mediaTemp);
    lcd.write(0xDF);  // Exibe o símbolo de grau Celsius
    lcd.print("C");
  }

  delay(2000);  // Aguarda 2 segundos
  lcd.clear();  // Limpa o LCD

  if (mediaUmid >= 50 && mediaUmid <= 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK ");
    lcd.setCursor(1, 1);
    lcd.print(mediaUmid);
    lcd.print("%");
  } else if (mediaUmid > 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Alta ");
    lcd.setCursor(1, 1);
    lcd.print(mediaUmid);
    lcd.print("%");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Baixa ");
    lcd.setCursor(1, 1);
    lcd.print(mediaUmid);
    lcd.print("%");
  }

  delay(2000);  // Aguarda 2 segundos
  lcd.clear();  // Limpa o LCD

  if (mediaLuz < 25) {
    lcd.setCursor(0, 0);
    lcd.print("Luminosidade");
    lcd.setCursor(0, 1);
    lcd.print("Ideal!");
  } else if (mediaLuz >= 25 && mediaLuz <= 50) {
    lcd.setCursor(0, 0);
    lcd.print("Ambiente a ");
    lcd.setCursor(1, 1);
    lcd.print("meia Luz!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Ambiente");
    lcd.setCursor(1, 1);
    lcd.print("MUITO CLARO");
  }

  delay(2000);  // Aguarda 2 segundos
  lcd.clear();  // Limpa o LCD
}
