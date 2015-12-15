#pragma once
#include <list>
#include "BaseObject.h"
class QuadTree
{
public:
	QuadTree *tl;
	QuadTree *tr;
	QuadTree * bl;
	QuadTree * br;
	list<BaseObject*> object;
	QuadTree();
	~QuadTree();
	bool Add(BaseObject* obj);
};

