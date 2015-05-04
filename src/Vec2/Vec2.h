#ifndef SRC_VEC2_VEC2_H_
#define SRC_VEC2_VEC2_H_

class Vec2 {
	public:
		explicit Vec2(double x = 0, double y = 0);

		double x() const;
		double y() const;
		void set_x(double x);
		void set_y(double y);

	private:
		double x_;
		double y_;
};

#endif  // SRC_VEC2_VEC2_H_
