
#include <Leanbot.h>

int SPEED_MAX = 1000;             // run at a maximum speed of 1000
int SPEED_4   = 0.8 * SPEED_MAX;  // run at 80% speed
int SPEED_3   = 0.6 * SPEED_MAX;  // run at 60% speed
int SPEED_2   = 0.4 * SPEED_MAX;  // run at 40% speed
int SPEED_1   = 0.2 * SPEED_MAX;  // run at 20% speed
int SPEED_0   = 0.0 * SPEED_MAX;  // stop
unsigned long previousMillis = 0;
bool endOfLine= false;
const long interval = 1000;
void setup() {
  Serial.begin(115200);
  Leanbot.begin();                // initialize Leanbot
}

void Mission1(){
  LbMotion.runLR(SPEED_MAX, SPEED_MAX);
  LbMotion.waitDistanceMm(60);
  unsigned int d = Leanbot.pingCm();
  LbDelay(50);
  while(true) {
    d = Leanbot.pingCm();
    if(d < 10){
      LbMotion.runLR(0,0);  
      LbMotion.runRotationDeg(SPEED_MAX, -SPEED_MAX, 55);
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      LbMotion.waitDistanceMm(100);
      LbMotion.runRotationDeg(- SPEED_MAX, SPEED_MAX, -45);
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      LbMotion.waitDistanceMm(30);
      LbMotion.runRotationDeg(- SPEED_MAX, SPEED_MAX, -35);
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      while(LbIRLine.read(90) == 0);
      
    }
    else {
      followLine();
      
    }
    if(LbIRLine.read(90) == 0){
      break;
    }
    }
  LbGripper.open();  
  LbMotion.runLR(SPEED_MAX, SPEED_MAX);
  LbMotion.waitDistanceMm(6);
  LbMotion.runLR(0,0); 
  LbGripper.close();
  LbMotion.runLR(SPEED_MAX, SPEED_MAX);
  LbMotion.waitDistanceMm(40);
  LbMotion.runRotationDeg(-SPEED_MAX/2, SPEED_MAX/2, -90);

}



void followLine(){
  
  
  byte line = LbIRLine.read(90);  // Read the value of 4 bar sensors with a threshold of 50
  LbIRLine.println(line);         // transfer the results to the computer

  switch (line) {                 // check the location of Leanbot
    case 0b0000:
    case 0b0110:
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      break;


    case 0b0010:
      LbMotion.runLR(SPEED_MAX, SPEED_2);
      break;

    case 0b0011:
      LbMotion.runLR(SPEED_MAX, SPEED_0);
      break;

    case 0b0001:
      LbMotion.runLR(SPEED_MAX, -SPEED_1);
      break;


    case 0b0100:
      LbMotion.runLR(SPEED_2, SPEED_MAX);
      break;

    case 0b1100:
      LbMotion.runLR(SPEED_0, SPEED_MAX);
      break;

    case 0b1000:
      LbMotion.runLR(-SPEED_1, SPEED_MAX);
      break;
    

    case 0b1111:
      LbMotion.runLR(SPEED_2, SPEED_2);
      break;
    case 0b0111:
    LbMotion.runLR(SPEED_MAX*0.11,SPEED_0);
    break;
    case 0b1110:
    LbMotion.runLR(SPEED_0, SPEED_MAX*0.11);
    break;
  }
}

void loop() {
  Mission1();
  
}
