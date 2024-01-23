// ESCRAVO
#include <SoftwareSerial.h>

SoftwareSerial ArduinoMaster(10, 11);
#define ledPin 8
String botao = "";
String pot = "";
String msgPot = "";
int ledVal = 0;
int intVal = 0;

void setup() {
  Serial.begin(9600);
  ArduinoMaster.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  receberMsg();

  if (botao == "1") {
    digitalWrite(ledPin, HIGH);
  } else {
    intVal = pot.toInt();
    ledVal = map(intVal, 0, 1023, 0, 255);
    analogWrite(ledPin, ledVal);
    if(ledVal<20) {
      Serial.println("BAIXA LUMINOSIDADE");
    }
  }

  
  delay(500);
}

void receberMsg() {
  while (ArduinoMaster.available() > 0) {
      botao = ArduinoMaster.readStringUntil('-');
      pot = ArduinoMaster.readStringUntil('\n');

      Serial.print("Botão: ");
      Serial.println(botao);

      Serial.print("Potênciometro: ");
      Serial.println(pot);

      msgPot = String(pot);
      msgPot.concat("\n");
      ArduinoMaster.print(msgPot);
  }
}       
