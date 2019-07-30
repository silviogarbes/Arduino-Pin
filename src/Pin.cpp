#include <Pin.h> // Inclui a declaração
// Inclui bibliotecas padrão
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Arduino.h>

#if defined(ARDUINO_AVR_UNO)
//Uno specific code
static const int pinAnalogMin = A0;
static const int pinAnalogMax = A5;
#else
#error Unsupported hardware
#endif

// (0) analog, (1) digital
Pin::Pin(int aux){
  number = aux;
  if((number >= pinAnalogMin) && (number <= pinAnalogMax)){
    isDigital = false;
  } else{
    isDigital = true;
  }
}
// Somente se quiser usar uma porta analogica como digital
void Pin::setToDigital(){
  isDigital = true;
}
// (0) INPUT, (1) OUTPUT, (2) INPUT_PULLUP
void Pin::setMode(byte aux){
  mode = aux;
  pinMode(number,mode);
  if(mode == 2){
    level = HIGH;
    lastLevel = HIGH;
    trigger = level;
  }
}
// Tempo de debounce, default is 50 ms
void Pin::setDebounceDelay(unsigned long aux){
  debounceDelay = aux;
}
// digitalRead |LOW|HIGH|FALLING|RISING| ou analogRead 0 - 500
int Pin::read(){
  if(isDigital){
    bool currentLevel = digitalRead(number);
    trigger = level;
    if (currentLevel != level) {
      if(level == HIGH && currentLevel == LOW){
        trigger = FALLING;
      }
      if(level == LOW && currentLevel == HIGH){
        trigger = RISING;
      }
      level = currentLevel;
    }
    return trigger;
  }else{
    level = map(analogRead(number), 0, 1023, 0, 500);
    return level;
  }
}
// digitalRead com debounce |LOW|HIGH|FALLING|RISING|
byte Pin::readWithDebounce(){
  bool currentLevel = digitalRead(number);
  trigger = level;
  if (currentLevel != lastLevel) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentLevel != level) {
      if(level == HIGH && currentLevel == LOW){
        trigger = FALLING;
      }
      if(level == LOW && currentLevel == HIGH){
        trigger = RISING;
      }
      level = currentLevel;
    }
  }
  lastLevel = currentLevel;
  return trigger;
}
// Tempo rodando neste level
unsigned long Pin::readTimeRunningLevel(){
  bool currentLevel = digitalRead(number);
  if (currentLevel != level) {
    millisLastLevel = millis();
    level = currentLevel;
  }
  return millis() - millisLastLevel;
}
// Tempo rodando no ultimo level
int Pin::readTimeLastLevel(){
  bool currentLevel = digitalRead(number);
  if (currentLevel != level) {
    timeLastLevel = millis() - millisLastLevel;
    millisLastLevel = millis();
    level = currentLevel;
  }
  return timeLastLevel;
}
// Contador de pulso
int Pin::readPulseCount(){
  bool currentLevel = digitalRead(number);
  if (currentLevel != level) {
    countPulse++;
    level = currentLevel;
  }
  return countPulse;
}
// Reinicia contador de pulso
void Pin::resetPulse(){
  countPulse = 0;
}
// digitalWrite 0 ou 1
void Pin::write(bool aux){
  level = aux;
  digitalWrite(number, level);
}
// analogWrite 0 - 500
void Pin::writePwm(int aux){
  level = aux;
  analogWrite(number, map(aux, 0, 500, 0, 255));
}
