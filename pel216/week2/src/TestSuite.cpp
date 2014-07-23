#include <assert.h>
#include <limits>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/TestSuite.h>

#include <inc/ex/IllegalParameterException.h>

#include <inc/elementary/Point.h>
#include <inc/elementary/Line.h>
#include <inc/elementary/LineSegment.h>

#include <inc/2d/Circle.h>
#include <inc/2d/Polygon.h>
#include <inc/2d/Triangle.h>
#include <inc/2d/Quadrilateral.h>
#include <inc/2d/Pentagon.h>
#include <inc/2d/Hexagon.h>
#include <inc/2d/Septagon.h>
#include <inc/2d/Octagon.h>
#include <inc/2d/Nonagon.h>
#include <inc/2d/Decagon.h>

#include <inc/3d/Cylinder.h>
#include <inc/3d/Cone.h>
#include <inc/3d/Sphere.h>
#include <inc/3d/Pyramid.h>

#include <inc/3d/Tetraedron.h>
#include <inc/3d/Cube.h>
#include <inc/3d/Octaedron.h>
#include <inc/3d/Dodecaedron.h>
#include <inc/3d/Icosaedron.h>

using namespace pel216::commons;

PRIVATE void pel216::week2::TestSuite::testPointClass() {

	Logger::log("Testando classe pel216::week2::Point...\n");


	Logger::log("Testando pel216::week2::Point::get|set[X|Y|Z]() ...\n");
	pel216::week2::Point *point = new Point();
	Logger::log("> %s\n", point->toString().c_str());
	assert((point->getX() == 0) && (point->getY() == 0) && (point->getZ() == 0));
	point->setX(1);
	assert((point->getX() == 1) && (point->getY() == 0) && (point->getZ() == 0));
	point->setY(1);
	assert((point->getX() == 1) && (point->getY() == 1) && (point->getZ() == 0));
	point->setZ(1);
	assert((point->getX() == 1) && (point->getY() == 1) && (point->getZ() == 1));
	Logger::log("> %s\n", point->toString().c_str());
	delete point;

	Logger::log("Testando pel216::week2::Point(x,y) ...\n");
	point = new Point(-10, -20);
	assert(point->getX() == -10 && point->getY() == -20 && point->getZ() == 0);
	Logger::log("> %s\n", point->toString().c_str());
	delete point;

	Logger::log("Testando pel216::week2::Point(x,y,z) ...\n");
	point = new Point(-1, -2, -1);
	assert(point->getX() == -1 && point->getY() == -2 && point->getZ() == -1);
	Logger::log("> %s\n", point->toString().c_str());
	delete point;

}

PRIVATE void pel216::week2::TestSuite::testLineClass() {

	Logger::log("Testando classe pel216::week2::Line...\n");

	Point *p1_9 = new Point(1, 9);
	Point *p3_15 = new Point(3, 15);
	Point *p5_20 = new Point(5, 20);
	Point *p1_10 = new Point(1, 10);

	Logger::log("Testando pel216::week2::Line::Line(float,float) ...\n");
	pel216::week2::Line *line1 = new Line(5, 4);
	Logger::log("> %s\n", line1->toString().c_str());
	assert((line1->getGradient() == 5.0f) && (line1->getYIntersect() == 4.0f));
	Logger::log("Testando pel216::week2::Line::belongs() ...\n");
	assert(line1->belongs(p1_9));
	delete line1;

	Logger::log("Testando pel216::week2::Line::Line(Point,Point) ...\n");
	pel216::week2::Line *line2 = new Line(p3_15, p5_20);
	Logger::log("> %s\n", line2->toString().c_str());
	assert((line2->getGradient() == 2.5f) && (line2->getYIntersect() == 7.5f));
	Logger::log("Testando pel216::week2::Line::belongs() ...\n");
	assert(line2->belongs(p1_10));
	delete line2;

	Logger::log("Testando pel216::week2::Line::Point(NULL, Point) ...\n");
	bool hasException1 = false;
	try {
		pel216::week2::Line *line3 = new Line(NULL, p5_20);
		assert(pel216::commons::Utils::isInvalidHandle(line3));
	} catch (pel216::commons::IllegalParameterException *ex) {
		assert(pel216::commons::Utils::isValidHandle(ex));
		hasException1 = true;
	}
	assert(hasException1);


	Logger::log("Testando pel216::week2::Line::belongs(NULL) ...\n");
	pel216::week2::Line *line4 = new Line(5, 4);
	bool hasException2 = false;
	try {
		assert(line4->belongs(NULL));
	} catch (pel216::commons::IllegalParameterException *ex) {
		assert(pel216::commons::Utils::isValidHandle(ex));
		hasException2 = true;
	}
	assert(hasException2);
	delete line4;

}

