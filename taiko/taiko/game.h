#pragma once

# include "common.h"
# include "song_data.h"
# include "song_select.h"

class Title;
class Song_data;
class Song_select;

class Game {
public:

	//�Q�[���̏�Ԃ��Ǘ����Ԃ񃍃O�C����ʂƂ��ǉ����܂�
	enum State {
		TYTLE,
		SONGSELECT,
		GAME,
		RESULT,
	};

	//���񂷂Ƃ炭���[
	Game();
	void update();
	void draw();
	void find_files();
	void select_rayout();

private:
	//shared_ptr<Music> music;
	State state;
	shared_ptr<Title> title;
	//�t�@�C�������Ɏg��
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	int select = 0;
	vector<Song_data> songs_list;
	Song_select sel;
};