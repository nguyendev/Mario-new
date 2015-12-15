#include "QuadTree.h"


QuadTree::QuadTree()
{
}


QuadTree::~QuadTree()
{
	if (tl != NULL) delete tl;
		tl = NULL;
	if (tr != NULL) delete tr;
		tr = NULL;
	if (bl != NULL) delete bl;
		bl = NULL;
	if (br != NULL) delete br;
		br = NULL;
	list<BaseObject*>::iterator i;
	for (i = object.begin(); i != object.end(); i++)
	{
			if ((*i) != NULL) delete *i;
			(*i) = NULL;
	}
}
