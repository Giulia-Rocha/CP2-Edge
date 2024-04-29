#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield Lcd = Adafruit_RGBLCDShield();

#define DHTPIN 13      // Pino digital conectado ao sensor DHT
#define DHTTYPE DHT22  // Tipo de sensor DHT (DHT 22)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

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

int redPin = 10;
int yellowPin = 9;
int greenPin = 8;
int buzzerPin = 12;
int ldrPin = A0;
float mediaTemp, mediaUmid, mediaLuz;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);  // Inicializa o LCD com 16 colunas e 2 linhas
  

  // Carrega caracteres personalizados na memória do LCD

   for (int i = 0; i < 6; i++) {
    lcd.createChar(i, logo[i]);
  }

  displayLogo();     // Exibe o logo animado
  lcd.clear();       // Limpa a tela do LCD

  lcd.createChar(0, thermometerSymbol); // Caractere personalizado para termômetro
  lcd.createChar(1, humiditySymbol);    // Caractere personalizado para umidade
  lcd.createChar(2, sun);
  // Inicializa o sensor DHT
  dht.begin();

}

void loop() {
  LerVariaveis();
  Serial.println(mediaLuz);
  verifica(mediaTemp, mediaUmid, mediaLuz);
  mostrarTempUmid();

}

void displayLogo() {
  // Limpa o LCD
  lcd.clear();
  
  // Exibe o logo animado
  lcd.setCursor(0, 0);
  lcd.print("Tech Nova"); //mostrando a logo
  lcd.setCursor(1,5);
  lcd.print("Solutions");

  
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
  delay(3000); // Tempo para exibição do logo
}

void LerVariaveis(){
	
	 float somaTemp =0, somaUmid = 0, somaLuz = 0;
	 float temp[5], umid[5],luz[5];
	 
	 //lendo as variaveis
	 for(int i=0;i<5;i++){
		 temp[i] = dht.readTemperature();
		 umid[i] = dht.readHumidity();
		 luz [i] = map(analogRead(ldrPin), 1023,0,0,100);
	 }
	 for (int i =0;i<5;i++){
		 somaTemp += temp[i];
		 somaUmid += umid[i];
		 somaLuz += luz[i];
	 }
	 mediaTemp = somaTemp/5;
	 mediaUmid = somaUmid/5;
	 mediaLuz =somaLuz/5;
	 delay(5000);
   
	 
}



void verifica(float mediaTemp, float mediaUmid, float mediaLuz){
	if (mediaLuz <= 25 && mediaTemp >= 10 && mediaTemp <= 15 && mediaUmid >= 50 && mediaUmid <= 70) {
    digitalWrite(greenPin, HIGH);  // Ambiente OK - Luz verde
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    noTone(buzzerPin);
} else if (mediaLuz > 50 ||  mediaUmid < 30 || mediaUmid > 90) {
    digitalWrite(greenPin, LOW);     // vermelho + buzzer->umidade e luz fora do normal
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);
    tone(buzzerPin, 1000);      // Ativa o buzzer por 1 segundo
} else if(mediaTemp<10 || mediaTemp>15){
    digitalWrite(greenPin, LOW);     //Amarelo + buzzer -> temp fora do normal
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, LOW);
    tone(buzzerPin, 1000);
}else{
	digitalWrite(greenPin, LOW);     //Amarelo + buzzer -> temp fora do normal
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, LOW);
    noTone(buzzerPin);
}


	
}

void mostrarTempUmid() {
  

  // Exibe símbolos de temperatura e umidade no LCD
  lcd.setCursor(0, 0);
  lcd.write(byte(0)); // Exibe o símbolo do termômetro
  lcd.print(mediaTemp);

  lcd.setCursor(0, 1);
  lcd.write(byte(1)); // Exibe o símbolo de umidade
  lcd.print(mediaUmid);

  lcd.setCursor(10, 0);
  lcd.write(byte(2));
  lcd.print(mediaLuz);
  delay(3000);
  lcd.clear();

  // Exibe mensagens de temperatura e umidade no Display
  if (mediaTemp >= 10 && mediaTemp <= 15) {
    lcd.setCursor(0, 0);
    lcd.print("Temp OK ");
    lcd.setCursor(1,1);
    lcd.print(mediaTemp);
    lcd.write(0xDF);
    lcd.print("C");
  } else if (mediaTemp > 15) {
    lcd.setCursor(0, 0);
    lcd.print("Temp Alta ");
    lcd.setCursor(1,1);
    lcd.print(mediaTemp);
    lcd.write(0xDF);
    lcd.print("C");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp Baixa ");
    lcd.setCursor(1,1);
    lcd.print(mediaTemp);
    lcd.write(0xDF);
    lcd.print("C");
    
  }
    delay(2000);
    lcd.clear();
  if (mediaUmid >= 50 && mediaUmid <= 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK ");
    lcd.setCursor(1,1);
    lcd.print(mediaUmid);
    lcd.print("%");
  } else if (mediaUmid > 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Alta ");
    lcd.setCursor(1,1);
    lcd.print(mediaUmid);
    lcd.print("%");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Baixa ");
    lcd.setCursor(1,1);
    lcd.print(mediaUmid);
    lcd.print("%");
  }
  delay(2000);
  lcd.clear();
  if (mediaLuz < 25) {
    lcd.setCursor(0,0);
    lcd.print("Luminosidade");
    lcd.setCursor(0,1);
    lcd.print("Ideal!");
    
  } else if (mediaLuz >= 25 && mediaLuz <= 50) {
    lcd.setCursor(0,0);
      lcd.print("Ambiente a ");
      lcd.setCursor(1,1);
      lcd.print("meia Luz!");
  } else {
    lcd.setCursor(0,0);
    lcd.print("Ambiente");
    lcd.setCursor(1,1);
    lcd.print("MUITO CLARO");
  }
  delay(2000);
  lcd.clear();
}