PRIVATE void pel216::week2::TestSuite::testLineSegmentClass() {

	Logger::log("Testando classe pel216::week2::LineSegment...\n");

	Point begin = Point(-10, -20);
	Point end = Point(30, 10);
	pel216::week2::LineSegment *line = new LineSegment(&begin, &end);

	Logger::log("Testando pel216::week2::LineSegment::get[Begin|End]() ...\n");
	Point *lineBegin = line->getBegin();
	Point *lineEnd = line->getEnd();
	Logger::log("> %s\n", line->toString().c_str());
	assert((lineBegin->getX() == -10) && (lineBegin->getY() == -20) && (lineBegin->getZ() == 0));
	assert((lineEnd->getX() == 30) && (lineEnd->getY() == 10) && (lineEnd->getZ() == 0));
	delete line;

}

PRIVATE void pel216::week2::TestSuite::testCircleClass() {

	Logger::log("Testando classe pel216::week2::Circle...\n");

	pel216::week2::Circle *circle= new Circle(1);
	Logger::log("> %s\n", circle->toString().c_str());
	Logger::log("Testando pel216::week2::Circle::getArea() ...\n");
	assert(circle->getArea() == ((pel216::week2::pi * pow(1, 2)) / 4));
	Logger::log("Testando pel216::week2::Circle::getPerimeter() ...\n");
	assert(circle->getPerimeter() == pel216::week2::pi);
	delete circle;

}

PRIVATE void pel216::week2::TestSuite::testPolygons() {

	Logger::log("Testando poligonos...\n");

	double sideLen = 2;

	Logger::log("Testando classe pel216::week2::Triangle...\n");
	pel216::week2::Polygon *triangle= new Triangle(sideLen);
	Logger::log("> %s\n", triangle->toString().c_str());
	delete triangle;

	Logger::log("Testando classe pel216::week2::Quadrilateral...\n");
	pel216::week2::Polygon *square= new Quadrilateral(sideLen);
	Logger::log("> %s\n", square->toString().c_str());
	delete square;

	Logger::log("Testando classe pel216::week2::Pentagon...\n");
	pel216::week2::Polygon *pentagon= new Pentagon(sideLen);
	Logger::log("> %s\n", pentagon->toString().c_str());
	delete pentagon;

	Logger::log("Testando classe pel216::week2::Hexagon...\n");
	pel216::week2::Polygon *hexagon= new Hexagon(sideLen);
	Logger::log("> %s\n", hexagon->toString().c_str());
	delete hexagon;

	Logger::log("Testando classe pel216::week2::Septagon...\n");
	pel216::week2::Polygon *septagon= new Septagon(sideLen);
	Logger::log("> %s\n", septagon->toString().c_str());
	delete septagon;

	Logger::log("Testando classe pel216::week2::Octagon...\n");
	pel216::week2::Polygon *octagon= new Octagon(sideLen);
	Logger::log("> %s\n", octagon->toString().c_str());
	delete octagon;

	Logger::log("Testando classe pel216::week2::Nonagon...\n");
	pel216::week2::Polygon *nonagon= new Nonagon(sideLen);
	Logger::log("> %s\n", nonagon->toString().c_str());
	delete nonagon;

	Logger::log("Testando classe pel216::week2::Decagon...\n");
	pel216::week2::Polygon *decagon= new Decagon(sideLen);
	Logger::log("> %s\n", decagon->toString().c_str());
	delete decagon;

}


