#include "BaseObject.h"
class CBox:public BaseObject
{

		//position of top-left corner
	
public:
	float x, y;

	//dimensions
	float w, h;

	//velocity
	float vx, vy;
	CBox();
	CBox(BaseObject*);
	~CBox();
};

