
#include "trajectory.h"
#include "point.h"
#include <vector>


using namespace std;

namespace Model{

trajectory::trajectory(point* from[],int len, int skip=0)
{
	this->assign(from + skip, from + len);
};

point* trajectory::get(int i)
{
	return (*this)[i];
};

point* trajectory::operator[](int idx) const
{
	return ((vector<point*>)(*this))[idx];
};
int trajectory::len()
{	int size=(*this).size();
	return size;

};
point *trajectory::add(point	*nuevo)
{
 this->push_back(nuevo);
 return nuevo;
};
}
