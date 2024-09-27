/*
  Basic Leanbot Motion

  Wait for TB1A+TB1B touch signal, then go straight for 100 mm, then stop.

  More Leanbot examples at  https://git.pythaverse.space/leanbot/Examples
*/


#include <Leanbot.h>                    // use Leanbot library

unsigned int SPEED_MAX = 2000;             // run at a maximum speed of 1000
unsigned int SPEED_4   = 0.8 * SPEED_MAX;  // run at 80% speed
unsigned int SPEED_3   = 0.6 * SPEED_MAX;  // run at 60% speed
unsigned int SPEED_2   = 0.4 * SPEED_MAX;  // run at 40% speed
unsigned int SPEED_1   = 0.2 * SPEED_MAX;  // run at 20% speed
unsigned int SPEED_0   = 0.0 * SPEED_MAX;  // stop
unsigned int minSonic = 4; //cm
unsigned int dist0; //Tay -> sonic
unsigned int centerDist = 43; //Edge -> mid of da square
unsigned int normal_speed = 0.5 * SPEED_MAX; // Avarage speed
int mspeedL = 2000;              // khong duoc thay doi tham so o day
int mspeedR = 2000;               // khong duoc thay doi tham so o day
bool mission1sucess = false;      // khong duoc thay doi tham so o day
bool mission2sucess = false;      // khong duoc thay doi tham so o day
bool mission3sucess = false;      // khong duoc thay doi tham so o day
bool mission4sucess = false;      // khong duoc thay doi tham so o day


void setup() {
  Leanbot.begin();                      // initialize Leanbot
}


void loop() {
  if(!mission1sucess){
    Mission1();
  }
  else if(mission1sucess && !mission2sucess ){
    Mission2();
  }
  else if(mission2sucess && !mission3sucess ){
    Mission3();
  }
  else if(mission3sucess && !mission4sucess){
    Mission4();
  }
}



void Mission1(){
  unsigned int obstacledist = 200;
  while(!LbIRLine.isBlackDetected()){
    LbMotion.runLR(mspeedL, mspeedR);
  }
  unsigned int d = Leanbot.pingCm();
  while( LbIRLine.isBlackDetected()) {
    if( d >= 5  ){
      runFollowLine();
      LbMotion.runLR(mspeedL, mspeedR);
      d = Leanbot.pingCm();
    }
    else if(d < 5){
      
      LbMotion.runLR(0,0);
      int eyeleft = irScan(ir6L, obstacledist);
      int eyeright = irScan(ir7R, obstacledist);
      if(eyeleft < eyeright){
        LbMotion.runRotationDeg(-mspeedL, mspeedR, -45);
        while(!LbIRLine.isBlackDetected()){
        LbMotion.runLR(mspeedL, mspeedR/3);
      }
      }
      else{
        LbMotion.runRotationDeg(mspeedL, -mspeedR, 45);
        while(!LbIRLine.isBlackDetected()){
        LbMotion.runLR(mspeedL/3, mspeedR);
        }
      }
    }
  }
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(43);
  LbGripper.close();
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(43);
  LbMotion.runRotationDeg(-mspeedL, mspeedR, -90);
  mission1sucess = true;

}



void Mission2(){

}

void Mission3(){
  
}

