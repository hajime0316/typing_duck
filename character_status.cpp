#include "character_status.h"
#include "background_process.h"

// GrowthStatusクラスをインスタンス化
GrowthStatus growth_status;

GrowthStatus::GrowthStatus()
{
  level_status = 0;
  evolution_status = 0;
  generation_status = 0;
}

GrowthStatus::~GrowthStatus()
{
}

void GrowthStatus::begin()
{
}
