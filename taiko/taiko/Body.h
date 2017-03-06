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

	void shed_note();

	void judge();

	void judge_don();

	void judge_katu();
private:
	/*---------‘åŽ–----------*/
	Song_data note;
	vector<Don> data_don;
	vector<Katu> data_katu;
	/*----------‚»‚Ì‘¼--------*/
	string songtitle;
	double diff;
	int point;
	int combo;
	double error_rate;
	double draw_point;
	double onef;
	int flag;
	int play;
	double scroll;
	double time_sto;
	Stopwatch stopwatch;
	int count;
};
