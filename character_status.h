#ifndef GROWTH_STATUS_H_
#define GROWTH_STATUS_H_

#include "background_process.h"

class CharacterStatus {
 private:
  int level_status;           // レベルを表す
  int evolution_status;       // 進化の段階を表す．ダックは0で進化するごとに1増える
  int generation_status;      // 世代を表す
  TypingStatus typing_status; // 待機中やタイピング中などの状態を保持する

  int last_evolution_status;
  TypingStatus last_typing_status;

 public:
  CharacterStatus();
  ~CharacterStatus();
  void start_background_process();
  void update();
  // getter
  int get_level_status() const { return level_status; };
  int get_evolution_status() const { return evolution_status; };
  int get_generation_status() const { return generation_status; };
  TypingStatus get_typing_status() const { return typing_status; };
  // ステータスの変化を通知する関数
  bool was_changed_to_first_evolution();
  bool was_changed_to_second_evolution();
  bool was_changed_to_third_evolution();
  bool was_changed_to_waiting();
  bool was_changed_to_typing();
  bool was_changed_to_prompting_rest();
  bool was_changed_to_rejecting_input();
};

// CharacterStatusクラスをインスタンス化
// ヘッダーファイルをインクルードすると，このインスタンスが使える
extern CharacterStatus character_status;

#endif // GROWTH_STATUS_H_
