#pragma once

#include "common.h"

class Song_data {
public:
	int find_files();

private:
	string file_name;
	//�Ȗ�
	string song_title;
	//�w�i�̕ǎ�
	string wallpaper;
	//���y�f�[�^
	string song;
	//�I�t�Z�b�g
	double offset;
	//BPM(�܂��)
	double BPM;
	//���ʒ萔(sp�v�Z�Ɏg������)
	double songs_constant;
	//��Փx(1�`10)
	int songs_def;
	//���ʂ̒��g
	vector<string> note;
	//�t�@�C�������Ɏg��
	HANDLE hFind;
	WIN32_FIND_DATA fd;

};