#include "Body.h"

bool Body::exe() {
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
		game_end = false;
		perfect = 0;
		good = 0;
		miss = 0;
		achievement = 0;
		view_achievement = 0;
		music_reading = 1;
		demo_flag = 0;
	}
	reyout_draw();
	main_exec();
	if (game_end == true) {
		return true;
	}
	else {
		return false;
	}
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
		if (i == 3) {
			note.velume = atof(hoge.c_str());
		}
		if (i == 4) {
			note.BPM = atof(hoge.c_str());
		}
		if (i == 5) {
			note.music_offset = atof(hoge.c_str());
		}
		if (i == 6) {
			note.note_offset = atof(hoge.c_str());
		}
		if (i == 7) {
			note.songs_constant = atof(hoge.c_str());
		}
		if (i == 8) {
			note.songs_def = atoi(hoge.c_str());
		}
		if (i >= 9) {
			note.note.push_back(empty);
			note.note[i - 9] = hoge;
		}
		i++;
	}
	i = 0;
}

void Body::reyout_draw() {
	static Font score(40);
	static Font achi(30);
	static Font com(25);
	score(L"SCORE").draw(500,20);
	achi(L"Achievement").draw(450, 120);
	achi(view_achievement).draw(850, 120);
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
	static Font font(40);
	static Sound bgm;
	static int song_length;
	if (music_reading == 1) {
		string song;
		song += "Songs\\";
		song += songtitle;
		song += "\\";
		song += note.song;
		music_reading = 0;
		bgm = Sound(Widen(song));
		song_length = bgm.lengthSec() + note.music_offset + 1;
	}
	if (stopwatch.ms() >= note.music_offset * 1000) {
		bgm.setVolume(note.velume);
		bgm.play();
	}
	if (song_length == stopwatch.s()) {
		bgm.stop();
		stopwatch.reset();
		game_end = true;
	}
	font(perfect).draw(100, 500);
	font(good).draw(100,600);
	font(miss).draw(100, 700);
	font(song_length).draw(300, 150);
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
	double time = stopwatch.ms();
	for (int i = 0; i < data_don.size(); i++) {
		//missの最遅判定より遅かったらfalseに
		if (data_don[i].hit_ms + 150.0 <= time && data_don[i].draw_canc == true) {
			combo = 0;
			miss++;
			data_don[i].draw_canc = false;
		}
	}

	for (int i = 0; i < data_katu.size(); i++) {
		//missの最遅判定より遅かったらfalseに
		if (data_katu[i].hit_ms + 150.0 <= time && data_katu[i].draw_canc == true) {
			combo = 0;
			miss++;
			data_katu[i].draw_canc = false;
		}
	}
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
	//アチーブメントの計算
	achievement = (perfect + good * 0.5) / (perfect + good + miss) * 100;
	view_achievement = achievement;
}

void Body::judge_don() {
	double time = stopwatch.ms();
	//先頭のノーツを探す
	int i = 0;
	for (i = 0; i < data_don.size(); i++) {
		//falseなら流れた後
		if (data_don[i].draw_canc == true) {
			break;
		}
	}
	if (i != data_don.size()) {
		if (data_don[i].hit_ms - 34 <= time && data_don[i].hit_ms + 34 >= time) {
			point += 500 + 500 / 10 * (combo / 10);
			combo++;
			data_don[i].draw_canc = false;
			perfect++;
		}
		else if (data_don[i].hit_ms - 117 <= time && data_don[i].hit_ms + 117 >= time) {
			point += 250 + 250 / 10 * (combo / 10);
			combo++;
			data_don[i].draw_canc = false;
			good++;
		}
		else if (data_don[i].hit_ms - 150 <= time && data_don[i].hit_ms + 150 >= time) {
			combo = 0;
			data_don[i].draw_canc = false;
			miss++;
		}
	}
}

void Body::judge_katu() {
	//叩いたときの時間取得
	double time = stopwatch.ms();
	//先頭のノーツを探す
	int i = 0;
	for (i = 0; i < data_katu.size(); i++) {
		//falseなら流れた後
		if (data_katu[i].draw_canc == true) {
			break;
		}
	}
	if (i != data_katu.size()) {
		if (data_katu[i].hit_ms - 34 <= time && data_katu[i].hit_ms + 34 >= time) {
			point += 500 + 500 / 10 * (combo / 10);
			combo++;
			data_katu[i].draw_canc = false;
			perfect++;
		}
		else if (data_katu[i].hit_ms - 117 <= time && data_katu[i].hit_ms + 117 >= time) {
			point += 250 + 250 / 10 * (combo / 10);
			combo++;
			data_katu[i].draw_canc = false;
			good++;
		}
		else if (data_katu[i].hit_ms - 150 <= time && data_katu[i].hit_ms + 150 >= time) {
			combo = 0;
			data_katu[i].draw_canc = false;
			miss++;
		}
	}
}

void Body::result() {
	static Font font(40);
	font(point).draw(600, 150);
	font(perfect).draw(500,400);
	font(good).draw(500,500);
	font(miss).draw(500,600);
	font(view_achievement).draw(600, 275);
}

void Body::release() {
	//使った動的配列群を開放する
	data_don.clear();
	data_katu.clear();
	note.note.clear();
	flag = 0;
	play = 0;
	music_reading = 1;
}

void Body::play_demo(string title) {
	//画像、音楽、難易度を読み込む
	//音楽のデモ再生の時間もひつようですね
	ostringstream img;
	ostringstream music;
	static Texture back_img;
	static Sound demo_music;
	if (demo_flag == 0) {
		int i = 0;
		string fuga;
		string file = "Songs\\";
		file += title;
		file += "\\";
		file += title;
		file += ".txt";
		ifstream ifs(file);
		for (int i = 0; i <= 8; i++) {
			getline(ifs, fuga);
			if (i == 0) {
				demo.wallpaper = fuga;
			}
			if (i == 1) {
				demo.song = fuga;
			}
			if (i == 2) {
				demo.demo_play = atof(fuga.c_str());
			}
			if (i == 8) {
				demo.songs_def = atoi(fuga.c_str());
			}
		}
		img << "Songs\\" << title << "\\" << demo.wallpaper;
		music << "Songs\\" << title << "\\" << demo.song;
		back_img = Texture(Widen(img.str()));
		demo_music = Sound(Widen(music.str()));
		demo_music.setPosSec(demo.demo_play);
		demo_music.play();
		demo_flag = 1;
	}
	back_img.resize(1080, 720).draw();
	if (demo_music.lengthSec() == demo_music.streamPosSec()) {
		demo_music.setPosSec(demo.demo_play);
	}
	if (Input::KeyUp.clicked) {
		demo_flag = 0;
		demo_music.stop();
	}
	if (Input::KeyDown.clicked) {
		demo_flag = 0;
		demo_music.stop();
	}
	if (Input::KeyEnter.clicked) {
		demo_music.stop();
	}
}