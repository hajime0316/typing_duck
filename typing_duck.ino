#include <M5Stack.h>
#include "background_process.h"
#include "character_status.h"

void setup()
{
  // M5Stackを初期化
  // LCDとSerialのみ有効化
  M5.begin(true, false, true, false);

  // M5Stackをバッテリ―駆動する場合に必要
  M5.Power.begin();

  // バックグラウンド処理を初期化
  // M5.begin()の後に書く
  background_process.begin();
}

void loop()
{
  // update button state
  M5.update();

  // NOTE: BackgroundProcessにおいて，M5Stackのボタンが押されたときに，
  // キーボードのキーが押されたのと同じ動作をするようにするための命令．
  // 実験のために入れている．後で必ず削除する．
  if (M5.BtnA.wasPressed()) {
    background_process.keyboard_press_callback();
  }
}
