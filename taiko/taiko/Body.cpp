#include "Body.h"

void Body::exe() {
	if (flag != 1) {
		point = 0;
		combo = 0;
		scroll = 0;
		onef = 60 / (note.BPM / 60);
		flag = 1;
	}
	reyout_draw();
	main_exec();
}

void Body::find_note(string title) {
	//カウント用
	int i = 0;
	//push_back用の空のクラス
	string hoge;
	string empty;
	vector<double> fuga;
	//Enterキー押されたときに中央にあった曲のデータを読み込む
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
			note.BPM = atof(hoge.c_str());
		}
		if (i == 3) {
			note.offset = atof(hoge.c_str());
		}
		if (i == 4) {
			note.songs_constant = atof(hoge.c_str());
		}
		if (i == 5) {
			note.songs_def = atoi(hoge.c_str());
		}
		if (i >= 6) {
			note.note.push_back(empty);
			draw_save_don.push_back(fuga);
			draw_save_katu.push_back(fuga);
			note.note[i - 6] = hoge;
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
	note_draw();
	judge();
}

void Body::draw_don() {
	Circle(draw_point, 300, 32).draw();
	Circle(draw_point, 300, 28).draw(Color(237, 68, 46));
}
void Body::draw_katu() {
	Circle(draw_point, 300, 32).draw();
	Circle(draw_point, 300, 28).draw(Color(68, 141, 173));

}

void Body::note_draw() {
	double empty = 0;
	for (int i = 0;i < note.note.size();i++) {
		for (int j = 0;j < note.note[i].size();j++) {
			draw_point = (note.offset * 60) * (100 / onef) + 200 + ((200 / (note.note[i].size() / 4)) * ((j + 1) + i * note.note[i].size())) - scroll;
			draw_save_don[i].push_back(empty);
			draw_save_katu[i].push_back(empty);
			if (note.note[i][j] == '0') {/*何もしない*/}
			else if (note.note[i][j] == '1' && draw_point >=140) {
				draw_don();
				draw_save_don[i][j] == draw_point;
			}
			else if (note.note[i][j] == '2' && draw_point >= 140) {
				draw_katu();
				draw_save_katu[i][j] == draw_point;
			}
		}
	}
	scroll += 8;
}

void Body::judge() {
	if (Input::KeyS.clicked || Input::KeyK.clicked) {
		for (int i = 0;i < note.note.size();i++) {
			for (int j = 0;j < note.note[i].size();j++) {
				if (draw_save_don[i][j] - 32 <= 252 || draw_save_don[i][j] + 32 >= 198) {
					point += 500;
				}
				else if (draw_save_don[i][j] - 53 <= 283 || draw_save_don[i][j] + 53 >= 177) {
					point += 300;
				}
			}
		}
	}
	if (Input::KeyA.clicked || Input::KeyL.clicked) {
		for (int i = 0;i < note.note.size();i++) {
			for (int j = 0;j < note.note[i].size();j++) {
				if (draw_save_katu[i][j] - 32 <= 252 || draw_save_katu[i][j] + 32 >= 198) {
					point += 500;
				}
				else if (draw_save_katu[i][j] - 53 <= 283 || draw_save_katu[i][j] + 53 >= 177) {
					point += 300;
				}
			}
		}
	}
}