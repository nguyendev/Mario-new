#include "QuadTree.h"

QuadTree::QuadTree(int x, int y, int size, char _level)
{
	RECT r = { x, y, x + size, 500 };
	rect = r;
	level = _level;
	topLeft = topLeft1 = topRight = topRight1 = NULL;
}
QuadTree::~QuadTree()
{
	if (topLeft != NULL) delete topLeft;
	topLeft = NULL;
	if (topLeft1 != NULL) delete topLeft1;
	topLeft1 = NULL;
	if (topRight != NULL) delete topRight;
	topRight = NULL;
	if (topRight1 != NULL) delete topRight1;
	topRight1 = NULL;
	list<BaseObject*>::iterator i;
	for (i = staticObj.begin(); i != staticObj.end(); i++)
	{
		if ((*i) != NULL) delete *i;
		(*i) = NULL;
	}
	for (i = dynamicObj.begin(); i != dynamicObj.end(); i++)
	{
		if ((*i) != NULL) delete *i;
		(*i) = NULL;
	}
}

QuadTree** QuadTree::GetChildNodeFromChildRect(char childRectType)
{
	switch (childRectType)
	{
	case TR_TL:
		return &topLeft;
	case TR_TL1:
		return &topLeft1;
	case TR_TR:
		return &topRight;
	case TR_TR1:
		return &topRight1;
	default:
		return NULL;
	}
}
bool QuadTree::Add(BaseObject* obj, bool isStatic)
{
	//Nếu Rect của object không thuộc thì không thêm
	if (obj == NULL) return false;
	char childRectType = CheckInChildRect(obj->_rect);
	if (childRectType == TR_NONE || level >= MAX_LEVEL)			//Nếu không thể chứa vào hình chữ nhật con
	{
		if (isStatic == true)
			staticObj.push_back(obj);
		else dynamicObj.push_back(obj);
		obj->_oldNode = this;
		return true;
	}
	else
	{
		RECT r;//=GetChildRect(rect,childRect);
		QuadTree** qChild = GetChildNodeFromChildRect(childRectType);
		if (*qChild == NULL)
		{
			r = GetChildRect(rect, childRectType);
			(*qChild) = new QuadTree(r.left, r.top, r.right - r.left, level + 1);
		}
		(*qChild)->Add(obj, isStatic);
	}
}

void QuadTree::Update(/*list<Object*> l*/)
{
	list<BaseObject*> l;
	GetBaseObjectsAllNode(&l, false);
	list<BaseObject*>::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		BaseObject* obj = (*i);
		QuadTree* oldNode = obj->_oldNode;
		if (!oldNode->IsExistDynamic(obj))break;		//Nếu object không còn tồn tại thì bỏ qua
		if (!oldNode->IsContainable(obj))			//Nếu object không thể chứa được trong list cũ
		{
			oldNode->dynamicObj.remove(obj);
			Add(obj, false);
		}
	}
}
void QuadTree::Update(list<BaseObject*> l)
{
	int n = l.size();
	if (n == 0)
		n = 1;
	list<BaseObject*>::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		BaseObject* obj = (*i);
		if (obj->_ID == 1)
			n = 1;
		QuadTree* oldNode = obj->_oldNode;
		if (!oldNode->IsExistDynamic(obj))break;		//Nếu object không còn tồn tại thì bỏ qua
		if (!oldNode->IsContainable(obj))			//Nếu object không thể chứa được trong list cũ
		{
			oldNode->dynamicObj.remove(obj);
			Add(obj, false);
		}
	}
}
//Kiểm tra một hình chữ nhật có thuộc rect con nào không.
char QuadTree::CheckInChildRect(RECT rInner)
{
	if (RectInRect(rInner, GetChildRect(rect, TR_TL))) return TR_TL;
	if (RectInRect(rInner, GetChildRect(rect, TR_TL1))) return TR_TL1;
	if (RectInRect(rInner, GetChildRect(rect, TR_TR))) return TR_TR;
	if (RectInRect(rInner, GetChildRect(rect, TR_TR1))) return TR_TR1;
	else return TR_NONE;
}

