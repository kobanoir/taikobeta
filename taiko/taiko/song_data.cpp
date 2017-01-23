#include "Song_data.h"


int Song_data::find_files() {
	string file = "\\taikobeta\\taiko\\taiko\\Songs\\*.*";
	hFind = FindFirstFile(file.c_str(), &fd);
	if (hFind == INVALID_HANDLE_VALUE) {
		return 114514;
	}
	else {
		return 1919;
	}
}