#pragma once

# include "common.h"

//class Music;
class Title;

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

private:
	//shared_ptr<Music> music;
	State state;
	shared_ptr<Title> title;
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	vector<string> file_name;
};