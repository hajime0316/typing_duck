#include "character_status.h"

// CharacterStatusクラスをインスタンス化
CharacterStatus character_status;

static const double EXP_WEIGHT = 1.0 / 5.0;

CharacterStatus::CharacterStatus()
{
  level_status = 0;
  evolution_status = 0;
  generation_status = 0;
  typing_status = TypingStatus::WAITING;

  last_evolution_status = 0;
  last_typing_status = TypingStatus::WAITING;
}

CharacterStatus::~CharacterStatus()
{
}

void CharacterStatus::start_background_process()
{
  background_process.begin();
}

void CharacterStatus::update()
{
  // 1つ前のステータスの更新
  last_evolution_status = evolution_status;
  last_typing_status = typing_status;

  // 経験値に関するステータスの更新
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

  // タイピングステータスの更新
  typing_status = background_process.get_typing_status();
}

bool CharacterStatus::was_changed_to_first_evolution()
{
  if (last_evolution_status == 0 && evolution_status == 1) {
    last_evolution_status = evolution_status;
    return true;
  }
  return false;
}

bool CharacterStatus::was_changed_to_second_evolution()
{
  if (last_evolution_status == 1 && evolution_status == 2) {
    last_evolution_status = evolution_status;
    return true;
  }
  return false;
}

bool CharacterStatus::was_changed_to_origin_evolution()
{
  if (last_evolution_status == 2 && evolution_status == 0) {
    last_evolution_status = evolution_status;
    return true;
  }
  return false;
}

bool CharacterStatus::was_changed_to_waiting()
{
  if (last_typing_status != typing_status &&
      typing_status == TypingStatus::WAITING) {
    last_typing_status = typing_status;
    return true;
  }
  return false;
}

bool CharacterStatus::was_changed_to_typing()
{
  if (last_typing_status != typing_status &&
      typing_status == TypingStatus::TYPING) {
    last_typing_status = typing_status;
    return true;
  }
  return false;
}

bool CharacterStatus::was_changed_to_prompting_rest()
{
  if (last_typing_status != typing_status &&
      typing_status == TypingStatus::PROMPTING_REST) {
    last_typing_status = typing_status;
    return true;
  }
  return false;
}

bool CharacterStatus::was_changed_to_rejecting_input()
{
  if (last_typing_status != typing_status &&
      typing_status == TypingStatus::REJECTING_INPUT) {
    last_typing_status = typing_status;
    return true;
  }
  return false;
}
