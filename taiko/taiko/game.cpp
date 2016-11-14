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
		font(L"せんきょく").draw();
		break;
	case State::GAME:
		if (Input::KeySpace.clicked) {
			state = State::RESULT;
		}
		if (Input::KeyQ.clicked) {
			state = State::SONGSELECT;
		}
		font(L"ぷれいがめん").draw();
		break;
	case State::RESULT:
		if (Input::KeySpace.clicked) {
			state = State::SONGSELECT;
		}
		font(L"りざると").draw();
		break;
	}
}

void Game::draw() {
	static Font font(40);
	switch (state) {
	case State::TYTLE:
		font(L"仮タイトル的な").draw(350, 150);
		title->draw();
		break;
	case State::SONGSELECT:
		font(L"楽曲選択").draw(50, 50);
		break;
	case State::GAME:
		Line(0, 240, 1080, 240).draw();
		Line(0, 360, 1080, 360).draw();
		break;
	case State::RESULT:
		break;
	}
}