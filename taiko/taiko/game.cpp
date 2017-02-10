# include "game.h"
#include "Title.h"

Game::Game() {
	//�X�e�[�g���X�^�[�g��ʂɂ��ď�����
	state = State::TYTLE;
	title = make_shared<Title>();
}

void Game::select_rayout() {
	static Font font(40);
	static Rect rect(400, 300, 1000, 100);
	static Rect rect1(500, 180, 1000, 100);
	static Rect rect2(500, 420, 1000, 100);
	static Rect rect3(600, 60, 1000, 100);
	static Rect rect4(600, 540, 1000, 100);
	static Rect rect5(700, -50, 1000, 100);
	static Rect rect6(700, 660, 1000, 100);
	rect.drawFrame(3, 0);
	rect1.drawFrame(3, 0);
	rect2.drawFrame(3, 0);
	rect3.drawFrame(3, 0);
	rect4.drawFrame(3, 0);
	rect5.drawFrame(3, 0);
	rect6.drawFrame(3, 0);
	if (Input::KeyUp.clicked) {
		select++;
	}
	if (Input::KeyDown.clicked) {
		if (select == 0) {
			select = songs_list.size() - 1;
		}
		else{
			select--;
		}
	}
	if (select >= songs_list.size()) {
		select = 0;
	}
	//�����`��
	font(Widen(songs_list[select].file_name)).draw(420, 300);
	font(select).draw(100, 100);
	//��i��
	if (select + 1 == songs_list.size()) {
		font(Widen(songs_list[0].file_name)).draw(520, 420);
	}
	else {
		font(Widen(songs_list[select + 1].file_name)).draw(520, 420);
	}
	//������i��
	if (select + 2 >= songs_list.size()) {
		font(Widen(songs_list[select - 1].file_name)).draw(620, 540);
	}
	else {
		font(Widen(songs_list[select + 2].file_name)).draw(620, 540);
	}
	//��ԉ�
	if (select + 3 >= songs_list.size()) {
		font(Widen(songs_list[select - 2].file_name)).draw(720, 660);
	}
	else {
		font(Widen(songs_list[select + 2].file_name)).draw(720, 660);
	}
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
		sel.exe();
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