#include "character_status.h"

// CharacterStatusクラスをインスタンス化
CharacterStatus character_status;

CharacterStatus::CharacterStatus()
{
  level_status = 0;
  evolution_status = 0;
  generation_status = 0;
}

CharacterStatus::~CharacterStatus()
{
}

void CharacterStatus::begin()
{
  background_process.begin();
}

void CharacterStatus::update()
{
}
