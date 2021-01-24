#ifndef TRAjECTORY_H
#define TRAjECTORY_H

#include <vector>
#include "point.h"

using namespace std;

namespace Model{


class trajectory:

	public vector<point*> 
{
	public :
	trajectory(): vector<point*>() {};
	trajectory (point *from[],int ,int);
	point *add(point*);
	point* get(int);
	int len();
	point* operator[](int idx)const;
};
}
#endif
