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

void bz(int x, int y, int tx , int tx1, int tx2,
        String CH = "", String KM = "", String LM = "",
        String S = "", String UP = "", String D = "",
        String LT = "", String DN = "", String RT = "") {
  //屏幕区域初始化
  display.clearDisplay();
  display.drawLine(1, 1, 126, 1, WHITE); //line_1
  display.drawLine(1, 16, 126, 16, WHITE); //line_2
  display.drawLine(1, 31, 126, 31, WHITE); //line_3
  display.drawLine(68, 1, 68, 31, WHITE); //row_1
  display.drawLine(88, 1, 88, 31, WHITE); //row_2
  display.drawLine(108, 1, 108, 31, WHITE); //row_3
  display.setTextSize(1);
  display.setTextColor(WHITE);
  //灯光及键盘模式显示
  display.setCursor(7, 5);
  display.println("KEY:" + KM);
  display.setCursor(7, 21);
  display.println("LIT:" + LM);
  display.setCursor(tx, 5);
  display.println(S);
  display.setCursor(tx1, 5);
  display.println(UP);
  display.setCursor(tx2, 5);
  display.println(D);
  display.setCursor(tx, 21);
  display.println(LT);
  display.setCursor(tx1, 21);
  display.println(DN);
  display.setCursor(tx2, 21);
  display.println(RT);
  //选择框
  display.setCursor(x, y);
  display.print(CH);
  display.display();
  delay(100);
}
//body
void setup() {
  //Keys
  pinMode(Fn, INPUT_PULLUP);
  pinMode(i2, INPUT_PULLUP);
  pinMode(i3, INPUT_PULLUP);
  pinMode(i4, INPUT_PULLUP);
  pinMode(i5, INPUT_PULLUP);
  pinMode(i6, INPUT_PULLUP);
  pinMode(i7, INPUT_PULLUP);
  pinMode(i8, INPUT_PULLUP);
  
  delay(500);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  int x = 0, y = 5, //选择框位置 
      tx = 73, tx1 = 93, tx2 = 112, //键值位置
      i = 0, //Fn计数 
      n = 0, n1 = 0; //灯光,键盘模式值 
  String lm = "OFF", km = "Num", 
         s = "2", up = "1", d = "0", 
         lt = "3", dn = "4", rt = "5", 
         ch = "";//屏幕初始功能键位显示
  
  while (true)
  {
     bz(x, y, tx, tx1, tx2, ch, km, lm, s, up, d, lt, dn, rt);
//设置状态      
      if (digitalRead(Fn) == 0){ //进入菜单
          i++;
          delay(100);
      } 
      if (i%2 != 0)//处于菜单
      {
          ch = "<         >";
          
               if (digitalRead(i4) == 0) { //光标上移
                      
                          y = 5;
               }
               if (digitalRead(i7) == 0) { //光标下移
                      
                          y = 21;
               }      
                      if(y == 21)//灯光模式
                      {
                            if (digitalRead(i8) == 0){ //二级菜单加
                              n++;
                              delay(100);
                            }
                            if (digitalRead(i6) == 0){ //二级菜单减
                              n--;
                              if(n<0)
                              n=3;
                              delay(100);
                            }
            
                      }else if(y == 5){//键盘模式
                        
                            if (digitalRead(i8) == 0){
                              n1++;
                              delay(100);
                            }
                            if (digitalRead(i6) == 0){
                              n1--;
                              if(n1<0)
                              n1=4;
                              delay(100);
                            }
                            
                      }
        } else { //退出菜单
          ch = "";
          y = 5;
        }
//使用状态        
        if(i%2 != 0){ //屏幕显示
    
                switch(n){//Light_Mode
                    case 0: lm = "OFF";
                         break;
                    case 1: lm = "ON";
                         break;
                    case 2: lm = "Mode1";
                         break;
                    case 3: lm = "Mode2";     
                         break; 
                    case 4: lm = "OFF";
                            n = 0;
                         break;
                 }
           
                switch(n1){//Key_Mode
                      case 0:km = "Num", s = "2", up = "1", d = "0", lt = "3", dn = "4", rt = "5";
                           break;
                      case 1:km = "Ctrl",s = "Cx", up = "Cc", d = "EN", lt = "BA", dn = "Ca", rt = "Cv";
                           break;
                      case 2:km = "Win",s = "Wr",up = "We", d = "Wv", lt = "W<", dn = "Wd", rt = "W>";
                           break;        
                      case 3:km = "PtSp",s = "As",up = "Ct", d = "EN", lt = "<", dn = "Wd", rt = ">";
                           break; 
                      case 4:km = "SdWk",s = "E",up = "A", d = "C8", lt = "<", dn = "V", rt = ">";
                           break;
                      case 5:km = "Num", s = "2", up = "1", d = "0", lt = "3", dn = "4", rt = "5";
                             n1 = 0;
                           break;
                  }
                   
        } else { //按键功能实现

                  switch(n){ //Light_Mode
                                case 0: 
                                     break;
                                case 1: 
                                     break;
                                case 2: 
                                     break;
                                case 3: 
                                     break; 
                                case 4: 
                                        n = 0;
                                     break;
                            }
                   switch(n1){ //Key_Mode
                                case 0:
                                     break;
                                case 1:
                                     break;
                                case 2:
                                     break;        
                                case 3:
                                     break; 
                                case 4:
                                     break;
                                case 5:
                                       n1 = 0;
                                     break;
                              }
          
        }

           
    }//while
}//loop
