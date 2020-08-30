#ifndef GROWTH_STATUS_H_
#define GROWTH_STATUS_H_

class CharacterStatus {
 private:
  int level_status;      // レベルを表す
  int evolution_status;  // 進化の段階を表す．ダックは0で進化するごとに1増える
  int generation_status; // 世代を表す

 public:
  CharacterStatus();
  ~CharacterStatus();
  void begin();
  void update();
};

// CharacterStatusクラスをインスタンス化
// ヘッダーファイルをインクルードすると，このインスタンスが使える
extern CharacterStatus growth_status;

#endif // GROWTH_STATUS_H_
