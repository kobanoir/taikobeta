#pragma once

#include "common.h"
#include "song_data.h"

class Song_data;

class Body {
public:
	void find_note(string title);

	void reyout_draw();

	void exe();

	void main_exec();

	void draw_don();

	void draw_katu();

	void note_draw();

	void play_song();

private:
	Song_data note;
	string songtitle;
	int point;
	int combo;
	double draw_point;
	double onef;
	int flag;
	double scroll;
	Stopwatch stopwatch;
	vector<vector<double>> draw_save_don;
	vector<vector<double>> draw_save_katu;
};
