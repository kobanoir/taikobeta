#include "note_katu.h"

Katu::Katu(double point,bool dai) {
	x_point = point;
	big = dai;
	draw_canc = true;
}

void Katu::draw_katu() {
	if (draw_canc == true) {
		if (big == false) {
			Circle(x_point, 300, 32).draw();
			Circle(x_point, 300, 28).draw(Color(68, 141, 173));
		}
		else if (big == true) {
			Circle(x_point, 300, 53).draw();
			Circle(x_point, 300, 48).draw(Color(68, 141, 173));
		}
	}
	else {
		//‰½‚à‚µ‚È‚¢(‰½‚à•`‰æ‚µ‚È‚¢)
	}
}