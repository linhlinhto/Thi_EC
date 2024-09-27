void Mission1(){
  unsigned int obstacledist = 200;
  while(!LbIRLine.isBlackDetected()){
    LbMotion.runLR(mspeedL, mspeedR);
  }
  unsigned int d = Leanbot.pingCm();
  while( LbIRLine.isBlackDetected()) {
    if( d >= 5  ){
      followLine();
      d = Leanbot.pingCm();
    }
    else if(d < 5){
      
      LbMotion.runLR(0,0);
      int eyeleft = irScan(ir6L, obstacledist);
      int eyeright = irScan(ir7R, obstacledist);
      if(eyeleft < eyeright){
        LbMotion.runRotationDeg(-SPEED_MAX/2, SPEED_MAX/2, -45);
        while(!LbIRLine.isBlackDetected()){
        LbMotion.runLR(SPEED_MAX, SPEED_MAX/3);
      }
      }
      else{
        LbMotion.runRotationDeg(SPEED_MAX/2, -SPEED_MAX/2, 45);
        while(!LbIRLine.isBlackDetected()){
        LbMotion.runLR(SPEED_MAX/3, SPEED_MAX);
        }
      }
    }
  }
  mspeedL = 2000;
  mspeedR = 2000;
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(43);
  LbGripper.close();
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(43);
  LbMotion.runRotationDeg(-mspeedL, mspeedR, -90);
  mission1sucess = true;

}
