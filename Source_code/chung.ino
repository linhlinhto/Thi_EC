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

    if(distanceleft< distanceright-30){       // neu ben trai gan hon
      mspeedR = 0;                        
      mspeedL = 2000;             //giam toc do banh phai
    }

    else if(distanceright< distanceleft-30){     // neu ben phai gan hon
      mspeedR = 2000;
      mspeedL = 0;            // giam toc do banh trai
    }

    else{          //  neu bang nhau
      mspeedR = 2000;
      mspeedL = 2000;   //   toc do 2 banh bang nhau
    }

    LbMotion.runLR(mspeedL, mspeedR);  //  dat toc do cho 2 banh 
  }

  LbMotion.waitDistanceMm(2000);   //  sau khi het duong di them 2 cm de den giua o dich
  LbMotion.runLR(0, 0);  //  dung xe
  mission4sucess = true;  
}
