#include <Leanbot.h>                    // use Leanbot library

unsigned int SPEED_MAX = 2000;             // run at a maximum speed of 1000
unsigned int SPEED_4   = 0.8 * SPEED_MAX;  // run at 80% speed
unsigned int SPEED_3   = 0.6 * SPEED_MAX;  // run at 60% speed
unsigned int SPEED_2   = 0.4 * SPEED_MAX;  // run at 40% speed
unsigned int SPEED_1   = 0.2 * SPEED_MAX;  // run at 20% speed
unsigned int SPEED_0   = 0.0 * SPEED_MAX;  // stop

bool mission4flag = false;

void setup() {
  Leanbot.begin();                // initialize Leanbot
  Serial.begin(115200);
}



void Mission4(){
  LbMotion.runLR(SPEED_MAX,SPEED_MAX);
  int distanceleft = LbIRArray.read(ir6L);        // doc gia tri cam bien
  int distanceright = LbIRArray.read(ir7R);
   LbMotion.waitDistanceMm(43);
 
  Serial.println(distanceleft);
  Serial.println(distanceright);
  while(true){
    distanceleft = LbIRArray.read(ir6L);        // doc gia tri cam bien
    distanceright = LbIRArray.read(ir7R);
    Serial.println(distanceleft);
    Serial.println(distanceright);
    if(distanceleft < distanceright-30){       // neu ben trai gan hon
      Serial.println("banh trai gan hon");
      LbMotion.runLR(SPEED_MAX,SPEED_0);               //giam toc do banh phai
    }

    else if(distanceright< distanceleft-30){     // neu ben phai gan hon
      Serial.println("banh phai gan hon");
      LbMotion.runLR(SPEED_0,SPEED_MAX);
                 // giam toc do banh trai
    }

    else{          //  neu bang nhau
      LbMotion.runLR(SPEED_MAX,SPEED_MAX);
        //   toc do 2 banh bang nhau
    }
    if(distanceleft > 760 && distanceright > 760){
      break;
    } 
  }
  LbMotion.waitDistanceMm(85);
  LbMotion.runLR(SPEED_0,SPEED_0);
  mission4flag = true;

  }

void loop(){
  if(mission4flag == false){
  Mission4();
  }
}

