#include <Pin.h>
#include <ParallelLoop.h>

#define pinLed1 3
#define pinLed2 5
#define pinLed3 7
#define pinLed4 6
#define pinLed5 4
#define pinBotao1 8
#define pinBotao2 9
#define pinBotao3 10
#define pinBotao4 A1

ParallelLoop loop2;
ParallelLoop loop100(100); // Com ciclo de 100 milisegundos
ParallelLoop loop300(300); // Com ciclo de 300 milisegundos

Pin led1(pinLed1);
Pin led2(pinLed2);
Pin led3(pinLed3);
Pin led4(pinLed4);
Pin led5(pinLed5);
Pin botao1(pinBotao1);
Pin botao2(pinBotao2);
Pin botao3(pinBotao3);
Pin botao4(pinBotao4); // Poteciometro

void setup(){
  led1.setMode(OUTPUT);
  led2.setMode(OUTPUT);
  led3.setMode(OUTPUT);
  led4.setMode(OUTPUT);
  led5.setMode(OUTPUT);

  botao1.setMode(INPUT_PULLUP);
  botao2.setMode(INPUT_PULLUP);
  botao3.setMode(INPUT_PULLUP);
  botao4.setMode(INPUT);
}

void loop(){

  if(loop300.cycleLevel()){
    led1.writePwm(500);
  }else{
    led1.writePwm(100);
  }
	
  if(loop100.cycleLevel()){
    led2.write(HIGH);
  }else{
    led2.write(LOW);
  }

  if(botao1.readWithDebounce()){
    led3.write(HIGH);
  }else{
    led3.write(LOW);
  }

  // Usando controle do tempo
  if(loop2.timeRunning() > botao4.read()){
    led5.write(HIGH);
  }else{
    led5.write(LOW);
  }
  if(loop2.timeRunning() > (botao4.read() * 2)){
    loop2.resetTime();
  }

  // Controlar Pwm com poteciometro
  led4.writePwm(botao4.read());;
}
