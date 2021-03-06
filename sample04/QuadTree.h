
#pragma once

#include <list>
using namespace std;

#include "d3dx9.h"
#include "BaseObject.h"
#define MAX_LEVEL	7

enum TYPE_RECT{ TR_NONE, TR_TL, TR_TR, TR_BL, TR_BR };
bool RectInRect(RECT rInner, RECT outerRect);
RECT GetChildRect(RECT rect, int typeRect);

class QuadTree
{
private:
	char CheckInChildRect(RECT rInner);		//Kiểm tra xem thuộc rect con nào
	QuadTree** GetChildNodeFromChildRect(char childRectType);
	bool IsExistDynamic(BaseObject* obj);
	bool IsContainable(BaseObject* obj);
public:

	RECT		rect;
	char		level;

	QuadTree*	topLeft;
	QuadTree*	topRight;
	QuadTree*	bottomLeft;
	QuadTree*	bottomRight;

	list<BaseObject*>	staticObj;
	list<BaseObject*>	dynamicObj;

	QuadTree(int x, int y, int size, char _level);
	~QuadTree();

	bool Add(BaseObject* obj, bool isStatic);
	void GetObjectsInNode(list<BaseObject*>* staticList, list<BaseObject*>* dynamicList);
	void GetObjectsAllNode(list<BaseObject*>* staticList, list<BaseObject*>* dynamicList);
	void GetObjectsInNode(list<BaseObject*>* l, bool isStatic);
	void GetObjectsAllNode(list<BaseObject*>* l, bool isStatic);
	void GetObjectsFromCamera(RECT rCamera, list<BaseObject*>* staticList, list<BaseObject*>* dynamicList);
	void DeleteObj(BaseObject* obj, bool isStatic);
	void Update(/*list<Object*> l*/);
	void QuadTree::Update(list<BaseObject*> l);
};