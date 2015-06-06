#ifndef SRC_VEC2_VEC2_H_
#define SRC_VEC2_VEC2_H_

class Vec2 {
	public:
		explicit Vec2(double x = 0, double y = 0);

		Vec2* clone();
		Vec2* direction(Vec2* vector);
		double distance(Vec2* vector);
		double magnitude();
		double angle_between(Vec2* vector);
		double x() const;
		double y() const;
		void randomize(int max_x, int max_y);
		void translate(Vec2* vector);
		void normalize();
		void scale(double scalar);
		void translate_along_angle(double translate_by, double angle);
		void rotate(Vec2* origin, double angle);
		void set_x(double x);
		void set_y(double y);

	private:
		double x_;
		double y_;
};

#endif  // SRC_VEC2_VEC2_H_
