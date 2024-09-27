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
  LbMotion.waitDistanceMm(43);
  LbGripper.close();
  LbMotion.runLR(mspeedL, mspeedR);
  LbMotion.waitDistanceMm(43);
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