PRIVATE void pel216::week2::TestSuite::testPolyhedrals() {

	Logger::log("Testando poliedros...\n");

	float sideLen = 2.0f;

	Logger::log("Testando classe pel216::week2::Tetraedron...\n");
	pel216::week2::Polyhedral *tetraedron = new Tetraedron(sideLen);
	Logger::log("> %s\n", tetraedron->toString().c_str());
	delete tetraedron;

	Logger::log("Testando classe pel216::week2::Cube...\n");
	pel216::week2::Polyhedral *cube= new Cube(sideLen);
	Logger::log("> %s\n", cube->toString().c_str());
	delete cube;

	Logger::log("Testando classe pel216::week2::Octaedron...\n");
	pel216::week2::Polyhedral *octaedron= new Octaedron(sideLen);
	Logger::log("> %s\n", octaedron->toString().c_str());
	delete octaedron;

	Logger::log("Testando classe pel216::week2::Dodecaedron...\n");
	pel216::week2::Polyhedral *dodecadron= new Dodecaedron(sideLen);
	Logger::log("> %s\n", dodecadron->toString().c_str());
	delete dodecadron;

	Logger::log("Testando classe pel216::week2::Icosaedron...\n");
	pel216::week2::Polyhedral *icosadron= new Icosaedron(sideLen);
	Logger::log("> %s\n", icosadron->toString().c_str());
	delete icosadron;

}

PRIVATE void pel216::week2::TestSuite::testCylinderClass() {

	double two = 2.0f;

	Logger::log("Testando classe pel216::week2::Cylinder...\n");
	pel216::week2::Cylinder *cylinder = new Cylinder(two, two);
	Logger::log("> %s\n", cylinder->toString().c_str());
	delete cylinder;

}


PRIVATE void pel216::week2::TestSuite::testConeClass() {

	double two = 2.0f;

	Logger::log("Testando classe pel216::week2::Cone...\n");
	pel216::week2::Cone *cone = new Cone(two, two);
	Logger::log("> %s\n", cone->toString().c_str());
	delete cone;

}


PRIVATE void pel216::week2::TestSuite::testPyramidClass() {

	double two = 2.0f;

	Logger::log("Testando classe pel216::week2::Pyramid...\n");
	pel216::week2::Pyramid *pyramid = new Pyramid(two, two);
	Logger::log("> %s\n", pyramid->toString().c_str());
	delete pyramid;

}


PRIVATE void pel216::week2::TestSuite::testSphereClass() {

	Logger::log("Testando classe pel216::week2::Sphere...\n");
	pel216::week2::Sphere *sphere = new Sphere(2.0f);
	Logger::log("> %s\n", sphere->toString().c_str());
	delete sphere;

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week2::TestSuite::run() {
	
	Logger::log("Iniciando execucao dos testes unitarios...\n");

	pel216::week2::TestSuite::testPointClass();
	pel216::week2::TestSuite::testLineClass();
	pel216::week2::TestSuite::testLineSegmentClass();

	pel216::week2::TestSuite::testCircleClass();
	pel216::week2::TestSuite::testPolygons();

	pel216::week2::TestSuite::testPolyhedrals();
	pel216::week2::TestSuite::testCylinderClass();
	pel216::week2::TestSuite::testConeClass();
	pel216::week2::TestSuite::testPyramidClass();
	pel216::week2::TestSuite::testSphereClass();

	Logger::log("Todos os testes foram executados com sucesso\n");

}
