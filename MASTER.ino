////MESTRE

#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(10,11);
String msg;
int btPin = 6;
int btState = 0;
int potVal=0;
int intVal = 0;
String ledVal = "";

void setup() {
  Serial.begin(9600);
  pinMode(btPin, INPUT);
  ArduinoSlave.begin(9600);
}

void loop() {
  potVal=analogRead(A0);
  btState = digitalRead(btPin);
  enviarMsg();

  Serial.print("Botão:");
  Serial.println(btState);

  Serial.print("Potênciometro:");
  Serial.println(potVal);

  ArduinoSlave.print(msg);
  receberMsg();

  delay(500);
}

void receberMsg() {
  while (ArduinoSlave.available() > 0){
    ledVal = ArduinoSlave.readStringUntil('\n');
    intVal = ledVal.toInt();
    if(intVal<20) {
      Serial.println("BAIXA LUMINOSIDADE");  
    }
  }  
}

void enviarMsg() {
  msg = String(btState);
  msg.concat("-");
  msg.concat(String(potVal));
  Serial.print("Mensagem: ");
  Serial.println(msg);
  msg.concat("\n");
}
