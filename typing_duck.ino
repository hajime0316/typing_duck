#include <M5Stack.h>
#include "character_status.h"
#include"keyboard_wiretap.h"
#include<Ticker.h>
#include<string>

static const int LOOP_TIME_MAX =100;

Ticker ticker;

//画像の表示位置(画像サイズ:280*210)
uint16_t jpg_x = 20;
uint16_t jpg_y = 0;

//進化コース
//↓evolution_status
//0 →ダック
//1 →11:ダチョウ，12:カモシカ，13:ヴェロキラプトル
//2 →21:ダチョウ（進化ver）22:カモシカ（進化ver）23:ヴェロキラプトル（進化ver）
int character_num = 0;

std::string character_name = "Duck";


void present_status() {//ステータスを画面下部に表示する
  M5.Lcd.setCursor(0, 220); //表示位置

  //名前
  if(character_num == 0) {
    M5.Lcd.print("Name:Duck");
  } else if(character_num == 11) {
    M5.Lcd.print("Name:Husen");
  } else if(character_num == 12) {
    M5.Lcd.print("Name:Nukege");
  } else if(character_num == 13) {
    M5.Lcd.print("Name:Zabeth");
  } else if(character_num == 21) {
    M5.Lcd.print("Name:Maeba");
  } else if(character_num == 22) {
    M5.Lcd.print("Name:Ushika");
  } else if(character_num == 23) {
    M5.Lcd.print("Name:Blue");
  }
  M5.Lcd.print(" ");
  
  M5.Lcd.print("Lv."); //レベル
  M5.Lcd.print(character_status.get_level_status());
  M5.Lcd.print(" ");
  M5.Lcd.print("Gen.");//世代
  M5.Lcd.print(character_status.get_generation_status());
}

void draw_character() 
{
  static bool flag_for_toggle_picture = true;
  
  if(character_status.get_typing_status() == TypingStatus::WAITING){
    if (flag_for_toggle_picture) {
      M5.Lcd.drawJpgFile(SD,("/" + character_name + "/" + character_name + "_1.jpg").c_str(), jpg_x, jpg_y);
    }
    else {
      M5.Lcd.drawJpgFile(SD,("/" + character_name + "/" + character_name + "_2.jpg").c_str(), jpg_x, jpg_y);
    }
  } else if(character_status.get_typing_status() == TypingStatus::TYPING){
    if (flag_for_toggle_picture) {
      M5.Lcd.drawJpgFile(SD,("/" + character_name + "/" + character_name + "_1.jpg").c_str(), jpg_x, jpg_y);
    }
    else {
      M5.Lcd.drawJpgFile(SD,("/" + character_name + "/" + character_name + "_kira.jpg").c_str(), jpg_x, jpg_y);
    }
  } else if(character_status.get_typing_status() == TypingStatus::PROMPTING_REST){
    M5.Lcd.drawJpgFile(SD,("/" + character_name + "/" + character_name + "_rest.jpg").c_str(), jpg_x, jpg_y);//休め
  } else if(character_status.get_typing_status() == TypingStatus::REJECTING_INPUT){
    M5.Lcd.drawJpgFile(SD,("/" + character_name + "/" + character_name + "_oko.jpg").c_str(), jpg_x, jpg_y);//入力拒否
  }

  flag_for_toggle_picture = !flag_for_toggle_picture;
}

void setup()
{
  // M5Stackを初期化
  // LCDとSerialのみ有効化
  M5.begin(true, true, true, false);

  // M5Stackをバッテリ―駆動する場合に必要
  M5.Power.begin();

  //text setting 
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);

  // バックグラウンド処理をスタートする
  // character_statusを使う場合，この関数を最初に一回だけ呼び出す必要がある
  // M5.begin()の後に書く必要がある
  character_status.start_background_process();
  //ticker.attach_ms(1000, draw_character); //draw_character関数を１秒毎に呼び出す
}

void loop()
{
  // M5Stackのボタンの状態を参照する場合は，ループの最初でupdate()を呼び出す必要がある
  M5.update();
  // character_statusを参照する場合は，ループの最初でupdate()を呼び出す必要がある
  character_status.update();
  keyboard_wiretap.task();
  
  if(character_status.was_changed_to_first_evolution() == true) {//第１進化の時のコース選択
    character_num = random(11, 14);
    if (character_num == 11) {
      character_name = "Husen";
    }
    else if (character_num == 12) {
      character_name = "Nukege";
    }
    else if (character_num == 13) {
      character_name = "Zabeth";
    }
  } else if(character_status.was_changed_to_second_evolution() == true) {//第２進化の時のcharacter_num変数の更新
    if(character_num == 11){
      character_num = 21;
    } else if(character_num == 12) {
      character_num = 22;
    } else if(character_num == 13) {
      character_num = 23;
    }
  } else if(character_status.was_changed_to_origin_evolution() == true) {//世代交代の時のcharacter_num変数の更新
    character_num = 0;
  }

  static int loop_time = 0;
  loop_time++;
  
  if(loop_time > LOOP_TIME_MAX) {
    draw_character();
    loop_time = 0;
  }

  //キャラクターのステータス表示
  present_status();
}
