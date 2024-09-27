void Mission4(){
  LbMotion.runLR(mspeedL, mspeedR);
  int distanceleft = LbIRArray.read(ir6L);        // doc gia tri cam bien
  int distanceright = LbIRArray.read(ir7R);
  while(distanceleft >= 760 && distanceright >= 760){   // cho den khi vao duong di
    distanceleft = LbIRArray.read(ir6L);      
    distanceright = LbIRArray.read(ir7R);     // kiem tra lai gia tri
  }
  while(distanceleft < 760 && distanceright < 760){     // khi da vao duong di
    distanceleft = LbIRArray.read(ir6L);
    distanceright = LbIRArray.read(ir7R);     // kiem tra lai gia tri

    if(distanceleft< distanceright-5){       // neu ben trai gan hon
      mspeedR = 0;                        
      mspeedL = 2000;             //giam toc do banh phai
    }

    else if(distanceright< distanceleft-5){     // neu ben phai gan hon
      mspeedR = 2000;
      mspeedL = 0;            // giam toc do banh trai
    }

    else{          //  neu bang nhau
      mspeedR = 2000;
      mspeedL = 2000;   //   toc do 2 banh bang nhau
    }

    LbMotion.runLR(mspeedL, mspeedR);  //  dat toc do cho 2 banh 
  }

  LbMotion.waitDistanceMm(2000);   //  sau khi het duong phai ne di them 2 cm de den giua o dich
  LbMotion.runLR(0, 0);  //  dung xe
  mission4sucess = true;  
}
