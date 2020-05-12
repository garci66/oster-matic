#include <Encoder.h>
#define ENCODER_USE_INTERRUPTS
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <AutoPID.h>
#include "TKLCDL.h"
#include "sousvide-lcd-encoder.h"

TKLCDL lcd=TKLCDL();

double temperature;
double pidTemperature;
double bottomTemp;
double pulseValue;
unsigned long lastTempUpdate; //tracks clock time of last temp update
unsigned long printLoop, serialPrintLoop=0;
unsigned long adjustTimer=0;
unsigned long bottomTempADC;
unsigned long lastDebounceTime=0;
bool lastButtonState=true;
long knobPosition=0;

bool usingBottom=false;


OneWire oneWire(TEMPPIN);
DallasTemperature tempSensor(&oneWire);
double setPoint=60.0;

bool relayStatus=false;
bool localRelayStatus=false;
float myTemp=0.0;  
char keyRead;

Encoder myKnob(ENCODER1A, ENCODER1B);


AutoPIDRelay myPID(&pidTemperature, &setPoint, &relayStatus,RELAY_PULSE, KP, KI, KD);
//AutoPIDRelay(double *input, double *setpoint, bool *relayState, double pulseWidth, double Kp, double Ki, double Kd)

bool updateTemperature() {
  if ((millis() - lastTempUpdate) > TEMP_READ_DELAY) {
    temperature = tempSensor.getTempCByIndex(0); //get temp reading
    lastTempUpdate = millis();
    tempSensor.requestTemperatures(); //request reading for next time
    analogRead(BOTTOMTEMPPIN);
    delay(10);
    bottomTemp=ntcAdcToTemp(analogRead(BOTTOMTEMPPIN));
    pidTemperature=usingBottom?bottomTemp:temperature;
    return true;
  }
  return false;
}

double ntcAdcToTemp(unsigned long adcValue){
  // 'y = -1.4843E-04x2 + 7.0989E-02x + 8.1006E+01
  //Serial.println(localADC);
  return (81.006 - 1.4843E-04 * pow(adcValue,2) + 7.0989E-02*adcValue);
}

void updateLcd(){
    pulseValue= myPID.getPulseValue();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("S:");
    lcd.print(setPoint);
    lcd.setCursor(8,0);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.setCursor(15,0);
    lcd.print(usingBottom?"_":"*");
    lcd.setCursor(0,1);
    lcd.print("R:");
    lcd.print(relayStatus?"*":" ");
    lcd.print(pulseValue);
    lcd.setCursor(8,1);
    lcd.print("B:");
    lcd.print(bottomTemp);
    lcd.setCursor(15,1);
    lcd.print(usingBottom?"*":"_");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAYPIN, OUTPUT);
  pinMode(BOTTOMTEMPPIN, INPUT);
  pinMode(ENCODER_BUTTON, INPUT_PULLUP);
  
  lcd.begin();
  lcd.clear();
  
  tempSensor.begin();
  if (tempSensor.getDS18Count() <1) {
    Serial.println("Temperature read timed out!!!");
  }
  tempSensor.setResolution(11);
  tempSensor.requestTemperatures();

  while (!updateTemperature()) {} 
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("Finished init");
  
  myPID.setBangBang(0.5);
  myPID.setTimeStep(1000);

  lcd.setCursor(0,0);
  lcd.print("S:");
  lcd.print(setPoint);
  lcd.setCursor(8,0);
  lcd.print("T:");
  lcd.setCursor(0,1);
  lcd.print("R:");
  lcd.setCursor(8,1);
  lcd.print("B:");
}

void loop() {
  bool myRead=digitalRead(ENCODER_BUTTON);
  if (myRead != lastButtonState) {
    if(!myRead ){
      lastDebounceTime = millis();
      lastButtonState=false;
    } else if (lastDebounceTime==0){
      lastButtonState=true;
    }
  }
  if (lastDebounceTime>0 && ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)) {
    if(!myRead){
      usingBottom=!usingBottom;
    }
    lastDebounceTime=0;
  }
  
  myPID.run();
  knobPosition = myKnob.readAndReset();
  if (knobPosition!=0) {
    Serial.println(knobPosition);
    setPoint+=knobPosition*(0.25/4);
    lcd.setCursor(2,0);
    lcd.print(setPoint);
  }
  updateTemperature();

  if (millis()>printLoop+PRINTLOOPTIME){
    printLoop=millis();
    pulseValue= myPID.getPulseValue();
    analogWrite(RELAYPIN, relayStatus?128:0);
    updateLcd();
  }
 
  if (millis()>serialPrintLoop+SERIALPRINTLOOPTIME){
    serialPrintLoop=millis();
    //digitalWrite(RELAYPIN,relayStatus);
    //analogTemp=analogRead(SETPOINTPIN);
    //Serial.print(tempSetPointADC);
    //Serial.print(" ");
    Serial.print(bottomTempADC);
    Serial.print(" ");
    Serial.print(temperature);
    Serial.print(" ");
    Serial.print(pulseValue);
    Serial.print(" ");
    Serial.print(relayStatus);
    Serial.print(" ");
    Serial.print(setPoint);  
    Serial.print(" ");
    Serial.print(bottomTemp);
    Serial.print(" ");
    Serial.println(usingBottom);
  }
  
  if (Serial.available()) {
     keyRead=Serial.read();
     switch (keyRead)
     {
        case 'r':
          Serial.print("toggle relay ");
          localRelayStatus= !localRelayStatus;
          Serial.println(localRelayStatus);
          //digitalWrite(RELAYPIN,localRelayStatus);
          analogWrite(RELAYPIN, localRelayStatus?128:0);
          break;
        case 'f':
          setPoint+=0.25;
          if (setPoint >90)
            setPoint=90.0;
          break;
        case 's':
          setPoint-=0.25;
          if (setPoint < 30)
            setPoint=30.0;
          break;
     }

  }

}
