#include "character_status.h"

// CharacterStatusクラスをインスタンス化
CharacterStatus character_status;

static const double EXP_WEIGHT = 1.0 / 50.0;

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
  int exp = background_process.get_exp();

  level_status = static_cast<int>(exp * EXP_WEIGHT) % 100 + 1;
  if (1 <= level_status && level_status < 20) {
    evolution_status = 0;
  }
  else if (20 <= level_status && level_status < 50) {
    evolution_status = 1;
  }
  else {
    evolution_status = 2;
  }
  generation_status = static_cast<int>(exp * EXP_WEIGHT) / 100 + 1;
}
