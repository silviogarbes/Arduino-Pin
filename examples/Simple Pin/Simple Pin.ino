#include <Pin.h>

#define pinLed1 3
#define pinLed2 5
#define pinLed3 6
#define pinBotao1 8
#define pinBotao2 9
#define pinBotao3 10
#define pinBotao4 A1

Pin led1(pinLed1);
Pin led2(pinLed2);
Pin led3(pinLed3);
Pin botao1(pinBotao1);
Pin botao2(pinBotao2);
Pin botao3(pinBotao3);
Pin botao4(pinBotao4); // Poteciometro

void setup(){
  Serial.begin(115200);

  led1.setMode(OUTPUT);
  led2.setMode(OUTPUT);
  led3.setMode(OUTPUT);

  botao1.setMode(INPUT_PULLUP);
  botao2.setMode(INPUT_PULLUP);
  botao3.setMode(INPUT_PULLUP);
  botao4.setMode(INPUT);

  led1.write(HIGH);
  led2.write(HIGH);
}

void loop(){
  led1.writePwm(100);
  led2.writePwm(500);
  delay(200);
  led1.writePwm(500);
  led2.writePwm(100);
  
  Serial.print("read: ");
  Serial.println(botao1.read()); // |LOW|HIGH|FALLING|RISING|
  Serial.print("readWithDebounce: ");
  Serial.println(botao1.readWithDebounce()); // |LOW|HIGH|FALLING|RISING|
  
  botao1.readWithDebounce();
  
  delay(200);
  led1.writePwm(botao4.read());
  Serial.println(botao4.read()); // analogRead 0 - 500
}
