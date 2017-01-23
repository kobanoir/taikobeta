#pragma once

#include "common.h"

class Song_data {
public:
	int find_files();

private:
	string file_name;
	//曲名
	string song_title;
	//背景の壁紙
	string wallpaper;
	//音楽データ
	string song;
	//オフセット
	double offset;
	//BPM(まんま)
	double BPM;
	//譜面定数(sp計算に使うかも)
	double songs_constant;
	//難易度(1～10)
	int songs_def;
	//譜面の中身
	vector<string> note;
	//ファイル走査に使う
	HANDLE hFind;
	WIN32_FIND_DATA fd;

};