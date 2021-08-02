#include "Mouse.h"
#include "Keyboard.h"
#include "Adafruit_SSD1306.h"
//OLED
#define OLED_RESET 4
#define a1FLAKES 10
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Keys
#define Fn 1  //W
#define i2 0  //A
#define i3 7  //S
#define i4 8  //D
#define i5 16 //^
#define i6 4  //<
#define i7 19 //v
#define i8 15 //>
//Lights
#define Ln 5  //W
#define L2 6  //A
#define L3 9  //S
#define L4 18 //D
#define L5 10 //^
#define L6 21 //<
#define L7 20 //v
#define L8 14 //>
//OLED
void OLED(String KM = "", String LM = "",
          String S = "", String D = "", String UP = "",
          String LT = "", String DN = "", String RT = "") {
  display.clearDisplay();
  display.drawLine(0, 1, 127, 1, WHITE); //line_1
  display.drawLine(0, 16, 127, 16, WHITE); //line_2
  display.drawLine(0, 31, 127, 31, WHITE); //line_3
  display.drawLine(69, 1, 69, 31, WHITE); //row_1
  display.drawLine(89, 1, 89, 31, WHITE); //row_2
  display.drawLine(109, 1, 109, 31, WHITE); //row_3
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 5);
  display.println("KEY:" + KM);
  display.setCursor(2, 21);
  display.println("LIT:" + LM);
  display.setCursor(73, 5);
  display.println(S);
  display.setCursor(93, 5);
  display.println(UP);
  display.setCursor(112, 5);
  display.println(D);
  display.setCursor(73, 21);
  display.println(LT);
  display.setCursor(93, 21);
  display.println(DN);
  display.setCursor(112, 21);
  display.println(RT);
  display.display();
}
//body
void setup() {
//Keys
      pinMode(Fn,INPUT_PULLUP);
      pinMode(i2,INPUT_PULLUP);
      pinMode(i3,INPUT_PULLUP);
      pinMode(i4,INPUT_PULLUP);
      pinMode(i5,INPUT_PULLUP);
      pinMode(i6,INPUT_PULLUP);
      pinMode(i7,INPUT_PULLUP);
      pinMode(i8,INPUT_PULLUP);
//Lights
      pinMode(Ln,OUTPUT);
      pinMode(L2,OUTPUT);
      pinMode(L3,OUTPUT);
      pinMode(L4,OUTPUT);
      pinMode(L5,OUTPUT);
      pinMode(L6,OUTPUT);
      pinMode(L7,OUTPUT);
      pinMode(L8,OUTPUT);
      delay(500);
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      Mouse.begin();
}
void loop() { 
      String lm = "OFF", km = "Mouse",s = "LC", up = "UP", d = "RC", lt = "TL", dn = "DN", rt = "TR";
      int n = 0, n1 = 0, no = 5, no1 = 0, a1 = 0, a2 = 0, HL = 0, HL1 = 0, m2n = 0;
while(true){
  OLED(km, lm, s, d, up, lt, dn, rt);
  if(n1==0)
  mouse: Mouse_c();
//Light_Mode_Switch
          if (digitalRead(Fn) == 0)
          {
            HL = 0;
            L_RE(HL);
            if (n1 != 0)
            n++;
            delay(200);
          }
//Key_Mode_Switch
          if (digitalRead(i2) == 0)
          {
            n1++;
            delay(200);
          }
          if(n1 == 0)
            goto mouse;
//Light_Mode
          switch(n){
                case 1: lm = "ON";
                          HL = 1;
                          L_RE(HL);
                     break;
                case 2: lm = "Mode_1";
                        if(digitalRead(i3) == 0){
                            no1 = 9;
                            no = L_M1(no,no1);
                         }else if(digitalRead(i4) == 0){
                            no1 = 18;
                            no = L_M1(no,no1);
                         }else if(digitalRead(i5) == 0){
                            no1 = 10;
                            no = L_M1(no,no1);
                         }else if(digitalRead(i6) == 0) {
                            no1 = 21;
                            no = L_M1(no,no1);
                         }else if(digitalRead(i7) == 0){
                            no1 = 20;
                            no = L_M1(no,no1);
                         }else if(digitalRead(i8) == 0){
                            no1 = 14;
                            no = L_M1(no,no1);    
                          }
                   break;
              case 3: lm = "Mode_2";
                         HL1 = 1;
                       if(digitalRead(L3) == 1 && digitalRead(L4) == 1 && digitalRead(L5) == 1 && digitalRead(L6) == 1 && digitalRead(L7) == 1 && digitalRead(L8) == 1)
                          m2n = 1;
                       if(digitalRead(L3) == 0 && digitalRead(L4) == 0 && digitalRead(L5) == 0 && digitalRead(L6) == 0 && digitalRead(L7) == 0 && digitalRead(L8) == 0)
                          m2n = 0;
                          if(m2n == 1)
                          HL1 = 0;
                         if(digitalRead(i3) == 0){
                            digitalWrite(L3,HL1);
                         }else if(digitalRead(i4) == 0){
                            digitalWrite(L4,HL1);
                         }else if(digitalRead(i5) == 0){
                            digitalWrite(L5,HL1);
                         }else if(digitalRead(i6) == 0){
                            digitalWrite(L6,HL1);
                         }else if(digitalRead(i7) == 0){
                            digitalWrite(L7,HL1);
                         }else if(digitalRead(i8) == 0){
                            digitalWrite(L8,HL1);
                         }
                   break; 
              case 4: lm = "OFF";
                      n = 0;
                   break;
           }
//Key_Mode
        switch(n1){
              case 1:a1 = 128;
                    km = "Ctrl",s = "Cx", up = "Cc", d = "EN", lt = "BA", dn = "Ca", rt = "Cv";
                  if(digitalRead(i3) == 0){
                        a2 = 120;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i4) == 0){
                        a2 = 99;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i5) == 0){
                          Keyboard. press(176);
                          delay(200);
                          Keyboard.releaseAll();
                          delay(80);
                    }
                  if(digitalRead(i6) == 0){
                         Keyboard. press(178);
                         delay(200);
                         Keyboard.releaseAll();
                    }
                  if(digitalRead(i7) == 0){
                        a2 = 97;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i8) == 0){
                        a2 = 118;
                        K_ASC(a1,a2);
                    }
                   break;
              case 2: a1 = 131;
                   km = "Win",s = "Wr",up = "We", d = "Wv", lt = "W<", dn = "Wd", rt = "W>";
                   if(digitalRead(i3) == 0){
                       Keyboard.press(131);
                       Keyboard.press(114);
                       Keyboard.release(131);
                       Keyboard.print("cmd");
                       Keyboard.press(176);
                       delay(200);
                       Keyboard.releaseAll();
                    }
                  if(digitalRead(i4) == 0){
                       a2 = 101;
                       K_ASC(a1,a2);
                    }
                  if(digitalRead(i5) == 0){
                        a2 = 108;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i6) == 0){
                        a2 = 216;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i7) == 0){
                        a2 = 100;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i8) == 0){
                        a2 = 215;
                        K_ASC(a1,a2);
                    }
                   break;        
              case 3: a1 = 128;
              km = "PhtShp",s = "As",up = "Ct", d = "EN", lt = "Cz", dn = "Wd", rt = "CB";
                  if(digitalRead(i3) == 0){
                       Keyboard.press(130);
                       Keyboard.press(129);
                       if(digitalRead(i3) == 1)
                       Keyboard.releaseAll();
                    }
                  if(digitalRead(i4) == 0){
                       a2 = 116;
                       K_ASC(a1,a2);
                    }
                  if(digitalRead(i5) == 0){
                    Keyboard. press(176);
                    delay(200);
                    Keyboard.releaseAll();
                    delay(80);
                    }
                  if(digitalRead(i6) == 0){
                        a2 = 122;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i7) == 0){
                        a2 = 100;
                        K_ASC(a1,a2);
                    }
                  if(digitalRead(i8) == 0){
                        a2 = 178;
                        K_ASC(a1,a2);
                    }
                   break; 
              case 4:km = "SldWks",s = "ES",up = "UP", d = "C8", lt = "TL", dn = "DN", rt = "TR";
                  if(digitalRead(i3) == 0){
                    Keyboard. press(177);
                    delay(200);
                    Keyboard.releaseAll();
                    }
                  if(digitalRead(i4) == 0){
                    Keyboard. press(218);
                    delay(200);
                    Keyboard.releaseAll();
                    }
                  if(digitalRead(i5) == 0){
                    a1 = 128;
                    a2 = 56;
                    K_ASC(a1,a2);
                    }
                  if(digitalRead(i6) == 0){
                    Keyboard. press(216);
                    delay(200);
                    Keyboard.releaseAll();
                    }
                  if(digitalRead(i7) == 0){
                    Keyboard. press(217);
                    delay(200);
                    Keyboard.releaseAll();
                    }
                  if(digitalRead(i8) == 0){
                    Keyboard. press(215);
                    delay(200);
                    Keyboard.releaseAll();
                    }
                   break; 
              case 5:km = "Mouse",s = "LC", up = "UP", d = "RC", lt = "TL", dn = "DN", rt = "TR";
                      n1 = 0;
                   break;
           }
}//while
}
/********************************************Functions**************************************************/
//KEY_Mode
void K_ASC(int a1,int a2){
  Keyboard. press(a1);
  Keyboard. press(a2);
  delay(200);
  Keyboard.releaseAll();
}
//Lights_ALL_ctrl
void L_RE(int HL){
  digitalWrite(Ln,HL);
  digitalWrite(L2,HL);
  digitalWrite(L3,HL);
  digitalWrite(L4,HL);
  digitalWrite(L5,HL);
  digitalWrite(L6,HL);
  digitalWrite(L7,HL);
  digitalWrite(L8,HL);
}
//L_Mode_1
int L_M1(int no,int no1){
   digitalWrite(no,0);
   no = no1;
   digitalWrite(no,1);
   return no;
}
//Mouse
void Mouse_c(){
  int upState = digitalRead(i4);
  int downState = digitalRead(i7);
  int rightState = digitalRead(i8);
  int leftState = digitalRead(i6);
  int clickState = digitalRead(i3);
  int RState = digitalRead(i5);
  int xDistance = (leftState - rightState) * 5;
  int yDistance = (upState - downState) * 5;
  if ((xDistance != 0) || (yDistance != 0)) {
                    Mouse.move(xDistance, yDistance, 0);
                  }
                  if (clickState == 0) {
                    if (!Mouse.isPressed(MOUSE_LEFT)) {
                      Mouse.press(MOUSE_LEFT);
                    }
                  }
                  else {
                    if (Mouse.isPressed(MOUSE_LEFT)) {
                      Mouse.release(MOUSE_LEFT);
                    }
                  }
                  if (RState == 0) {
                    if (!Mouse.isPressed(MOUSE_RIGHT)) {
                      Mouse.press(MOUSE_RIGHT);
                    }
                  }
                  else {
                    if (Mouse.isPressed(MOUSE_RIGHT)) {
                      Mouse.release(MOUSE_RIGHT);
                    }
                  }
                  delay(10);
}
