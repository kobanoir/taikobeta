# include "game.h"
#include "Title.h"

Game::Game() {
	//ステートをスタート画面にして初期化
	state = State::TYTLE;
	title = make_shared<Title>();
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
			exe.find_note(sel.get_title());
		}
		if (Input::KeyQ.clicked) {
			state = State::TYTLE;
		}
		break;
	case State::GAME:
		exe.exe();
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
	static Circle good(230, 300, 53);
	static Circle parfect(230, 300, 32);
	switch (state) {
	case State::TYTLE:
		font(L"仮タイトル的な").draw(350, 150);
		start(L"Press to space").draw(450, 350);
		title->draw();
		break;
	case State::SONGSELECT:
		sel.exe();
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