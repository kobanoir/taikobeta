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

	void draw_bigkatu();

	void draw_bigdon();
private:
	Song_data note;
	string songtitle;
	int diff;
	int point;
	int combo;
	double error_rate;
	double draw_point;
	double onef;
	int flag;
	int play;
	double scroll;
	Stopwatch stopwatch;
};
