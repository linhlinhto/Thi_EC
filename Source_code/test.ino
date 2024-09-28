void followLine(){
  byte line = LbIRLine.read(90);
  printItOut(String(line));   
  switch (line) {                 // check the location of Leanbot
    case 0b0000:
      printItOut("End of life");
      LbMotion.runLR(0, 0);
      break;
    case 0b0110:
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      break;


    case 0b0010:
      LbMotion.runLR(SPEED_MAX, SPEED_2);
      break;

    case 0b0011:
      LbMotion.runLR(SPEED_MAX, SPEED_1);
      break;

    case 0b0001:
      LbMotion.runLR(SPEED_MAX, -SPEED_3);
      break;


    case 0b0100:
      LbMotion.runLR(SPEED_2, SPEED_MAX);
      break;

    case 0b1100:
      LbMotion.runLR(SPEED_1, SPEED_MAX);
      break;

    case 0b1000:
      LbMotion.runLR(-SPEED_3, SPEED_MAX);
      break;


    case 0b1111:
      LbMotion.runLR(SPEED_1, SPEED_1);
      break;
    
    case 0b1010:
      LbMotion.runLR(SPEED_0, SPEED_MAX);
      break;

    case 0b0101:
      LbMotion.runLR( SPEED_MAX, SPEED_0);
      break;

    case 0b0111:
      LbMotion.runLR( SPEED_MAX,  SPEED_0);
      break;
    case 0b1110:
      LbMotion.runLR( SPEED_0, SPEED_MAX);
      break;
   }
}