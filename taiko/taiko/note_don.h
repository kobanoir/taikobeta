#pragma once
#include "common.h"

class Don {
public:
	Don(double point,bool dai);
	//�`�悷�邽�߂�x���̍��W�f�[�^�����炤
	void draw_don();

	double x_point;
	//���̃m�[�c�̓����蔻�肪���鎞�Ԃ̒��S
	double hit_ms;
	//�m�[�g�����������Ƃ��̏��łɎg��true�Ȃ�`�悷��false�Ȃ炵�Ȃ�
	bool draw_canc;
	//�剹�����ǂ���
	bool big;
};
