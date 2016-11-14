#include "Title.h"

void Title::draw(){
	static Font spfont(10);
	static Font sp(12);
	static Font name(13);
	spfont(L"skill point ranking").draw(850, 400);
	spfont(L"sp").draw(1010, 400);
	spfont(L"1").draw(820, 450);
	spfont(L"2").draw(820, 500);
	spfont(L"3").draw(820, 550);
	spfont(L"4").draw(820, 600);
	spfont(L"5").draw(820, 650);
	name(L"n1doking").draw(850,445);
	sp(L"9700").draw(1000, 445);

}