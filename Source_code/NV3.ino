


//I wanna comment it more, but now im out of mind with ifelsing

#include <Leanbot.h>
  int SPEED_MAX = 1000;             // run at a maximum speed of 1000
  int SPEED_4   = 0.8 * SPEED_MAX;  // run at 80% speed
  int SPEED_3   = 0.6 * SPEED_MAX;  // run at 60% speed
  int SPEED_2   = 0.4 * SPEED_MAX;  // run at 40% speed
  int SPEED_1   = 0.2 * SPEED_MAX;  // run at 20% speed
  int SPEED_0   = 0.0 * SPEED_MAX;  // stop
  unsigned int minSonic = 4; //cm
  unsigned int dist0; //Tay -> sonic
  unsigned int centerDist; //Edge -> mid of da square
  unsigned int normal_speed = 0.5 * SPEED_MAX; // Avarage speed
//Mission3
void mission3(){
  LbMission.start();
  LbMotion.waitRotationDeg(180);
  followLine();
  if(junctionSpot() != 0x00){
    method1();
  }
  LbMission.stop();
}
//wtf is going with this block?
void method1(){
  doStuff();
  if(junctionSpot() != 0x00){
    LbMotion.waitRotationDeg(+90);
    followLine();
    LbMotion.waitRotationDeg(-90);
    if(junctionSpot() != 0x00){
      LbMotion.waitRotationDeg(-90);
      followLine();
      if(endOfLineSpot()){
        LbGripper.open();
        LbMotion.waitRotationDeg(180);
        followLine();
        if(junctionSpot() != 0x00){
          LbMotion.waitRotationDeg(-90);
          followLine();
          if(endOfLineSpot){
            LbMotion.waiDistance(centerDist);
          }
        }
      }
    }
  }
}
//and this block?
void method2(){
  followLine();
  if(endOfLineSpot()){
  LbMotion.waitRotationDeg(180);
  followLine();
  if(junctionSpot != 0x00){
    followLine();
    if(junctionSpot != 0x00){
      doStuff();
      if(endOfLineSpot()){
        LbGripper.open();
        LbMotion.waitRotationDeg(180);
        if(junctionSpot() != 0x00){
          LbMotion.waitRotationDeg(90);
          followLine();
          if(junctionSpot() != 0x00){
            LbMotion.waitRotationDeg(-90);
            followLine();
            if(endOfLineSpot){
              LbMotion.waiDistance(centerDist);
            }
          }
        }
      }
    }
  }
  }

}
//Spot and rescue da victim
void doStuff(){
  char dir = 0; //-1 = right, 1 = left
  bool gotDist = false;
  unsigned int backwardSpeed = 0; // Tốc độ cà giật lùi của xe
  if(irScan(ir6)){
    dir = -1;
  }
  else if(irScan(ir7)){
    dir = 1; 
  }
  LbMotion.waitRotationDeg(dir * 90);
  while(!gotDist){
  unsigned int dist = Leanbot.pingCm();
  gotDist = (dist >= minSonic)?true:false;
  LbMotion.runLR(-backwardSpeed, -backwardSpeed);
  
  }
  LbMotion.waitDistance(dist - dist0);
  LbGripper.close();
  LbMotion.waitRotationDeg(180);
  junctionSpot();
  LbMotion.waitRotationDeg(dir * 90);
  
}
//By its name, spot da junction
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
//By its name, spot line whether it's the dead end
boolean endOfLineSpot(){
    bool state = LbIRLine.read();
    return state&&0x0000; //4 line IR Sensors are all 0 
}

//Surely, it's for line following
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