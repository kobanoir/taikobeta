#pragma once

# include "common.h"
# include "song_data.h"

class Song_data;

class Song_select {
public:
	Song_select();
	void exe();
	void find_files();
	void select_rayout();
	string get_title();
private:
	//ファイル走査に使う
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	int select = 0;
	vector<string> songs_list;
	int flag = 0;
};
