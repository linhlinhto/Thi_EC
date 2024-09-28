#include <Leanbot.h>
 

 void setup(){
   Leanbot.begin();
  Serial.begin(115200);
 }

 void loop(){
   Serial.println("LbIRArray.read(ir7R)") ;
 }
