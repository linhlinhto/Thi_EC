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
unsigned int normal_speed = 0.5 * SPEED_MAX; // Avarage speed

unsigned int rotate90SpeedL;
unsigned int rotate90SpeedR;
unsigned int rotate180SpeedL;
unsigned int rotate180SpeedR;

unsigned int lineWidth; 
unsigned int juncToObjDist;

unsigned int minSonic = 4; //cm
unsigned int dist0; //Tay -> sonic
unsigned int centerDist = 43; //Edge -> mid of da square
unsigned int noIRValue = 760;
int mspeedL = 2000;              // khong duoc thay doi tham so o day
int mspeedR = 2000;               // khong duoc thay doi tham so o day
bool mission1sucess = false;      // khong duoc thay doi tham so o day
bool mission2sucess = false;      // khong duoc thay doi tham so o day
bool mission3sucess = false;      // khong duoc thay doi tham so o day
bool mission4sucess = false;      // khong duoc thay doi tham so o day

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Leanbot.begin();                      // initialize Leanbot
  Serial.begin(9600);
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
  while(!endOfLineSpot()){
    LbMotion.runLR(mspeedL, mspeedR);
  }
  unsigned int d = Leanbot.pingCm();
  while(endOfLineSpot()) {
    if( d >= minSonic  ){
      followLine();
      d = Leanbot.pingCm();
    }
    else if(d < minSonic){
      
      LbMotion.runLR(0,0);
      int eyeleft = irScan(ir6L, obstacledist);
      int eyeright = irScan(ir7R, obstacledist);  
      if(eyeleft < eyeright){
        LbMotion.runRotationDeg(-mspeedL, mspeedR, -45);
        while(!endOfLineSpot()){
        LbMotion.runLR(mspeedL, mspeedR/3);
      }
      }
      else{
        LbMotion.runRotationDeg(mspeedL, -mspeedR, 45);
        while(!endOfLineSpot()){
        LbMotion.runLR(mspeedL/3, mspeedR);
        }
      }
    }
  }
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(centerDist);
  LbGripper.close();
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(43);
  LbMotion.runRotationDeg(-mspeedL, mspeedR, -90);
  mission1sucess = true;

}



void Mission2(){

}

void Mission3(){
  LbMotion.runRotationDeg(-rotate180SpeedL, +rotate180SpeedR, 180);
  // LbMotion.waitRotationDeg(180);
  while(!junctionSpot()){followLine();}
  method1();
}

void Mission4(){
  LbMotion.runLR(mspeedL, mspeedR);
  int distanceleft = LbIRArray.read(ir6L);        // doc gia tri cacm bien
  int distanceright = LbIRArray.read(ir7R);
  while(distanceleft >= noIRValue && distanceright >= noIRValue){   // cho den khi vao duong di
    distanceleft = LbIRArray.read(ir6L);      
    distanceright = LbIRArray.read(ir7R);     // kiem tra lai gia tri
  }
  while(distanceleft < noIRValue && distanceright < noIRValue){     // khi da vao duong di
    distanceleft = LbIRArray.read(ir6L);
    distanceright = LbIRArray.read(ir7R);     // kiem tra lai gia tri

    if(distanceleft< distanceright - 10){       // neu ben trai gan hon
      mspeedR = SPEED_0;                        
      mspeedL = SPEED_MAX;             //giam toc do banh phai
    }

    else if(distanceright< distanceleft - 10){     // neu ben phai gan hon
      mspeedR = SPEED_MAX;
      mspeedL = SPEED_0;            // giam toc do banh trai
    }

    else{          //  neu bang nhau
      mspeedR = SPEED_MAX;
      mspeedL = SPEED_MAX;   //   toc do 2 banh bang nhau
    }

    LbMotion.runLR(mspeedL, mspeedR);  //  dat toc do cho 2 banh 
  }

  LbMotion.waitDistanceMm(centerDist);   //  sau khi het duong phai ne di them 2 cm de den giua o dich
  LbMotion.runLR(0, 0);  //  dung xe
  mission4sucess = true;  
}

