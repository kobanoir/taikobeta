#pragma once

#include "common.h"

class Song_data {
public:
	//�w�i�̕ǎ�
	string wallpaper;
	//���y�f�[�^
	string song;
	//����
	double velume;
	//�m�[�c�̃I�t�Z�b�g
	double note_offset;
	//�Ȃ̃I�t�Z�b�g
	double music_offset;
	//BPM(�܂��)
	double BPM;
	//���ʒ萔(sp�v�Z�Ɏg������)
	double songs_constant;
	//��Փx(1�`10)
	int songs_def;
	//���ʂ̒��g
	vector<string> note;

};