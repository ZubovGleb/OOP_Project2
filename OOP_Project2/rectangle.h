#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
private:
	point_t p1_;
	point_t p2_;
public:
	Rectangle();
	Rectangle(point_t p1, point_t p2);
	~Rectangle();

	double getArea() override;
	rectangle_t getFrameRect() override;
	void move(point_t& point) override;
	void move(double dx, double dy) override;
	void scale(double k) override;
	std::string getName() override;
	Shape* clone() override;
};

#endif