void method1(){
  doStuff();
  while(!junctionSpot()){followLine();}
  LbMotion.runRotationDeg(+rotate90SpeedL, -rotate90SpeedR, +90);
  // LbMotion.waitRotationDeg(+90);
  while(!junctionSpot()){followLine();}
  LbMotion.runRotationDeg(-rotate90SpeedL, +rotate90SpeedR, -90);
  // LbMotion.waitRotationDeg(-90);
  while(!junctionSpot()){followLine();}
  LbMotion.runRotationDeg(-rotate90SpeedL, +rotate90SpeedR, -90);
  // LbMotion.waitRotationDeg(-90);
  while(!endOfLineSpot()){followLine();}
  LbMotion.runLR(0, 0);
  LbGripper.open();
  LbMotion.runRotationDeg(-rotate180SpeedL, +rotate180SpeedR, 180);
  while(!junctionSpot()){followLine();}
  LbMotion.runRotationDeg(-rotate90SpeedL, +rotate90SpeedR, -90);
  // LbMotion.waitRotationDeg(-90);
  while(!endOfLineSpot()){followLine();}
  LbMotion.waiDistance(centerDist);
  }
       

void method2(){
  while(!endOfLineSpot()){followLine();}
  LbMotion.waitRotationDeg(180);
  while(!junctionSpot()){followLine();}
  printItOut("First junc!");
  LbMotion.waitDistance(lineWidth);
  while(!junctionSpot()){followLine();}
  printItOut("Second junc!");
  doStuff();
  while(!endOfLineSpot()){followLine();}
  LbGripper.open();
  LbMotion.runRotationDeg(-rotate180SpeedL, +rotate180SpeedR, 180);
  // LbMotion.waitRotationDeg(180);
  while(!junctionSpot()){followLine();}
  LbMotion.runRotationDeg(+rotate90SpeedL, -rotate90SpeedR, +90);
  // LbMotion.waitRotationDeg(90);
  while(!junctionSpot()){followLine();}
  LbMotion.runRotationDeg(-rotate90SpeedL, +rotate90SpeedR, -90);
  // LbMotion.waitRotationDeg(-90);
  while(!endOfLineSpot()){followLine();}
      LbMotion.waiDistance(centerDist);
}
//Spot and rescue da victim
void doStuff(){
  char dir = 0; //-1 = right, 1 = left
  if(irScan(ir6)){
    dir = -1;
  }
  else if(irScan(ir7)){
    dir = 1; 
  }
  LbMotion.runRotationDeg(dir * rotate90SpeedL, -dir * rotate90SpeedR, dir * 90);
  // LbMotion.waitRotationDeg(dir * 90);
  LbMotion.waitDistance(juncToObjDist);
  LbGripper.close();
  LbMotion.runRotationDeg(-rotate180SpeedL, +rotate180SpeedR, 180);
  // LbMotion.waitRotationDeg(180);
  while(!junctionSpot()){followLine();}
  LbMotion.runRotationDeg(dir * rotate90SpeedL, -dir * rotate90SpeedR, dir * 90);
  // LbMotion.waitRotationDeg(dir * 90);
  
}

void followLine(){
  byte line = LbIRLine.read(50);  // Read the value of 4 bar sensors with a threshold of 50
  LbIRLine.println(line);         // transfer the results to the computer

  switch (line) {                 // check the location of Leanbot
    case 0b0000:
    case 0b0110:
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      break;


    case 0b0100:
      LbMotion.runLR(SPEED_MAX, SPEED_3);
      break;

    case 0b1100:
      LbMotion.runLR(SPEED_MAX, SPEED_2);
      break;

    case 0b1000:
      LbMotion.runLR(SPEED_MAX, SPEED_0);
      break;


    case 0b0010:
      LbMotion.runLR(SPEED_3, SPEED_MAX);
      break;

    case 0b0011:
      LbMotion.runLR(SPEED_2, SPEED_MAX);
      break;

    case 0b0001:
      LbMotion.runLR(SPEED_0, SPEED_MAX);
      break;


    case 0b1111:
      LbMotion.runLR(SPEED_0, SPEED_0);
      break;
  }
}

boolean endOfLineSpot(){
  if(!endOfLineSpot()){
    printItOut("Line State: " + LbIRLine.read());
    return true;
  }
  printItOut("Line State: " + LbIRLine.read());
  return false;
}


boolean junctionSpot(){
    if(irScan(ir4L, 50)){
        printItOut("JunctionSpot: Left"); // Left line existing
        if(irScan(ir5R, 50)){
            printItOut("JunctionSpot: Left and Right"); // 2 side lines existing
            return true;
        }
        return true;
    }
    else if(irScan(ir5R, 50)){
        printItOut("JunctionSpot: Right"); //Right line existing
        return true;
    }
    return false; //Return no side lines existing by default
}
//Scan with a customized threshold
boolean irScan(eLbIRSensor irX, unsigned int threshold){
  int value = LbIRArray.read(irX);
  if(value >= threshold){
    return true;
  }
  return false;
  
}

void printItOut(String msg){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    Serial.println(msg);
  }
}
