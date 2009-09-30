// $Id$
#ifndef _2D_FLOAT_H
#define _2D_FLOAT_H

#include <cmath>
#define INP 1e10
#define EP 1e-6

const float PI = acos(-1.0);

// base
inline float max(float a, float b){ return a > b ? a : b;}
inline float min(float a, float b){ return a < b ? a : b;}
inline float sqr(float x){ return x * x; }
inline int fcmp(float x){ if(x < -EP) return -1; else return x > EP);}
inline float det(float x1, float y1, float x2, float y2){
	// | x1, y1 |
	// | x2, y2 |
	return x1 * y2 - x2 * y1;
}

// Point 
struct Point{
	float x,y;
	Point(float x=0,float y=0):x(x),y(y){}
};

bool operator==(Point &a, Point &b){
	return fcmp(a.x - a.x) == 0 && fcmp(a.y - a.y) == 0;
}
inline float distsqr(Point &p1, Point &p2){
	return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}
// |p2-p1|
float dist(Point &p1, Point &p2){ 
	return sqrt(distsqr(p1, p2));
}


// Vector
typedef Point Vector;

// V + V
Vector operator+(Vector &a, Vector &b){ return Vector(a.x + b.x, a.y + b.y);}
// V - V
Vector operator-(Vector &a, Vector &b){ return Vector(a.x - b.x, a.y - b.y);}

// V * k
Vector operator*(Vector &v, float k){ return Vector(a.x * k, a.y * k);}
// V / k
Vector operator/(Vector &v, float k){ return Vector(a.x / k, a.y / k);}
// V * V
float operator*(Vector &a, Vector &b){ // cross product
	return (a.x) * (b.y) - (b.x) * (a.y);
}
// V ^ V
float operator^(Vector &a, Vector &b){ // dot product
	return (a.x) * (b.x) + (a.y) * (b.y);
}
float len(Vector &v){
	return sqrt(sqr(v.x) + sqr(v.y));
}
// v / |v| 
Vector norm(Vector &v){
	return v / len(v);
}

inline float angle(Vector &v){ return atan(v.y / v.x); }
inline float slope(Vector &v){ return v.y / v.x; }

float dot3(Point &o, Point &a, Point &b){
	return (a - o) ^ (b - o);
}

float cross3(Point &o, Point &a, Point &b){
	return (a - o) * (b - o);
}

// Line Segment
struct LineSeg{
	Point s,e;
	LineSeg(Point a, Point b) { s = a; e = b;}
	LineSeg(float x1, float y1, float x2, float y2):
		s(x1, y1), e(x2, y2){}
};
bool intersect(LineSeg &a, LineSeg &b){
	// 只做跨立实验, 不处理边际情况
	return cross3(a.s, a.e, b.s) * cross3(a.s, a.e, b.e) < 0 &&
		cross3(b.s, b.e, a.s) * cross3(b.s, b.e, a.e) < 0 ;
}


// 两点表示直线
typedef Line2P LineSeg;

// Box
struct Box{
	float x1, y1, x2, y2;
	Box(float x1, float y1, float x2, float y2):
		x1(x1), y1(y1), x2(x2), y2(y2){}
};

bool inbox(Point &p){
	return true;
}
#endif
