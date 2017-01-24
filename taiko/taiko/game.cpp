# include "game.h"
#include "Title.h"

Game::Game() {
	//�X�e�[�g���X�^�[�g��ʂɂ��ď�����
	state = State::TYTLE;
	title = make_shared<Title>();
	//music = make_shared<Music>();
}

void Game::update() {

	static Font font(30);

	switch (state){
	case State::TYTLE:
		if (Input::KeySpace.clicked) {
			state = State::SONGSELECT;
		}
		break;
	case State::SONGSELECT:
		if (Input::KeyEnter.clicked) {
			state = State::GAME;
		}
		if (Input::KeyQ.clicked) {
			state = State::TYTLE;
		}
		break;
	case State::GAME:
		if (Input::KeySpace.clicked) {
			state = State::RESULT;
		}
		if (Input::KeyQ.clicked) {
			state = State::SONGSELECT;
		}
		break;
	case State::RESULT:
		if (Input::KeySpace.clicked) {
			state = State::SONGSELECT;
		}
		break;
	}
}

void Game::draw() {
	int flag = 0;
	static Font font(40);
	static Font start(20);
	static Circle good(200, 300, 53);
	static Circle parfect(200, 300, 32);
	switch (state) {
	case State::TYTLE:
		font(L"���^�C�g���I��").draw(350, 150);
		start(L"Press to space").draw(450, 350);
		title->draw();
		break;
	case State::SONGSELECT:
		font(L"�y�ȑI��").draw(50, 50);
		break;
	case State::GAME:
		Line(0, 240, 1080, 240).draw();
		Line(0, 360, 1080, 360).draw();
		Line(140, 240, 140, 360).draw();
		good.drawFrame(2, 0,Alpha(300));
		parfect.drawFrame(2, 0, Alpha(300));
		break;
	case State::RESULT:
		font(L"Score").draw(200, 150);
		font(L"Perfect").draw(180, 400);
		font(L"Good").draw(205, 500);
		font(L"Miss").draw(215, 600);
		break;
	}
}

void Game::find_files() {
	//�J�E���g�p
	int i = 0;
	//push_back�p�̋�̃N���X
	Song_data hoge;
	string file = "Songs\\*.*";
	hFind = FindFirstFile(file.c_str(), &fd);
	songs_list.push_back(hoge);
	if (hFind == INVALID_HANDLE_VALUE) {
	
	}
	//�Ȃ��̉B���t�@�C���H�����o����̂ł�����Ȃ��p
	if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		&& strcmp(fd.cFileName, "..") != 0 && strcmp(fd.cFileName, ".") != 0) {
		songs_list[0].file_name = fd.cFileName;
		i++;
	}
	//�Ȃ��̂��ꂾ�����Ƃ����X�g�̐�������Ȃ��Ȃ�̂Ń|�b�v
	else {
		songs_list.pop_back();
	}


	while (FindNextFile(hFind, &fd)) {
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& strcmp(fd.cFileName, "..") != 0 && strcmp(fd.cFileName, ".") != 0) {
			songs_list.push_back(hoge);
			songs_list[i].file_name = fd.cFileName;
			i++;
		}
	}
	for (i = 0; i < songs_list.size(); i++) {
		cout << songs_list[i].file_name << endl;
	}
}