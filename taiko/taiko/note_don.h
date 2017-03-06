#pragma once
#include "common.h"

class Don {
public:
	Don(double point,bool dai);
	//描画するためのx軸の座標データをもらう
	void draw_don();

	double x_point;
	//このノーツの当たり判定がある時間の中心
	double hit_ms;
	//ノートをたたいたときの消滅に使うtrueなら描画するfalseならしない
	bool draw_canc;
	//大音符かどうか
	bool big;
};
