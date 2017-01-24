# include "game.h"
#include "Title.h"

Game::Game() {
	//ステートをスタート画面にして初期化
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
		font(L"仮タイトル的な").draw(350, 150);
		start(L"Press to space").draw(450, 350);
		title->draw();
		break;
	case State::SONGSELECT:
		font(L"楽曲選択").draw(50, 50);
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
	//カウント用
	int i = 0;
	//push_back用の空のクラス
	Song_data hoge;
	string file = "Songs\\*.*";
	hFind = FindFirstFile(file.c_str(), &fd);
	songs_list.push_back(hoge);
	if (hFind == INVALID_HANDLE_VALUE) {
	
	}
	//なぞの隠しファイル？を検出するのでそれを省く用
	if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		&& strcmp(fd.cFileName, "..") != 0 && strcmp(fd.cFileName, ".") != 0) {
		songs_list[0].file_name = fd.cFileName;
		i++;
	}
	//なぞのあれだったときリストの数が合わなくなるのでポップ
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