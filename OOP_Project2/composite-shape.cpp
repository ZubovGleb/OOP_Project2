#include "composite-shape.h"
#include <algorithm>

CompositeShape::CompositeShape()
{
	pos_.x = 0.0;
	pos_.y = 0.0;
	size_ = 0;
}

CompositeShape::~CompositeShape() = default;

double CompositeShape::getArea()
{
	double area = 0;
	for (int i = 0; i < size_; i++) {
		area += complex_[i][0].getArea();
	}
	return area;
}

rectangle_t CompositeShape::getFrameRect()
{
	double lbx = 1e6, lby = 1e6, rtx = -1e6, rty = -1e6;
	rectangle_t partFrame{};
	double plbx = 0, plby = 0, prtx = 0, prty = 0;
	rectangle_t mainFrame{};
	for (int i = 0; i < size_; i++) {
		partFrame = complex_[i][0].getFrameRect();
		plbx = partFrame.pos.x - partFrame.width / 2;
		plby = partFrame.pos.y - partFrame.height / 2;
		prtx = partFrame.pos.x + partFrame.width / 2;
		prty = partFrame.pos.y + partFrame.height / 2;

		plbx < lbx ? lbx = plbx : lbx;
		plby < lby ? lby = plby : lbx;
		prtx > rtx ? rtx = prtx : rtx;
		prty > rty ? rty = prty : rty;
	}
	mainFrame.width = rtx - lbx;
	mainFrame.height = rty - lby;
	mainFrame.pos.x = lbx + mainFrame.width / 2;
	mainFrame.pos.y = lby + mainFrame.height / 2;
	return mainFrame;
}

void CompositeShape::move(double dx, double dy)
{
	for (int i = 0; i < size_; i++) {
		complex_[i][0].move(dx, dy);
	}
}

void CompositeShape::move(point_t& p)
{
	double dx = p.x - pos_.x;
	double dy = p.y - pos_.y;
	point_t destinationPoint{};

	for (int i = 0; i < size_; i++) {
		destinationPoint.x = complex_[i][0].getFrameRect().pos.x + dx;
		destinationPoint.y = complex_[i][0].getFrameRect().pos.y + dy;
		complex_[i][0].move(destinationPoint);
	}
	pos_.x = p.x;
	pos_.y = p.y;
}

void CompositeShape::scale(double k)
{
	point_t dp{};

	for (int i = 0; i < size_; i++) {
		dp.x = pos_.x + (complex_[i][0].getFrameRect().pos.x - pos_.x) * k;
		dp.y = pos_.y + (complex_[i][0].getFrameRect().pos.y - pos_.y) * k;
		complex_[i][0].move(dp);
		complex_[i][0].scale(k);
	}
}

std::string CompositeShape::getName()
{
	return "COMPLEX";
}

Shape* CompositeShape::clone()
{
	Shape* s;
	CompositeShape cloneCompositeShape;

	for (int i = 0; i < size_; i++) {
		cloneCompositeShape.addShape(complex_[i]);
	}
	cloneCompositeShape.pos_ = this->pos_;
	s = &cloneCompositeShape;
	return s;
}

void CompositeShape::addShape(Shape* s)
{
	size_++;
	Shape* sClone;
	sClone = s->clone();
	complex_[size_ - 1] = sClone;
	pos_.x = this->getFrameRect().pos.x;
	pos_.y = this->getFrameRect().pos.y;
}
