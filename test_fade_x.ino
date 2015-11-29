/* 
  Increase LED Brightness with Reset

  Each press of the gb increases the LED brightness by 10%.
  Press and hold the gb for 3 seconds to reset the LED to 0%.
 
  created 2012
  by Aaron Van Bokhoven
*/

const int gbPin = 40;           // number of the gb pin
const int greenPin = 9;              // number of the LED pin
const int rbPin = 42;           // number of the rb pin
const int redPin = 10;              // number of the LED pin
const int bbPin = 44;           // number of the rb pin
const int bluePin = 11;              // number of the LED pin
const int fPin = 46;           // number of the rb pin
const int resetVarPin = 50;

const int DelayPlusPin = 32;    // increase Delaytime Var
const int DelayMinusPin = 30;  // decrease Delaytime Var

const int LowBrightMinusPin = 47;    //lowbright down
const int LowBrightPlusPin = 45;    //lowbright up
const int FullBrightMinusPin = 43;  //fullbright down
const int FullBrightPlusPin = 41;  //fullbright up


int DelayStatePlus = 0;
int DelayStateMinus = 0;

int LBplusState = 0;
int LBminusState = 0;
int FBplusState = 0;
int FBMinusState = 0;

int fadeWait = 0;
int fadeThird = 0;
int fadeHalf = 0;
int fadeForth = 0;
int gFadeWait = 0;
int rFadeWait = 0;
int bFadeWait = 0;

int rbrightCheck = 0;
int gbrightCheck = 0;
int bbrightCheck = 0;

int Rx = 0;
int Bx = 0;
int Gx = 0;

int RxHigh = 0;
int BxHigh = 0;
int GxHigh = 0;

int rCounter = 0;
int gCounter = 0;
int bCounter = 0;
int startloop = 0;
int gbright = 0;
int gLastbright = 0;

int fullbright = 255;
int lowBright = 0;
int fadeVar = 5;


int rbright = 0;
int rLastbright = 0;
int bbright = 0;
int bLastbright = 0;

int brightness = 0; // brightness of LED starts at 0

int fadeAmount = 0;         // fadeAmount is equal to 10% of 255(max LED brightness)
int rfadeAmount = 1; 
int gfadeAmount = 1; 
int bfadeAmount = 1; 



int transfade = 1;
int delaytime =20;

int fadeState = 0;              // gb state starts at 0
int fadePressedCounter = 0;     // timer set to 0 whe depressing gb
int fadeCounter = 0;            // gb counter set to 0
int fadeLastState = 0;          // gb last state set to 0

int gbState = 0;              // gb state starts at 0
int gbPressedCounter = 0;     // timer set to 0 whe depressing gb
int gbCounter = 0;            // gb counter set to 0
int gbLastState = 0;          // gb last state set to 0
int rVarState = 0;           // reset vars state

int rbState = 0;              // rb state starts at 0
int rbPressedCounter = 0;     // timer set to 0 whe depressing rb
int rbLastState = 0;          // rb last state set to 0

int  rbCounter =0;
int bFullRCounter =0;

int bbState = 0;              // rb state starts at 0
int bbPressedCounter = 0;     // timer set to 0 whe depressing rb
int bbCounter = 0;            // rb counter set to 0
int bbLastState = 0;          // rb last state set to 0

int fadeAmountHalf = 0;


void setup() {
  // set gb as input
  pinMode(gbPin, INPUT);
  // set LED as output
  pinMode(greenPin, OUTPUT);
  // init serialize communication at 9600 bits per second
  pinMode(rbPin, INPUT);
  // set LED as output
  pinMode(redPin, OUTPUT);
  // init serialize communication at 9600 bits per second
  
  pinMode(bbPin, INPUT);
  // set LED as output
  pinMode(bluePin, OUTPUT);
  // init serialize communication at 9600 bits per second
  pinMode(fPin, INPUT);
  // set LED as output  
  pinMode(resetVarPin, INPUT);
  // set LED as output    
  
  
  
  Serial.begin(9600);
}

