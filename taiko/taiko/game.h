#pragma once

# include "common.h"
# include "song_data.h"

class Title;
class Song_data;

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

private:
	//shared_ptr<Music> music;
	State state;
	shared_ptr<Title> title;
	//�t�@�C�������Ɏg��
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	
	vector<Song_data> songs_list;
};