void QuadTree::GetBaseObjectsInNode(list<BaseObject*>* staticList, list<BaseObject*>* dynamicList)
{
	staticList->insert(staticList->end(), staticObj.begin(), staticObj.end());
	dynamicList->insert(dynamicList->end(), dynamicObj.begin(), dynamicObj.end());
}
void QuadTree::GetBaseObjectsInNode(list<BaseObject*>* l, bool isStatic)
{
	if (isStatic == true)
		l->insert(l->end(), staticObj.begin(), staticObj.end());
	else
		l->insert(l->end(), dynamicObj.begin(), dynamicObj.end());
}
void QuadTree::GetBaseObjectsAllNode(list<BaseObject*>* l, bool isStatic)
{
	GetBaseObjectsInNode(l, isStatic);
	if (topLeft != NULL) topLeft->GetBaseObjectsAllNode(l, isStatic);
	if (topLeft1 != NULL) topLeft1->GetBaseObjectsAllNode(l, isStatic);
	if (topRight != NULL) topRight->GetBaseObjectsAllNode(l, isStatic);
	if (topRight1 != NULL) topRight1->GetBaseObjectsAllNode(l, isStatic);
}
//Node - TL - TR - BL - BR
void QuadTree::GetBaseObjectsAllNode(list<BaseObject*>* staticList, list<BaseObject*>* dynamicList)
{
	GetBaseObjectsInNode(staticList, dynamicList);
	if (topLeft != NULL) topLeft->GetBaseObjectsAllNode(staticList, dynamicList);
	if (topLeft1 != NULL) topLeft1->GetBaseObjectsAllNode(staticList, dynamicList);
	if (topRight != NULL) topRight->GetBaseObjectsAllNode(staticList, dynamicList);
	if (topRight1 != NULL) topRight1->GetBaseObjectsAllNode(staticList, dynamicList);
}
void QuadTree::GetBaseObjectsFromCamera(RECT rCamera, list<BaseObject*>* staticList, list<BaseObject*>* dynamicList)
{
	char childRect = CheckInChildRect(rCamera);
	if (childRect == TR_NONE || level >= MAX_LEVEL)
	{
		GetBaseObjectsAllNode(staticList, dynamicList);
	}
	else
	{
		GetBaseObjectsInNode(staticList, dynamicList);
		QuadTree** qChild = GetChildNodeFromChildRect(childRect);
		if (*qChild != NULL) (*qChild)->GetBaseObjectsFromCamera(rCamera, staticList, dynamicList);
	}

}
bool QuadTree::IsExistDynamic(BaseObject* obj)
{
	list<BaseObject*>::iterator i;
	for (i = dynamicObj.begin(); i != dynamicObj.end(); i++)
	if (*i == obj) return true;
	return false;
}
bool QuadTree::IsContainable(BaseObject* obj)
{
	//RECT của Object thuộc Rect của Quadtree nhưng không thuộc rect con thì return true
	if (RectInRect(obj->_rect, rect) && CheckInChildRect(obj->_rect) == TR_NONE)
		return true;
	else return false;
}
bool RectInRect(RECT rInner, RECT outerRect)
{
	return (rInner.left >= outerRect.left&&rInner.right <= outerRect.right
		&&rInner.top >= outerRect.top&&rInner.bottom <= outerRect.bottom);
}

RECT GetChildRect(RECT rect, int typeRect)
{
	int vCenterLine = (rect.left + rect.right) / 4;
	RECT r;
	switch (typeRect)
	{
	case TR_TL:					//TypeRect TopLeft
		r.left = rect.left; r.top = rect.top; r.right = vCenterLine / 2; r.bottom = vCenterLine;
		return r;
	case TR_TL1:
		r.left = vCenterLine / 2; r.top = rect.top; r.right = vCenterLine; r.bottom = vCenterLine;
		return r;
	case TR_TR:
		r.left = vCenterLine; r.top = rect.top; r.right = vCenterLine + vCenterLine / 2; r.bottom = vCenterLine;
		return r;
	case TR_TR1:
		r.left = vCenterLine + vCenterLine / 2; r.top = rect.top; r.right = rect.right; r.bottom = vCenterLine;
		return r;
	}
}
void QuadTree::DeleteObj(BaseObject* obj, bool isStatic)
{
	if (obj->_oldNode == this)
	{
		BaseObject* o;
		list<BaseObject*>::iterator i;
		if (isStatic == true)
		{
			for (i = staticObj.begin(); i != staticObj.end(); i++)
			{
				o = *i;
				if (o == obj)
				{
					staticObj.remove(obj);
					if (obj != NULL) delete obj;
					obj = NULL;
					return;
				}
			}
		}
		else
		{
			for (i = dynamicObj.begin(); i != dynamicObj.end(); i++)
			{
				o = *i;
				if (obj == o)
				{
					dynamicObj.remove(obj);
					if (obj != NULL) delete obj;
					obj = NULL;
					return;
				}
			}
		}
	}
	if (topLeft != NULL) topLeft->DeleteObj(obj, isStatic);
	if (topRight != NULL) topRight->DeleteObj(obj, isStatic);
	if (topLeft1 != NULL) topLeft1->DeleteObj(obj, isStatic);
	if (topRight1 != NULL) topRight1->DeleteObj(obj, isStatic);
}