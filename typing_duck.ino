#include <M5Stack.h>
#include "character_status.h"

void setup()
{
  // M5Stackを初期化
  // LCDとSerialのみ有効化
  M5.begin(true, false, true, false);

  // M5Stackをバッテリ―駆動する場合に必要
  M5.Power.begin();

  // キャラクターステータスを初期化
  // バックグラウンド処理がスタートする
  // M5.begin()の後に書く
  character_status.begin();
}

void loop()
{
  // M5Stackのボタンの状態を参照する場合は，ループの最初でupdate()を呼び出す必要がある
  M5.update();
  // character_statusを参照する場合は，ループの最初でupdate()を呼び出す必要がある
  character_status.update();

  // NOTE: BackgroundProcessにおいて，M5Stackのボタンが押されたときに，
  // キーボードのキーが押されたのと同じ動作をするようにするための命令．
  // 実験のために入れている．後で必ず削除する．
  if (M5.BtnA.wasPressed()) {
    background_process.keyboard_press_callback();
  }
}
