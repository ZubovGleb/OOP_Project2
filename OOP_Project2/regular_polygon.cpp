#include "regular_polygon.h"
#include <cmath>

RegularPolygon::RegularPolygon()
{
	p1_.x = 0;
	p2_.x = 0;
	p3_.x = 0;
	p1_.y = 0;
	p2_.y = 0;
	p3_.y = 0;
}

RegularPolygon::RegularPolygon(point_t p1, point_t p2, point_t p3)
{
	p1_ = p1;
	p2_ = p2;
	p3_ = p3;
}

RegularPolygon::~RegularPolygon() = default;

double RegularPolygon::getArea()
{
	double k = 0;
	double area = 0;
	double catheter = sqrt(fmin((p2_.x - p1_.x) * (p2_.x - p1_.x) + (p2_.y - p1_.y) * (p2_.y - p1_.y), (p3_.x - p1_.x) * (p3_.x - p1_.x) + (p3_.y - p1_.y) * (p3_.y - p1_.y)));
	double anotherCatheter= sqrt((p2_.x - p3_.x) * (p2_.x - p3_.x) + (p2_.y - p3_.y) * (p2_.y - p3_.y));
	k = this->countCornersDouble();
	area = catheter * anotherCatheter * k;
	return area;
}

rectangle_t RegularPolygon::getFrameRect()
{
	int k = this->countCornersInt();
	rectangle_t frameRectangle{};
	frameRectangle.pos.x = p1_.x;
	frameRectangle.pos.y = p1_.y;
	double hypotenuse = sqrt(fmax((p2_.x - p1_.x) * (p2_.x - p1_.x) + (p2_.y - p1_.y) * (p2_.y - p1_.y), (p3_.x - p1_.x) * (p3_.x - p1_.x) + (p3_.y - p1_.y) * (p3_.y - p1_.y)));
	double catheter = sqrt(fmin((p2_.x - p1_.x) * (p2_.x - p1_.x) + (p2_.y - p1_.y) * (p2_.y - p1_.y), (p3_.x - p1_.x) * (p3_.x - p1_.x) + (p3_.y - p1_.y) * (p3_.y - p1_.y)));
	double length = 2 * sqrt((p2_.x - p3_.x) * (p2_.x - p3_.x) + (p2_.y - p3_.y) * (p2_.y - p3_.y));
	if (k % 4 == 0)
	{
		frameRectangle.height = 2 * catheter;
		frameRectangle.width = 2 * catheter;
	}
	else if (k % 2 == 0)
	{
		frameRectangle.height = 2 * catheter;
		frameRectangle.width = 2 * hypotenuse;
	}
	else
	{
		frameRectangle.height = catheter + hypotenuse;
		double angle = ((k / 2) / (double)k) * 2 * acos(-1);
		frameRectangle.width = hypotenuse * sqrt(2 - 2 * cos(angle));
	}

	return frameRectangle;
}

void RegularPolygon::move(point_t& point)
{
	p2_.x += point.x - p1_.x;
	p3_.x += point.x - p1_.x;
	p2_.y += point.y - p1_.y;
	p3_.y += point.y - p1_.y;
	p1_.x = point.x;
	p1_.y = point.y;
}

void RegularPolygon::move(double dx, double dy)
{
	p1_.x += dx;
	p2_.x += dx;
	p3_.x += dx;
	p1_.y += dy;
	p2_.y += dy;
	p3_.y += dy;
}

void RegularPolygon::scale(double k)
{
	double dx = p1_.x;
	double dy = p1_.y;
	p2_.x = (p2_.x - dx) * k + dx;
	p3_.x = (p3_.x - dx) * k + dx;
	p2_.y = (p2_.y - dy) * k + dy;
	p3_.y = (p3_.y - dy) * k + dy;
}

std::string RegularPolygon::getName()
{
	return "REGULAR";
}

Shape* RegularPolygon::clone()
{
	return new RegularPolygon(p1_, p2_, p3_);
}

int RegularPolygon::countCornersInt()
{
	double resultDouble = 0.0; // количество углов в double
	double roundedResultDouble = 0.0; // математическое округление количества углов
	int result = 0;
	double hypotenuse = sqrt(fmax((p2_.x - p1_.x) * (p2_.x - p1_.x) + (p2_.y - p1_.y) * (p2_.y - p1_.y), (p3_.x - p1_.x) * (p3_.x - p1_.x) + (p3_.y - p1_.y) * (p3_.y - p1_.y)));
	double catheter = sqrt(fmin((p2_.x - p1_.x) * (p2_.x - p1_.x) + (p2_.y - p1_.y) * (p2_.y - p1_.y), (p3_.x - p1_.x) * (p3_.x - p1_.x) + (p3_.y - p1_.y) * (p3_.y - p1_.y)));
	resultDouble = acos(-1) / acos(catheter / hypotenuse);
	roundedResultDouble = floor(resultDouble + 0.5);
	result = (int)roundedResultDouble;
	return result;
}

double RegularPolygon::countCornersDouble()
{
	double resultDouble = 0.0;
	double hypotenuse = sqrt(fmax((p2_.x - p1_.x) * (p2_.x - p1_.x) + (p2_.y - p1_.y) * (p2_.y - p1_.y), (p3_.x - p1_.x) * (p3_.x - p1_.x) + (p3_.y - p1_.y) * (p3_.y - p1_.y)));
	double catheter = sqrt(fmin((p2_.x - p1_.x) * (p2_.x - p1_.x) + (p2_.y - p1_.y) * (p2_.y - p1_.y), (p3_.x - p1_.x) * (p3_.x - p1_.x) + (p3_.y - p1_.y) * (p3_.y - p1_.y)));
	resultDouble = acos(-1) / acos(catheter / hypotenuse);
	return resultDouble;
}

