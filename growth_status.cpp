#include "growth_status.h"

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
