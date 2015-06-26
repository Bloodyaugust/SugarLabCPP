#ifndef SRC_COLLIDER_H_
#define SRC_COLLIDER_H_

#include "Rect.hpp"

class Collider {
	public:
		explicit Collider(Rect* rect);

		bool intersects(Rect* rect);

	private:
		Rect* collider_rect_;
		std::string type_;
};

#endif  // SRC_COLLIDER_H_
