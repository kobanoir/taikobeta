#include "Body.h"

void Body::exe() {
	if (flag != 1) {
		point = 0;
		combo = 0;
		scroll = 0;
		//1Fの間に流れてくる4分音符の数
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
		//ノーツを表示するための下準備:配列にpush_backしていく
		note_draw();
		play = 1;
		//ストップウォッチも動かす
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
	//この下の話は全部理論値
	//1秒あたりに流れてくるノート数
	draw_point = note.BPM / 60;
	//1つのノートがくるまでにかかる間隔
	draw_point = 60 / draw_point;
	//1Fあたりいくつ進むか
	draw_point = 220 / draw_point;
	//スクロールに保存
	scroll = draw_point;
	//offsetはsなのでfに直す
	draw_point *= (note.note_offset * 60);
	for (int i = 0;i < note.note.size();i++) {
		for (int j = 0;j < note.note[i].size();j++) {
			if (note.note[i][j] == '0') {/*何もしない*/}
			else if (note.note[i][j] == '1' && draw_point >=140 + 32) {
				//コンストラクタに座標を渡して入れておく
				//大音符かどうかも渡すbigだったらtrue
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
			//ノーツの間隔分値を増やす
			draw_point += (880 / note.note[i].size());
		}
	}
	//当たり判定の代入
	for (int i = 0; i < data_don.size(); i++) {
		//判定枠と重なるF数を求める
		double hit = ((data_don[i].x_point - 230) / scroll);
		//Fをmsに変換
		hit = hit * (1000.0 / 60.0);
		data_don[i].hit_ms = hit;
	}
	for (int i = 0; i < data_katu.size(); i++) {
		//判定枠と重なるF数を求める
		double hit = ((data_katu[i].x_point - 230) / scroll);
		//Fをmsに変換
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
	//時間を取得
	double time = stopwatch.ms();
	//前回との差分を求める最初の値は0
	diff = time - time_sto;
	//次の実行時の前回の値にするべく今回の値を前回の値に代入
	time_sto = time;
	//理論値(1F=0.0166666)との誤差率を求める
	if (diff == 0) {
		//0で除算をするとエラー吐くので0のときは自動的に0を代入
		//時間の変化が無いので値を変える必要はない
		error_rate = 0;
	}
	else {
		error_rate = diff / (1.0 / 60.0 * 1000.0);
	}
	//すべてのノートの座標からその値を引く+ 描画
	//error_rateが0だと変化ないようになってます
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
	//ドン、カッの音の読み込み
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
	//先頭のノーツを探す
	int i = 0;
	for (i = 0; i < data_don.size(); i++) {
		//missの最遅判定より遅かったらfalseに
		if (data_don[i].hit_ms + 150.0 <= time) {
			data_don[i].draw_canc = false;
		}
		//falseなら流れた後
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
	//叩いたときの時間取得
	double time = stopwatch.ms();
	//先頭のノーツを探す
	int i = 0;
	for (i = 0; i < data_katu.size(); i++) {
		//missの最遅判定より遅かったらfalseに
		if (data_katu[i].hit_ms + 150.0 <= time) {
			data_katu[i].draw_canc = false;
		}
		//falseなら流れた後
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

