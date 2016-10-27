# include "game.h"

Game::Game() {
	//ステートをスタート画面にして初期化
	state = State::START;
	music = make_shared<Music>();
}

void Game::update() {
	switch (state){
	default:
		break;
	}
}