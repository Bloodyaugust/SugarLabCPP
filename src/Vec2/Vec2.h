#ifndef VEC2_H
#define VEC2_H

class Vec2 {
private:
	float x;
	float y;

public:
	Vec2(float x = 0, float y = 0);
	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);
};

#endif