void loop() {
  // get gb state
  gbState = digitalRead(gbPin);
  rbState = digitalRead(rbPin);
  bbState = digitalRead(bbPin);
  fadeState = digitalRead(fPin);
  rVarState = digitalRead(resetVarPin);
  DelayStatePlus = digitalRead(DelayPlusPin);
  DelayStateMinus = digitalRead(DelayMinusPin);

  LBplusState =  digitalRead(LowBrightPlusPin);
  LBminusState = digitalRead(LowBrightMinusPin);
  FBplusState =  digitalRead(FullBrightPlusPin);
  FBMinusState = digitalRead(FullBrightMinusPin);
  
  
//greenbrightness();
//redbrightness();
//bluebrightness();

//greenbrightfade();
//redbrightfade();
//bluebrightfade();


redbluefade(); //RbState pin 42
bFullRfade(); //BbState pin 44
allcolorfade(); //FadeState pin 46



DelayTimeChange();

LowBrightControl();
//FullBrightControl();

//    Serial.print("LBplusState: ");
//    Serial.println(LBplusState);
//    Serial.print("LBminusState: ");
//    Serial.println(LBminusState);


if (rVarState == HIGH) {
    resetVars();
     while (rVarState == HIGH){
     rVarState = digitalRead(resetVarPin);  
    rbPressedCounter ++; // start counter
    Serial.print("Pressed Timer RB FADER: ");
    Serial.println(rbPressedCounter);
    rVarState = digitalRead(resetVarPin);  
  }
  } else { 
  rbPressedCounter = 0;
  }
 
}

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
void DelayTimeChange(){

 if (DelayStatePlus == HIGH) {
    delaytime = delaytime +5;
     while (DelayStatePlus == HIGH){
     DelayStatePlus = digitalRead(DelayPlusPin);  
    rbPressedCounter ++; // start counter
    Serial.print("delaytime: ");
    Serial.println(delaytime);
    DelayStatePlus = digitalRead(DelayPlusPin);  
  }
  } else { 
  rbPressedCounter = 0;
  }
if (DelayStateMinus == HIGH) {
    delaytime = delaytime -5;
    if (delaytime <= -1){
    delaytime = 0;
    }
     while (DelayStateMinus == HIGH){
     DelayStateMinus = digitalRead(DelayMinusPin);  
    rbPressedCounter ++; // start counter
    Serial.print("delaytime ");
    Serial.println(delaytime);
    DelayStateMinus = digitalRead(DelayMinusPin);  
  }
  } else { 
  rbPressedCounter = 0;
  }


}
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
void LowBrightControl(){
  
 if (LBplusState == HIGH) {
    lowBright = lowBright +5;
    if (lowBright >= 256){ lowBright = 255;}
     while (LBplusState == HIGH){
     LBplusState = digitalRead(LowBrightPlusPin);
    rbPressedCounter ++; // start counter
    Serial.print("lowbright: ");
    Serial.println(lowBright);
    LBplusState = digitalRead(LowBrightPlusPin);
  }
  } else { 
  rbPressedCounter = 0;
  }
  
 if (LBminusState == HIGH) {
    lowBright = lowBright -5;
    if (lowBright <= -1){ lowBright = 0;}
     while (LBminusState == HIGH){
     LBminusState = digitalRead(LowBrightMinusPin);
    rbPressedCounter ++; // start counter
    Serial.print("lowBright: ");
    Serial.println(lowBright);
    LBminusState = digitalRead(LowBrightMinusPin);
  }
  } else { 
  rbPressedCounter = 0;
  }


}

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

void resetVars(){
  startloop = 0;
  rCounter = 0;
  gCounter = 0;
  bCounter = 0;
  rbright = 0;
  gbright = 0;
  bbright = 0;
  Rx = 0;   
  Bx = 0; 
  Gx = 0; 

  RxHigh = 0;   
  BxHigh = 0; 
  GxHigh = 0;      

  bFullRCounter = 0; //reset redbluefade counter
  rbCounter =0; // reset bFullRfade counter
  fadeCounter = 0; // reset allcolorfade counter
  

  rbrightCheck = 0;
  gbrightCheck = 0;
  bbrightCheck = 0;
}

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

