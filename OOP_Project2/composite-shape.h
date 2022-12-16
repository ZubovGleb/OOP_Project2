#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "Shape.h"

class CompositeShape : public Shape
{
private:
	Shape** complex_ = new Shape*;
	int size_;
	point_t pos_;
public:
	CompositeShape();
	~CompositeShape();
	
	double getArea() override;
	rectangle_t getFrameRect() override;
	void move(double dx, double dy) override;
	void move(point_t& p) override;
	void scale(double k) override;
	std::string getName() override;
	Shape* clone() override;

	void addShape(Shape* s);
};

#endif