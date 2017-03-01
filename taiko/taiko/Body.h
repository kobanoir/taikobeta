#pragma once

#include "common.h"
#include "song_data.h"
#include "note_don.h"
#include "note_katu.h"

class Song_data;
class Don;
class Katu;

class Body {
public:
	void find_note(string title);

	void reyout_draw();

	void exe();

	void main_exec();

	void note_draw();

	void play_song();
private:
	/*---------‘åŽ–----------*/
	Song_data note;
	vector<Don> data_don;
	vector<Katu> data_katu;
	/*----------‚»‚Ì‘¼--------*/
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
