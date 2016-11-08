#include "Title.h"

void Title::draw(){
	static Font spfont(10);
	spfont(L"skill point ranking").draw(900, 400);
}