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
		time_sto = 0;
		count = 0;
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
			note.music_offset = atof(hoge.c_str());
		}
		if (i == 5) {
			note.note_offset = atof(hoge.c_str());
		}
		if (i == 6) {
			note.songs_constant = atof(hoge.c_str());
		}
		if (i == 7) {
			note.songs_def = atoi(hoge.c_str());
		}
		if (i >= 8) {
			note.note.push_back(empty);
			note.note[i - 8] = hoge;
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
	if (Input::KeySpace.clicked && play != 1) {
		//�m�[�c��\�����邽�߂̉�����:�z���push_back���Ă���
		note_draw();
		play = 1;
		//�X�g�b�v�E�H�b�`��������
		stopwatch.start();
	}

	if (play == 1) {
		play_song();
		shed_note();
		judge();
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
	draw_point *= (note.note_offset * 60);
	for (int i = 0;i < note.note.size();i++) {
		for (int j = 0;j < note.note[i].size();j++) {
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
			//�m�[�c�̊Ԋu���l�𑝂₷
			draw_point += (880 / note.note[i].size());
		}
	}
	//�����蔻��̑��
	for (int i = 0; i < data_don.size(); i++) {
		//����g�Əd�Ȃ�F�������߂�
		double hit = ((data_don[i].x_point - 230) / scroll);
		//F��ms�ɕϊ�
		hit = hit * (1000.0 / 60.0);
		data_don[i].hit_ms = hit;
	}
	for (int i = 0; i < data_katu.size(); i++) {
		//����g�Əd�Ȃ�F�������߂�
		double hit = ((data_katu[i].x_point - 230) / scroll);
		//F��ms�ɕϊ�
		hit = hit * (1000.0 / 60.0);
		data_katu[i].hit_ms = hit;
	}
}

void Body::play_song() {
	string song;
	song += "Songs\\";
	song += songtitle;
	song += "\\";
	song += note.song;
	static Sound bgm(Widen(song));
	if (stopwatch.ms() >= note.music_offset * 1000) {
		bgm.setVolume(note.velume);
		bgm.play();
	}
}

void Body::shed_note() {
	static Font font(40);
	//���Ԃ��擾
	double time = stopwatch.ms();
	//�O��Ƃ̍��������߂�ŏ��̒l��0
	diff = time - time_sto;
	//���̎��s���̑O��̒l�ɂ���ׂ�����̒l��O��̒l�ɑ��
	time_sto = time;
	//���_�l(1F=0.0166666)�Ƃ̌덷�������߂�
	if (diff == 0) {
		//0�ŏ��Z������ƃG���[�f���̂�0�̂Ƃ��͎����I��0����
		//���Ԃ̕ω��������̂Œl��ς���K�v�͂Ȃ�
		error_rate = 0;
	}
	else {
		error_rate = diff / (1.0 / 60.0 * 1000.0);
	}
	//���ׂẴm�[�g�̍��W���炻�̒l������+ �`��
	//error_rate��0���ƕω��Ȃ��悤�ɂȂ��Ă܂�
	for (int i = 0; i < data_don.size(); i++) {
		data_don[i].x_point -= scroll * error_rate;
		data_don[i].draw_don();
	}
	for (int i = 0; i < data_katu.size(); i++) {
		data_katu[i].x_point -= scroll * error_rate;
		data_katu[i].draw_katu();
	}
	font(stopwatch.ms()).draw(100, 200);
	font(count).draw(100, 100);
	count++;
}

void Body::judge() {
	//�h���A�J�b�̉��̓ǂݍ���
	static Sound don(L"Sound_Effect\\dong.wav");
	static Sound katu(L"Sound_Effect\\ka.wav");
	if (Input::KeyS.clicked || Input::KeyL.clicked) {
		don.stop();
		don.play();
		judge_don();
	}
	if (Input::KeySemicolon.clicked || Input::KeyA.clicked) {
		katu.stop();
		katu.play();
		judge_katu();
	}
}

void Body::judge_don() {
	double time = stopwatch.ms();
	//�擪�̃m�[�c��T��
	int i = 0;
	for (i = 0; i < data_don.size(); i++) {
		//miss�̍Œx������x��������false��
		if (data_don[i].hit_ms + 150.0 <= time) {
			data_don[i].draw_canc = false;
		}
		//false�Ȃ痬�ꂽ��
		if (data_don[i].draw_canc == true) {
			break;
		}
	}
	if (data_don[i].hit_ms - 34 <= time && data_don[i].hit_ms + 34 >= time) {
		point += 500;
		data_don[i].draw_canc = false;
	}
	else if (data_don[i].hit_ms - 117 <= time && data_don[i].hit_ms + 117 >= time) {
		point += 250;
		data_don[i].draw_canc = false;
	}
	else if (data_don[i].hit_ms - 150 <= time && data_don[i].hit_ms + 150 >= time) {
		data_don[i].draw_canc = false;
	}
}

void Body::judge_katu() {
	//�@�����Ƃ��̎��Ԏ擾
	double time = stopwatch.ms();
	//�擪�̃m�[�c��T��
	int i = 0;
	for (i = 0; i < data_katu.size(); i++) {
		//miss�̍Œx������x��������false��
		if (data_katu[i].hit_ms + 150.0 <= time) {
			data_katu[i].draw_canc = false;
		}
		//false�Ȃ痬�ꂽ��
		if (data_katu[i].draw_canc == true) {
			break;
		}
	}
	if (data_katu[i].hit_ms - 34 <= time && data_katu[i].hit_ms + 34 >= time) {
		point += 500;
		data_katu[i].draw_canc = false;
	}
	else if (data_katu[i].hit_ms - 117 <= time && data_katu[i].hit_ms + 117 >= time) {
		point += 250;
		data_katu[i].draw_canc = false;
	}
	else if (data_katu[i].hit_ms - 150 <= time && data_katu[i].hit_ms + 150 >= time) {
		data_katu[i].draw_canc = false;
	}
}

