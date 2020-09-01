#include <M5Stack.h>
#include "character_status.h"
#include "keyboard_wiretap.h"

void setup()
{
  // M5Stackを初期化
  // LCDとSerialのみ有効化
  M5.begin(true, true, true, false);

  // M5Stackをバッテリ―駆動する場合に必要
  M5.Power.begin();

  // バックグラウンド処理をスタートする
  // character_statusを使う場合，この関数を最初に一回だけ呼び出す必要がある
  // M5.begin()の後に書く必要がある
  character_status.start_background_process();
}

void loop()
{
  // M5Stackのボタンの状態を参照する場合は，ループの最初でupdate()を呼び出す必要がある
  M5.update();
  // character_statusを参照する場合は，ループの最初でupdate()を呼び出す必要がある
  character_status.update();
  keyboard_wiretap.task();
}
