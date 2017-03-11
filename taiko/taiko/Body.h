#pragma once

#include "common.h"
#include "song_data.h"
#include "note_don.h"
#include "note_katu.h"

class Song_data;
class Don;
class Katu;

struct demo {
	string wallpaper;
	string song;
	int songs_def;
	double demo_play;
};

class Body {
public:
	void find_note(string title);

	void reyout_draw();

	bool exe();

	void main_exec();

	void note_draw();

	void play_song();

	void shed_note();

	void judge();

	void judge_don();

	void judge_katu();

	void result();

	void release();

	void play_demo(string title);

	int get_level() { return demo.songs_def; }
private:
	/*---------‘åŽ–----------*/
	Song_data note;
	vector<Don> data_don;
	vector<Katu> data_katu;
	demo demo;
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
	bool game_end;
	bool music_reading;

	double perfect;
	double good;
	double miss;
	double achievement;
	int view_achievement;
	int demo_flag;
};
