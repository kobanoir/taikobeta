#include "Body.h"

void Body::exe() {
	if (flag != 1) {
		point = 0;
		combo = 0;
		scroll = 0;
		//1Fの間に流れてくる4分音符の数
		onef = (note.BPM / 60) / 60;
		flag = 1;
		diff = 0;
	}
	reyout_draw();
	main_exec();
}

void Body::find_note(string title) {
	//カウント用
	int i = 0;
	songtitle = title;
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
		play = 1;
	}

	if (play == 1) {
		play_song();
		note_draw();
	}
	else {
		psk(L"prass space key").draw(300, 290);
	}
}

void Body::draw_don() {
	Circle(draw_point, 300, 32).draw();
	Circle(draw_point, 300, 28).draw(Color(237, 68, 46));
}
void Body::draw_katu() {
	Circle(draw_point, 300, 32).draw();
	Circle(draw_point, 300, 28).draw(Color(68, 141, 173));

}

void Body::draw_bigdon() {
	Circle(draw_point, 300, 53).draw();
	Circle(draw_point, 300, 48).draw(Color(237, 68, 46));
}

void Body::draw_bigkatu() {
	Circle(draw_point, 300, 53).draw();
	Circle(draw_point, 300, 48).draw(Color(68, 141, 173));
}

void Body::note_draw() {
	//オフセット代入
	draw_point = (220 * ((note.offset * 60) / (1 / onef)));
	for (int i = 0;i < note.note.size();i++) {
		for (int j = 0;j < note.note[i].size();j++) {
<<<<<<< HEAD
			//時間を取得
			double time = stopwatch.ms();
			//前回との差分を求める最初の値は0
			diff = time - diff;
			//理論値(1F=0.0166666)との誤差率を求める
			error_rate = (1 / 60) / diff;
=======
			//最初のノーツが流れてくるまでの座標 + その小節の音符の数からノーツの間隔を出す
				draw_point = (220 * ((note.offset * 60) / (1 / onef))) + ((220 / (note.note[i].size() / 4))
					* (j + i * note.note[i].size())) - scroll;
			draw_save_don[i].push_back(empty);
			draw_save_katu[i].push_back(empty);
>>>>>>> origin/master
			if (note.note[i][j] == '0') {/*何もしない*/}
			else if (note.note[i][j] == '1' && draw_point >=140 + 32) {
				draw_don();
			}
			else if (note.note[i][j] == '2' && draw_point >= 140 + 32) {
				draw_katu();
			}
			else if (note.note[i][j] == '3' && draw_point >= 140 + 53) {
				draw_bigdon();
			}
			else if (note.note[i][j] == '4' && draw_point >= 140 + 53) {
				draw_bigkatu();
			}
			draw_point += (880 / note.note[i].size()) * time / 60 + scroll;
		}
	}
	scroll += 220 / (1 / onef);
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

