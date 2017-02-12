#pragma once

# include "common.h"
# include "song_data.h"
# include "song_select.h"
# include "Body.h"

class Title;
class Song_data;
class Body;
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

private:
	//shared_ptr<Music> music;
	State state;
	shared_ptr<Title> title;
	Body exe;
	Song_select sel;
};