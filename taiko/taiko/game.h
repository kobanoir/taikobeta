#pragma once

# include "common.h"

//class Music;

class Game {
public:

	//ゲームの状態を管理たぶんログイン画面とか追加します
	enum State {
		TYTLE,
		SONGSELECT,
		GAME,
		RESULT,
	};

	//こんすとらくたー
	Game();
	void update();
	//void draw();

private:
	//shared_ptr<Music> music;
	State state;
};