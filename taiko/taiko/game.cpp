# include "game.h"

Game::Game() {
	//�X�e�[�g���X�^�[�g��ʂɂ��ď�����
	state = State::START;
	music = make_shared<Music>();
}

void Game::update() {
	switch (state){
	default:
		break;
	}
}