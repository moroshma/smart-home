#include "IRremote.h"
IRrecv irrecv(D8);
decode_results results;
int led1=0;
int led2=0;
void setup() {
  pinMode(D4,OUTPUT);
  pinMode(RX,OUTPUT);

  Serial.begin(9600);
  irrecv.enableIRIn();
}
void loop() {
  if ( irrecv.decode( &results )) { 
    Serial.println(results.value, HEX);
    
if (results.value==0xFF30CF&&led1==0){
  digitalWrite( 3, HIGH );led1=1;results.value=0;
}
if (results.value==0xFF30CF&&led1==1){
  digitalWrite( 3, LOW );led1=0;results.value=0;
}   

if (results.value==0xFF18E7&&led2==0){
  digitalWrite( 9, HIGH );led2=1;results.value=0;
}
if (results.value==0xFF18E7&&led2==1){
  digitalWrite( 9, LOW );led2=0;results.value=0;
}
 irrecv.resume();   
  }
  
}