void redbluefade(){

analogWrite(redPin, rbright);
analogWrite(greenPin, gbright);
analogWrite(bluePin, bbright);


 if (rbState == HIGH) {
   
  resetVars();
  
  rbCounter = rbCounter + 1;
  fadeForth = fullbright /4;
  fadeHalf = fullbright / 2;

  

 fadeAmount =  fadeVar;         // fadeAmount is equal to 10% of 255(max LED brightness)
 rfadeAmount = fadeVar; 
 gfadeAmount = fadeVar; 
 bfadeAmount = fadeVar;

 fadeAmountHalf = fadeAmount*2;
 fadeWait = fullbright /fadeAmount;
  
  
 while (rbState == HIGH){
     rbState = digitalRead(rbPin);  
    rbPressedCounter ++; // start counter
    Serial.print("Pressed Timer RB FADER: ");
    Serial.println(rbPressedCounter);
    rbState = digitalRead(rbPin);  
  }
  } else { 
  rbPressedCounter = 0;
  }
  

 if (rbCounter == 1){

/*
Serial.print("R COUNT = ");
Serial.println(rCounter);

Serial.print("R BRIGHT = ");  
Serial.println(rbright);

Serial.print("RX = ");  
Serial.println(Rx);
Serial.println();


Serial.print("B COUNT = ");
Serial.println(bCounter);  

Serial.print("B BRIGHT = ");  
Serial.println(bbright);


Serial.print("BX = ");  
Serial.println(Bx);
Serial.println();






Serial.print("B BRIGHT = ");  
Serial.println(bbright);
Serial.println();

Serial.print("BX = ");  
Serial.println(Bx);
Serial.println();

Serial.print("B COUNT = ");
Serial.println(bCounter);  
Serial.println();

Serial.print("RX = ");  
Serial.println(Rx);
Serial.println();

Serial.print("R COUNT = ");
Serial.println(rCounter);  
Serial.println();

Serial.print(" FADE WAIT = ");  
Serial.println(fadeWait);
Serial.println();


Serial.print("R BRIGHT = ");  
Serial.println(rbright);
Serial.println();

*/



////////////////Start Cycle (red) //////////
   if(rCounter == 0){                         /////////Low to high 
      if (rbright <= fullbright){
   rbright = rbright + fadeAmount;
   Rx = Rx + fadeAmount;                      ///////count up Rx wait Var

      }
   }
   if ((rCounter == 3)&&(bCounter == 0)){
    bCounter =1;
   }
///////////(Blue)/////////////////////////

   if ((bCounter == 2) && (Bx >= lowBright+1)){   //////////// led High Wait time (half time it took to get from low to high)
   Bx = Bx - fadeAmountHalf; 
 
   }
   
   if ((bCounter == 2) && (Bx <= lowBright)){  //////////// Check if wait is over
    bCounter = 3;
   }
   
   if (bCounter == 3){                 ///////////Fade out led from High to Low
   if (bbright >= lowBright){
   bbright = bbright - fadeAmount;
  
     }
   }

    if (bCounter == 4){                ///////////// led Low Wait time (half time it took to get from High to low)
   Bx = Bx - fadeAmountHalf; 
   }
   
   if ((bCounter == 4) && (Bx <= lowBright)){
    bCounter = 1;
    Bx = lowBright;
   }


   if(bCounter == 1){
      if (bbright <= fullbright){
   bbright = bbright + fadeAmount;
   Bx = Bx + fadeAmount;
      }
   }
 
 //////////////CHECK Cycle State  HIGH  BLUE//////////////////////////// 

      if ((bbright >= fullbright)&& (Bx>=lowBright+1)){                //Check RED
   bCounter = 2;
   bbright = fullbright;
   } 

   
///////////(RED)/////////////////////////

   if ((rCounter == 2) && (Rx >= lowBright+1)){   //////////// led High Wait time (half time it took to get from low to high)
   Rx = Rx - fadeAmountHalf; 
 
   }
   
   if ((rCounter == 2) && (Rx <= lowBright)){  //////////// Check if wait is over
    rCounter = 3;
    Rx = lowBright;
    rbright = fullbright;
   }
   
   if (rCounter == 3){                 ///////////Fade out led from High to Low
   if (rbright >= lowBright){
   rbright = rbright - fadeAmount;
  
     }
   }

    if (rCounter == 4){                ///////////// led Low Wait time (half time it took to get from High to low)
   Rx = Rx - fadeAmountHalf; 
   }
   
   if ((rCounter == 4) && (Rx <= lowBright)){
   rCounter = 1;
   Rx = lowBright;
   }


   if(rCounter == 1){
      if (rbright <= fullbright){
   rbright = rbright + fadeAmount;
   Rx = Rx + fadeAmount;
      }
   }




 
 //////////////CHECK Cycle State  HIGH Red //////////////////////////// 

   
   if ((rbright >= fullbright)&& (Rx>=lowBright+1)){                //Check RED
   rCounter = 2;
   rbright = fullbright;
  
   }

 //////////////CHECK Cycle State  LOW ////////////////////////////
 
 if ((rbright <= lowBright ) && (rCounter == 3)){
   rCounter = 4;
   rbright = lowBright;
   Rx = fullbright;
   } 

   if ((bbright <= lowBright) && (bCounter == 3)){
   bCounter = 4;
   bbright = lowBright;
   Bx = fullbright;
   }  

   if ((gbright <= 1) && (gCounter == 3)){
   gCounter = 1;
   gbright = lowBright;
   }  




 }
 if (rbCounter > 1){
 rbCounter = 0;
 } 
  delay(delaytime);
}   

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

