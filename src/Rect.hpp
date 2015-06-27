#ifndef SRC_RECT_H_
#define SRC_RECT_H_

#include "Vec2.hpp"

class Rect {
	public:
		explicit Rect(double x = 0, double y = 0, double width = 0, double height = 0);
		explicit Rect(Vec2* position, Vec2* size);

		Rect* clone();
		double x();
		double y();
		double x2();
		double y2();
		double width();
		double height();
		bool intersects(Rect* rect);
		void translate(Vec2* vector);
		void translate(double x, double y);
		void scale(double scalar);
		void set_x(double x);
		void set_y(double y);
		void set_width(double width);
		void set_height(double height);

	private:
		double x_;
		double y_;
		double x2_;
		double y2_;
		double width_;
		double height_;
};

#endif  // SRC_RECT_H_
