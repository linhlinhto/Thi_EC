/*
  Basic Leanbot Motion

  Wait for TB1A+TB1B touch signal, then go straight for 100 mm, then stop.

  More Leanbot examples at  https://git.pythaverse.space/leanbot/Examples
*/


#include <Leanbot.h>                    // use Leanbot library

int mspeedL = 2000;              // khong duoc thay doi tham so o day
int mspeedR = 2000;               // khong duoc thay doi tham so o day
bool mission1sucess = false;      // khong duoc thay doi tham so o day
bool mission2sucess = false;      // khong duoc thay doi tham so o day
bool mission3sucess = false;      // khong duoc thay doi tham so o day
bool mission4sucess = false;      // khong duoc thay doi tham so o day
int centdist = 43;


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


byte junctionSpot(){
    byte state = 0x00;
    if(irScan(ir4)){
        state = 0x10; // Left line existing
        if(irScan(ir7)){
            state = 0x11; // 2 side lines existing
        }
    }
    elif(irScan(ir5)){
        state = 0x01; //Right line existing
    }
    return state; //Return no side lines existing by default
}
//Scan with a customized threshold
boolean irScan(int irX){
  int threshold = 0; //Chỉnh threshold ở đây
  int value = LbIRArray.read(irX);
  if(value >= threshold){
    return true;
  }
  return false;
  
}

void Mission1(){
  while(!LbIRLine.isBlackDetected()){
    LbMotion.runLR(mspeedL, mspeedR);
  }
  unsigned int d = Leanbot.pingCm();
  while( LbIRLine.isBlackDetected()) {
    if( d >= 5  ){
      runFollowLine();
      LbMotion.runLR(mspeedL, mspeedR);
      d = Leanbot.pingCm();
      LbDelay(50);
    }
    else if(d < 5){
      
      LbMotion.runLR(0,0);
      int eyeleft = LbIRArray.read(ir6L);
      int eyeright = LbIRArray.read(ir7R);
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
  LbMotion.waitDistanceMm(cendist);
  LbGripper.close();
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(cendist);
  LbMotion.runRotationDeg(-mspeedL, mspeedR, -90);
  mission1sucess = true;

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

  LbMotion.waitDistanceMm(20);   //  sau khi het duong phai ne di them 2 cm de den giua o dich
  LbMotion.runLR(0, 0);  //  dung xe
  mission4sucess = true;  
}