void bFullRfade(){

analogWrite(redPin, rbright);
analogWrite(greenPin, gbright);
analogWrite(bluePin, bbright);


 if (bbState == HIGH) {
  resetVars();
       
  
  fullbright = 150;
  lowBright = 30; 

  
  bFullRCounter = bFullRCounter + 1;
  fadeForth = fullbright /4;
  fadeHalf = fullbright / 2;
  

 fadeAmount =  fadeVar;         // fadeAmount is equal to 10% of 255(max LED brightness)
 rfadeAmount = fadeVar; 
 gfadeAmount = fadeVar; 
 bfadeAmount = fadeVar;

 fadeAmountHalf = fadeAmount*2;
 fadeWait = fullbright /fadeAmount;
  
  rbrightCheck = 0;
  gbrightCheck = 0;
  bbrightCheck = 0;
  
 while (bbState == HIGH){
     bbState = digitalRead(bbPin);  
    bbPressedCounter ++; // start counter
    Serial.print("Pressed Timer RB FADER: ");
    Serial.println(rbPressedCounter);
    bbState = digitalRead(bbPin); 
  }
  } else { 
  bbPressedCounter = 0;
  }
  

 if (bFullRCounter == 1){

/*Serial.print("R COUNT = ");
Serial.println(rCounter);

Serial.print("R BRIGHT = ");  
Serial.println(rbright);

Serial.print("RX = ");  
Serial.println(Rx);
Serial.println();


Serial.print("B COUNT = ");
Serial.println(bCounter);  

Serial.print("B BRIGHT = ");  
Serial.println(bbright);


Serial.print("BX = ");  
Serial.println(Bx);
Serial.println();






Serial.print("B BRIGHT = ");  
Serial.println(bbright);
Serial.println();

Serial.print("BX = ");  
Serial.println(Bx);
Serial.println();

Serial.print("B COUNT = ");
Serial.println(bCounter);  
Serial.println();

Serial.print("RX = ");  
Serial.println(Rx);
Serial.println();

Serial.print("R COUNT = ");
Serial.println(rCounter);  
Serial.println();

Serial.print(" FADE WAIT = ");  
Serial.println(fadeWait);
Serial.println();


Serial.print("R BRIGHT = ");  
Serial.println(rbright);
Serial.println();

*/



////////////////Start Cycle (red) //////////
   bbright = 255;
   if(rCounter == 0){                         /////////Low to high 
      if (rbright <= fullbright){
   rbright = rbright + fadeAmount;
   Rx = Rx + fadeAmount;                      ///////count up Rx wait Var

      }
   }
   
///////////(RED)/////////////////////////

   if ((rCounter == 2) && (Rx >= lowBright+1)){   //////////// led High Wait time (half time it took to get from low to high)
   Rx = Rx - fadeAmountHalf; 
 
   }
   
   if ((rCounter == 2) && (Rx <= lowBright)){  //////////// Check if wait is over
    rCounter = 3;
    Rx = lowBright;
    rbright = fullbright;
   }
   
   if (rCounter == 3){                 ///////////Fade out led from High to Low
   if (rbright >= lowBright){
   rbright = rbright - fadeAmount;
  
     }
   }

    if (rCounter == 4){                ///////////// led Low Wait time (half time it took to get from High to low)
   Rx = Rx - fadeAmountHalf; 
   }
   
   if ((rCounter == 4) && (Rx <= lowBright)){
   rCounter = 1;
   Rx = lowBright;
   }


   if(rCounter == 1){
      if (rbright <= fullbright){
   rbright = rbright + fadeAmount;
   Rx = Rx + fadeAmount;
      }
   }




 
 //////////////CHECK Cycle State  HIGH Red //////////////////////////// 

   
   if ((rbright >= fullbright)&& (Rx>=lowBright+1)){                //Check RED
   rCounter = 2;
   rbright = fullbright;
  
   }

 //////////////CHECK Cycle State  LOW ////////////////////////////
 
 if ((rbright <= lowBright ) && (rCounter == 3)){
   rCounter = 4;
   rbright = lowBright;
   Rx = fullbright;
   } 


 }
 if (bFullRCounter > 1){
 bFullRCounter = 0;
 } 
  delay(delaytime);
}   
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

