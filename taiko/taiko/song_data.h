#pragma once

#include "common.h"

class Song_data {
public:
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

};