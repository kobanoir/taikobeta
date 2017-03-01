#include "note_katu.h"

Katu::Katu(double point,bool dai) {
	x_point = point;
	big = dai;
}

void Katu::draw_katu() {
	Circle(x_point, 300, 32).draw();
	Circle(x_point, 300, 28).draw(Color(237, 68, 46));
}