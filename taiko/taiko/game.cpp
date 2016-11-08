# include "game.h"
#include "Title.h"

Game::Game() {
	//�X�e�[�g���X�^�[�g��ʂɂ��ď�����
	state = State::TYTLE;
	//music = make_shared<Music>();
}

void Game::update() {

	static Font font(30);

	switch (state){
	case State::TYTLE:
		if (Input::KeySpace.clicked) {
			state = State::SONGSELECT;
		}
		font(L"�����Ƃ�").draw();
		break;
	case State::SONGSELECT:
		if (Input::KeyEnter.clicked) {
			state = State::GAME;
		}
		if (Input::KeyQ.clicked) {
			state = State::TYTLE;
		}
		font(L"���񂫂傭").draw();
		break;
	case State::GAME:
		if (Input::KeySpace.clicked) {
			state = State::RESULT;
		}
		if (Input::KeyQ.clicked) {
			state = State::SONGSELECT;
		}
		font(L"�Ղꂢ���߂�").draw();
		break;
	case State::RESULT:
		if (Input::KeySpace.clicked) {
			state = State::SONGSELECT;
		}
		font(L"�肴���").draw();
		break;
	}
}

void Game::draw() {
	static Font font(40);
	switch (state) {
	case State::TYTLE:
		font(L"���^�C�g���I��").draw(350, 150);
		Title->draw();
		break;
	case State::SONGSELECT:
		font(L"�y�ȑI��").draw(50, 50);
		break;
	case State::GAME:
		break;
	case State::RESULT:
		break;
	}
}