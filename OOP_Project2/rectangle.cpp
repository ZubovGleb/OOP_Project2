#include "rectangle.h"


Rectangle::Rectangle()
{
	p1_.x = 0;
	p2_.x = 0;
	p1_.y = 0;
	p2_.y = 0;
}

Rectangle::Rectangle(point_t p1, point_t p2)
{
	p1_ = p1;
	p2_ = p2;
}

Rectangle::~Rectangle() = default;

double Rectangle::getArea()
{
	return (p1_.x - p2_.x) * (p1_.y - p2_.y);
}

rectangle_t Rectangle::getFrameRect()
{
	rectangle_t frameRectangle{};
	point_t pos{};
	pos.x = (p1_.x + p2_.x) / 2;
	pos.y = (p1_.y + p2_.y) / 2;
	frameRectangle.pos = pos;
	frameRectangle.width = abs(p1_.x - p2_.x);
	frameRectangle.height = abs(p1_.y - p2_.y);
	return frameRectangle;
}

void Rectangle::move(point_t& point)
{
	double centerX = (p1_.x + p2_.x) / 2;
	double centerY = (p1_.y + p2_.y) / 2;
	p1_.x += point.x - centerX;
	p2_.x += point.x - centerX;
	p1_.y += point.y - centerY;
	p2_.y += point.y - centerY;
}

void Rectangle::move(double dx, double dy)
{
	p1_.x += dx;
	p2_.x += dx;
	p1_.y += dy;
	p2_.y += dy;
}

void Rectangle::scale(double k)
{
	p1_.x -= (k - 1) * (p2_.x - p1_.x) / 2;
	p2_.x += (k - 1) * (p2_.x - p1_.x) / 2;
	p1_.y -= (k - 1) * (p2_.y - p1_.y) / 2;
	p2_.y += (k - 1) * (p2_.y - p1_.y) / 2;
}

std::string Rectangle::getName()
{
	return "RECTANGLE";
}

Shape* Rectangle::clone()
{
	return new Rectangle(p1_, p2_);
}
