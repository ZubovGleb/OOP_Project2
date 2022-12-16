#include "shape.h"

#include <iomanip>

std::ostream& operator<< (std::ostream& out, Shape& shape)
{
	double lbx = 0, lby = 0, rtx = 0, rty = 0;
	lbx = shape.getFrameRect().pos.x - shape.getFrameRect().width / 2;
	lby = shape.getFrameRect().pos.y - shape.getFrameRect().height / 2;
	rtx = shape.getFrameRect().pos.x + shape.getFrameRect().width / 2;
	rty = shape.getFrameRect().pos.y + shape.getFrameRect().height / 2;
	return (out << std::fixed << std::setprecision(1) << shape.getName() << " Area: " << shape.getArea() << " Frame rectangle: lb: (" << lbx << "; " << lby << ") rt: (" << rtx << "; " << rty << ")");
}

bool Shape::operator< (Shape& shape)
{
    return this->getArea() < shape.getArea();
}
