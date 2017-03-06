#include "note_don.h"

Don::Don(double point,bool dai) {
	x_point = point;
	big = dai;
	draw_canc = true;
}

void Don::draw_don() {
	if (draw_canc == true) {
		if (big == false) {
			Circle(x_point, 300, 32).draw();
			Circle(x_point, 300, 28).draw(Color(237, 68, 46));
		}
		else if (big == true) {
			Circle(x_point, 300, 53).draw();
			Circle(x_point, 300, 48).draw(Color(237, 68, 46));
		}
	}
	else {
		//‰½‚à‚µ‚È‚¢
	}
}