#include <iostream>
#include <fstream>
#include "base-types.h"
#include "Shape.h"
#include "Rectangle.h"
#include "regular_polygon.h"
#include "composite-shape.h"

Rectangle* readRectangle(std::ifstream& in);
RegularPolygon* readRegularPolygon(std::ifstream& in);
void geSortShapes(Shape** array, int count);
void moveXY(Shape* shape, double dx, double dy);
void moveAll(Shape** array, int count, std::ifstream& in);
void scale(Shape* shape, double posX, double posY, double k);
void scaleAll(Shape** array, int count, std::ifstream& in);

int main()
{
	std::cout << "Enter the path to the input file: ";
	std::string nameInputFile;
	std::cin >> nameInputFile;
	std::ifstream input;

	try {
		input.open(nameInputFile);
		if (!input) {
			throw std::runtime_error("no such file or directory");
		}
	}
	catch (std::exception const& e) {
		std::cerr << "ERROR: " << e.what() << "\n";
		return 1;
	}

	int sizeComplex = 0;
	int count = 0;
	std::string name;
	CompositeShape complex;
	std::string type;
	Shape** shapesArray = new Shape * [30];

	while (!input.eof()) {
		input >> type;
		if (type == "COMPLEX") {
			input >> sizeComplex;
			for (int i = 0; i < sizeComplex; i++) {
				input >> name;
				if (name == "RECTANGLE") {
					Shape* s = readRectangle(input);
					if (s != NULL)
					{
						complex.addShape(s);
					}
				}
				else if (name == "REGULAR") {
					Shape* s = readRegularPolygon(input);
					if (s != NULL) {
						complex.addShape(s);
					}
				}
				else {
					input.ignore(1000000, '\n');
				}
			}
			shapesArray[count] = &complex;
			count++;
		}
		else if (type == "RECTANGLE") {
				Shape* s = readRectangle(input);
				if (s != NULL)
				{
					shapesArray[count] = s->clone();
					count++;
				}
		}
		else if (type == "REGULAR") {
				Shape* s = readRegularPolygon(input);
				if (s != NULL)
				{
					shapesArray[count] = s->clone();
					count++;
				}		
		}
		else if (type == "MOVE") {
			moveAll(shapesArray, count, input);
		}
		else if (type == "SCALE") {
			scaleAll(shapesArray, count, input);
		}
		else {
			input.ignore(1000000, '\n');
		}
	}

	geSortShapes(shapesArray, count);
	std::cout << "Shapes after sorting: \n";
	for (int i = 0; i < count; i++) {
		std::cout << *(shapesArray[i]) << '\n';
	}

	input.close();
	delete[] shapesArray;
	return 0;
}

Rectangle* readRectangle(std::ifstream& in) {
	point_t p1;
	point_t p2;
	in >> p1.x >> p1.y >> p2.x >> p2.y;
	if (p1.x == p2.x || p1.y == p2.y) {
		std::cerr << "Error: incorrect shape description (RECTANGLE is not accepted) \n";
		return NULL;
	}
	Rectangle r(p1, p2);
	return &r;
}

RegularPolygon* readRegularPolygon(std::ifstream& in) {
	point_t p1, p2, p3;
	in >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
	double hypotenuse = sqrt(fmax((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y), (p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y)));
	double catheter = sqrt(fmin((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y), (p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y)));
	double anotherCatheter = sqrt((p2.x - p3.x) * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y));
	RegularPolygon rp(p1, p2, p3);
	if (abs(hypotenuse * hypotenuse - catheter * catheter - anotherCatheter * anotherCatheter) > 10 * DBL_EPSILON || rp.countCornersInt() < 3 || abs(rp.countCornersDouble() - rp.countCornersInt()) > 1e12 * DBL_EPSILON) {
		std::cerr << "Error: incorrect shape description (REGULAR is not accepted) \n";
		return NULL;
	}
	return &rp;
}

void geSortShapes(Shape** array, int count) {
	bool f = 1;
	Shape* shape;
	while (f) {
		f = 0;
		for (int i = 0; i < count - 1; i++) {
			if (*(array[i + 1]) < *(array[i])) {
				shape = &(*array[i + 1]);
				array[i + 1] = &(*array[i]);
				array[i] = &(*shape);
				f = 1;
			}
		}
	}
}

void moveXY(Shape* shape, double dx, double dy) {
	point_t tp{};
	tp.x = shape->getFrameRect().pos.x + dx;
	tp.y = shape->getFrameRect().pos.y + dy;
	shape->move(tp);
}

void moveAll(Shape** array, int count, std::ifstream& in) {
	double dx = 0, dy = 0;
	in >> dx >> dy;
	for (int i = 0; i < count; i++) {
		moveXY(array[i], dx, dy);
	}
}

void scale(Shape* shape, double posX, double posY, double k) {
	point_t a1{};
	a1.x = shape->getFrameRect().pos.x + shape->getFrameRect().width / 2;
	a1.y = shape->getFrameRect().pos.y + shape->getFrameRect().height / 2;
	point_t scaleCenter{};
	scaleCenter.x = posX;
	scaleCenter.y = posY;
	shape->move(scaleCenter);
	point_t a2{};
	a2.x = shape->getFrameRect().pos.x + shape->getFrameRect().width / 2;
	a2.y = shape->getFrameRect().pos.y + shape->getFrameRect().height / 2;
	double dx = a1.x - a2.x;
	double dy = a1.y - a2.y;
	shape->scale(k);
	dx *= k;
	dy *= k;
	point_t dp{};
	dp.x = posX + dx;
	dp.y = posY + dy;
	shape->move(dp);
}

void scaleAll(Shape** array, int count, std::ifstream& in) {
	double posX, posY, k;
	in >> posX >> posY >> k;
	for (int i = 0; i < count; i++) {
		scale(array[i], posX, posY, k);
	}
}