void Mission4(){
  LbMotion.runLR(mspeedL, mspeedR);
  int distanceleft = LbIRArray.read(ir6L);        // doc gia tri cacm bien
  int distanceright = LbIRArray.read(ir7R);
  while(distanceleft >= 760 && distanceright >= 760){   // cho den khi vao duong di
    distanceleft = LbIRArray.read(ir6L);      
    distanceright = LbIRArray.read(ir7R);     // kiem tra lai gia tri
  }
  while(distanceleft < 760 && distanceright < 760){     // khi da vao duong di
    distanceleft = LbIRArray.read(ir6L);
    distanceright = LbIRArray.read(ir7R);     // kiem tra lai gia tri

    if(distanceleft< distanceright-10){       // neu ben trai gan hon
      mspeedR = 0;                        
      mspeedL = 2000;             //giam toc do banh phai
    }

    else if(distanceright< distanceleft-10){     // neu ben phai gan hon
      mspeedR = 2000;
      mspeedL = 0;            // giam toc do banh trai
    }

    else{          //  neu bang nhau
      mspeedR = 2000;
      mspeedL = 2000;   //   toc do 2 banh bang nhau
    }

    LbMotion.runLR(mspeedL, mspeedR);  //  dat toc do cho 2 banh 
  }

  LbMotion.waitDistanceMm(centerDist);   //  sau khi het duong phai ne di them 2 cm de den giua o dich
  LbMotion.runLR(0, 0);  //  dung xe
  mission4sucess = true;  
}


void followLine(){
  byte line = LbIRLine.read(50);  // Read the value of 4 bar sensors with a threshold of 50
  LbIRLine.println(line);         // transfer the results to the computer

  switch (line) {                 // check the location of Leanbot
    case 0b0000:
    case 0b0110:
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      break;


    case 0b0010:
      LbMotion.runLR(SPEED_MAX, SPEED_3);
      break;

    case 0b0011:
      LbMotion.runLR(SPEED_MAX, SPEED_2);
      break;

    case 0b0001:
      LbMotion.runLR(SPEED_MAX, SPEED_0);
      break;


    case 0b0100:
      LbMotion.runLR(SPEED_3, SPEED_MAX);
      break;

    case 0b1100:
      LbMotion.runLR(SPEED_2, SPEED_MAX);
      break;

    case 0b1000:
      LbMotion.runLR(SPEED_0, SPEED_MAX);
      break;


    case 0b1111:
      LbMotion.runLR(SPEED_0, SPEED_0);
      break;
  }
}

void runFollowLine() {
  byte lineValue = LbIRLine.read();      // Read the value of 4 line sensors
  LbIRLine.displayOnRGB(CRGB::DarkCyan); // Display the result on RGB Leds for observation
 
  switch (lineValue) {                   // check the position of the black line relative to Leanbot
    case 0b0100:                         // .o.. - if the black line off to the left
      mspeedL = 1500;
      mspeedR = 2000;                     
      break;
    case 0b1110:                         // ooo.
      mspeedL = 1000;
      mspeedR = 2000;                     //        turn left
      break;

    case 0b1100:                         // oo..
      mspeedL = 1000;
      mspeedR = 2000; 
      break; 
    case 0b1000:                         // o...
      mspeedL = -2000;
      mspeedR = 2000;  
      break;

    case 0b0010:                         // ..o. - if the black line off to the right
      mspeedL = 2000;
      mspeedR = 1500; 
      break;
    case 0b0111:                         // .ooo
      mspeedL = 2000;
      mspeedR = 1000;         //        turn right
      break;

    case 0b0011:                         // ..oo
      mspeedL = 2000;
      mspeedR = 1000; 
      break;
    case 0b0001:                         // ...o
      mspeedL = 2000;
      mspeedR = -2000;        //        spin right
      break;
    case 0b0110:                         // ...o
      mspeedL = 2000;
      mspeedR = 2000;        //        spin right
      break; 
      
    default:                             // all other cases
      mspeedL = 2000;
      mspeedR = 2000;   //        go straight
  }
}

byte junctionSpot(){
    byte state = 0x00;
    if(irScan(ir4L, 50)){
        state = 0x10; // Left line existing
        if(irScan(ir5R, 50)){
            state = 0x11; // 2 side lines existing
        }
    }
    else if(irScan(ir5R, 50)){
        state = 0x01; //Right line existing
    }
    return state; //Return no side lines existing by default
}
//Scan with a customized threshold
boolean irScan(eLbIRSensor irX, int threshold){
  int value = LbIRArray.read(irX);
  if(value >= threshold){
    return true;
  }
  return false;
  
}
