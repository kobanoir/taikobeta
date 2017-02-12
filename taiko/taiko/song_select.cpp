# include "song_select.h"

Song_select::Song_select() {
	find_files();
}

void Song_select::exe() {
	select_rayout();
}

void Song_select::select_rayout() {
	static Font font(40);
	static Rect rect(400, 300, 1000, 100);
	static Rect rect1(500, 180, 1000, 100);
	static Rect rect2(500, 420, 1000, 100);
	static Rect rect3(600, 60, 1000, 100);
	static Rect rect4(600, 540, 1000, 100);
	static Rect rect5(700, -50, 1000, 100);
	static Rect rect6(700, 660, 1000, 100);
	rect.drawFrame(3, 0);
	rect1.drawFrame(3, 0);
	rect2.drawFrame(3, 0);
	rect3.drawFrame(3, 0);
	rect4.drawFrame(3, 0);
	rect5.drawFrame(3, 0);
	rect6.drawFrame(3, 0);
	if (Input::KeyUp.clicked) {
		if (select == 0) {
			select = songs_list.size() - 1;
		}
		else {
			select--;
		}
	}
	if (Input::KeyDown.clicked) {
		if (select == songs_list.size() - 1) {
			select = 0;
		}
		else {
			select++;
		}
	}
	//中央描画
 	font(Widen(songs_list[select])).draw(420, 300);
	font(select).draw(100, 100);
	//一段下
 	if (select + 1 == songs_list.size()) {
		font(Widen(songs_list[0])).draw(520, 420);
	}
	else {
		font(Widen(songs_list[select + 1])).draw(520, 420);
	}
	//もう一段下
	if (select + 2 >= songs_list.size()) {
		font(Widen(songs_list[select + 2 - songs_list.size()])).draw(620, 540);
	}
	else {
		font(Widen(songs_list[select + 2])).draw(620, 540);
	}
	//一つ上
	if (select == 0) {
		font(Widen(songs_list[songs_list.size() - 1])).draw(520, 180);
	}
	else {
		font(Widen(songs_list[select - 1])).draw(520, 180);
	}
	//もいっこ上
	if (select <= 1) {
		font(Widen(songs_list[songs_list.size() - 2 + select])).draw(620, 60);
	}
	else {
		font(Widen(songs_list[select - 2])).draw(620, 60);
	}
}

void Song_select::find_files() {
	//カウント用
	int i = 0;
	//push_back用の空のクラス
	string hoge;
	string file = "Songs\\*.*";
	hFind = FindFirstFile(file.c_str(), &fd);
	songs_list.push_back(hoge);
	if (hFind == INVALID_HANDLE_VALUE) {

	}
	//なぞの隠しファイル？を検出するのでそれを省く用
	if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		&& strcmp(fd.cFileName, "..") != 0 && strcmp(fd.cFileName, ".") != 0) {
		songs_list[0] = fd.cFileName;
		i++;
	}
	//なぞのあれだったときリストの数が合わなくなるのでポップ
	else {
		songs_list.pop_back();
	}


	while (FindNextFile(hFind, &fd)) {
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& strcmp(fd.cFileName, "..") != 0 && strcmp(fd.cFileName, ".") != 0) {
			songs_list.push_back(hoge);
			songs_list[i] = fd.cFileName;
			i++;
		}
	}
}

string Song_select::get_title() {
	return songs_list[select];
}