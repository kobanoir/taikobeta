#include "Body.h"

void Body::exe() {
	if (flag != 1) {
		point = 0;
		combo = 0;
		scroll = 0;
		//1F�̊Ԃɗ���Ă���4�������̐�
		onef = 60 / (note.BPM / 60);
		flag = 1;
		diff = 0;
	}
	reyout_draw();
	main_exec();
}

void Body::find_note(string title) {
	//�J�E���g�p
	int i = 0;
	songtitle = title;
	//push_back�p�̋�̃N���X
	string hoge;
	string empty;
	vector<double> fuga;
	//Enter�L�[�����ꂽ�Ƃ��ɒ����ɂ������Ȃ̃f�[�^��ǂݍ���
	string file = "Songs\\";
	file +=title;
	file += "\\";
	file += title;
	file += ".txt";

	ifstream ifs(file);
	while (getline(ifs, hoge)) {
		if (i == 0) {
			note.wallpaper = hoge;
		}
		if (i == 1) {
			note.song = hoge;
		}
		if (i == 2) {
			note.velume = atof(hoge.c_str());
		}
		if (i == 3) {
			note.BPM = atof(hoge.c_str());
		}
		if (i == 4) {
			note.offset = atof(hoge.c_str());
		}
		if (i == 5) {
			note.songs_constant = atof(hoge.c_str());
		}
		if (i == 6) {
			note.songs_def = atoi(hoge.c_str());
		}
		if (i >= 7) {
			note.note.push_back(empty);
			note.note[i - 7] = hoge;
		}
		i++;
	}
	i = 0;
}

void Body::reyout_draw() {
	static Font score(40);
	static Font com(25);
	score(L"SCORE").draw(500,20);
	score(point).draw(800, 20);
	com(combo).draw(50, 275);
}

void Body::main_exec() {
	static Font psk(10);
	if (Input::KeySpace.clicked) {
		//�m�[�c��\�����邽�߂̉�����:�z���push_back���Ă���
		note_draw();
		play = 1;
	}

	if (play == 1) {
		play_song();
	}
	else {
		psk(L"prass space key").draw(300, 290);
	}
}

void Body::note_draw() {
	//���̉��̘b�͑S�����_�l
	//1�b������ɗ���Ă���m�[�g��
	draw_point = note.BPM / 60;
	//1�̃m�[�g������܂łɂ�����Ԋu
	draw_point = 60 / draw_point;
	//1F�����肢���i�ނ�
	draw_point = 220 / draw_point;
	//�X�N���[���ɕۑ�
	scroll = draw_point;
	//offset��s�Ȃ̂�f�ɒ���
	draw_point *= (note.offset * 60);
	for (int i = 0;i < note.note.size();i++) {
		for (int j = 0;j < note.note[i].size();j++) {
			/*//���Ԃ��擾
			double time = stopwatch.ms();
			//�O��Ƃ̍��������߂�ŏ��̒l��0
			diff = time - diff;
			//���_�l(1F=0.0166666)�Ƃ̌덷�������߂�
			error_rate = (1 / 60) / diff;*/
			if (note.note[i][j] == '0') {/*�������Ȃ�*/}
			else if (note.note[i][j] == '1' && draw_point >=140 + 32) {
				//�R���X�g���N�^�ɍ��W��n���ē���Ă���
				//�剹�����ǂ������n��big��������true
				data_don.push_back(Don(draw_point,false));
			}
			else if (note.note[i][j] == '2' && draw_point >= 140 + 32) {
				data_katu.push_back(Katu(draw_point, false));
			}
			else if (note.note[i][j] == '3' && draw_point >= 140 + 53) {
				data_don.push_back(Don(draw_point, true));
			}
			else if (note.note[i][j] == '4' && draw_point >= 140 + 53) {
				data_katu.push_back(Katu(draw_point, true));
			}
			//�l�𑝂₷�̂͌�ł��
			draw_point += (880 / note.note[i].size());
		}
	}
}

void Body::play_song() {
	string song;
	song += "Songs\\";
	song += songtitle;
	song += "\\";
	song += note.song;
	static Sound bgm(Widen(song));
	if (stopwatch.ms() >= note.offset * 1000) {
		bgm.setVolume(note.velume);
		bgm.play();
	}
}

