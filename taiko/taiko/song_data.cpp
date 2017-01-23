#include "Song_data.h"


int Song_data::find_files() {
	string file = "Songs\\*.*";
	hFind = FindFirstFile(file.c_str(), &fd);
	file_name = fd.cFileName;
	if (hFind == INVALID_HANDLE_VALUE) {
		return -1;
	}

	if (file_name.size() != 0) {
		return 1;
	}

	return 3;
}