void allcolorfade(){

analogWrite(redPin, rbright);
analogWrite(greenPin, gbright);
analogWrite(bluePin, bbright);


 if (fadeState == HIGH) {
  resetVars();
  startloop = 0;
  rCounter = 0;
  gCounter = 1;
  bCounter = 1;
  rbright = 0;
  gbright = 0;
  bbright = 0;   

  
  fadeCounter = fadeCounter + 1;
  fadeThird = fadeWait/3*2;
  fadeForth = fullbright /4;
  fadeHalf = fullbright / 2;
  
 fadeAmount =  fadeVar;         // fadeAmount is equal to 10% of 255(max LED brightness)
 rfadeAmount = fadeVar; 
 gfadeAmount = fadeVar; 
 bfadeAmount = fadeVar;
  
  rbrightCheck = 0;
  gbrightCheck = 0;
  bbrightCheck = 0;
  
 while (fadeState == HIGH){
     fadeState = digitalRead(fPin);  
    fadePressedCounter ++; // start counter
    Serial.print("Pressed Timer: ");
    Serial.println(fadePressedCounter);
    fadeState = digitalRead(fPin);  
  }
  } else { 
  fadePressedCounter = 0;
  }
  

 if (fadeCounter == 1){

   
/*
Serial.println("R BRIGHT");  
Serial.println(rbright);
Serial.println("R COUNT");
Serial.println(rCounter);
Serial.println("");   
Serial.println("B BRIGHT");  
Serial.println(bbright);
Serial.println("B COUNT");  
Serial.println(bCounter);   
Serial.println("");     

Serial.println("G BRIGHT");  
Serial.println(gbright);
Serial.println("g COUNT");  
Serial.println(gCounter);
*/



////////////////Start Cycle//////////
   if(rCounter == 0){
      if (rbright <= fullbright){
   rbright = rbright + rfadeAmount;
      }
   }

////////   FADE IN ///////////////////
   if ((gCounter == 2)&&(gbright >= fullbright)){
      gbrightCheck = 1;                          
   } 
      if ((rCounter == 1)&&(gbrightCheck == 1)){  
   rbright = rbright + rfadeAmount;    
  }    
 

  
   if ((rCounter == 2)&&(rbright  >= fullbright)){
      rbrightCheck = 1;
   } 
      if ((bCounter == 1)&&(rbrightCheck == 1)){  
   bbright = bbright + bfadeAmount;
       
  }
  
   
   if ((bCounter == 2)&&(bbright  >= fullbright)){
      bbrightCheck = 1;
   } 
      if ((gCounter == 1)&&(bbrightCheck == 1)){  
   gbright = gbright + gfadeAmount;
   } 
 
 
////////   FADE OUT ///////////////////
   if ((gCounter == 1)&&(gbright >= lowBright)){
      gbrightCheck = 2;         
   } 
      if ((rCounter == 2)&&(gbrightCheck == 2)){  
      rbright = rbright - rfadeAmount;   
  }    
 

  
   if ((rCounter == 1)&&(rbright >= lowBright)){
      rbrightCheck = 2;                          
   } 
      if ((bCounter == 2)&&(rbrightCheck == 2)){  
   bbright = bbright - bfadeAmount;    
  }  
  
   
   if ((bCounter == 1)&&(bbright >= lowBright)){
      bbrightCheck = 2;                          
   } 
      if ((gCounter == 2)&&(bbrightCheck == 2)){  
   gbright = gbright - gfadeAmount;    
  }  
 
 

//////////////CHECK Cycle State  LOW ////////////////////////////


 if ((rbright <= lowBright) && (rCounter == 2)){
   rCounter = 1;
   rbright = lowBright;
   } 

   if ((bbright <= lowBright) && (bCounter == 2)){
   bCounter = 1;
   bbright = lowBright;
   }  

   if ((gbright <= lowBright) && (gCounter == 2)){
   gCounter = 1;
   gbright = lowBright;
   }  
 
 
 
 //////////////CHECK Cycle State  HIGH //////////////////////////// 
   if (rbright >= fullbright){                //Check 
   rCounter = 2;
   rbright = fullbright;
   }
   
      if (bbright >= fullbright){                //Check 
   bCounter = 2;
   bbright = fullbright;
   }
      
      if (gbright >= fullbright){                //Check 
   gCounter = 2;
   gbright = fullbright;
   } 
   
   
 }
 if (fadeCounter > 1){
 fadeCounter = 0;
 } 
  delay(delaytime);
}    

