#pragma once

# include "common.h"

//class Music;
class Title;

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
	void draw();

private:
	//shared_ptr<Music> music;
	State state;
	shared_ptr<Title> title;
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	vector<string> file_name;
};