#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H

#include "shape.h"

class RegularPolygon : public Shape
{
private:
	point_t p1_;
	point_t p2_;
	point_t p3_;
public:
	RegularPolygon();
	RegularPolygon(point_t p1, point_t p2, point_t p3);
	~RegularPolygon();

	double getArea() override;
	rectangle_t getFrameRect() override;
	void move(point_t& point) override;
	void move(double dx, double dy) override;
	void scale(double k) override;
	std::string getName() override;
	Shape* clone() override;

	int countCornersInt();
	double countCornersDouble();
};

#endif