#ifndef STRUCTURAPOINTER_H
#define STRUCTURAPOINTER_H
#include <iostream>
struct point
{
	float x;
	float y;
	point& operator=(const point& c)
	{
		this->x = c.x;
		this->y = c.y;
		return *this;
	}
	point& operator+=(const point& c) 
	{
		this->x += c.x;
		this->y += c.y;
		return *this;
	}
	bool operator==(const point& c)const
	{
		return x == c.x && y == c.y;
	}
	friend std::ostream& operator<<(std::ostream& os, const point&c)
	{
		os<< c.x << ' ' << c.y;
		return os;
	}
	point& operator*(int val)
	{
		x *= val;
		y *= val;
		return *this;
	}
};

struct AABB
{
	int x;
	int y;
	int width;
	int height;
	AABB(point x, int width, int height) :width(width), height(height), x(x.x), y(x.y) {};
	AABB operator=(const AABB& val)
	{
		x = val.x;
		y = val.y;
		width = val.width;
		height = val.height;
		return *this;
	}
	bool Coliziune(const AABB& obiect)
	{
		if (x < obiect.x + obiect.width)
		{
			//std::cout << "Primul check";
			if (x + width > obiect.x)
			{
				//std::cout << "Al doilea check";
				if (y < obiect.y + obiect.height)
				{
					//std::cout << "Al treilea check";
					if (y + height > obiect.y)
						return 1;
				}
			}
		}
			return 0;
	}

};
namespace std {
	template <>
	struct hash<point> {
		size_t operator()(const point& a) const {
			return std::hash<float>()(a.x) ^ std::hash<float>()(a.y);
		}
	};
}
#endif // !STRUCTURAPOINTER_H
