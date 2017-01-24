#pragma once

# include "common.h"
# include "song_data.h"

class Title;
class Song_data;

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
	void find_files();

private:
	//shared_ptr<Music> music;
	State state;
	shared_ptr<Title> title;
	//ファイル走査に使う
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	
	vector<Song_data> songs_list;
};