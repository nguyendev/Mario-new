#include "TimeManager.h"

TimeManager::TimeManager()
{
	INT64 tickPerSecond;
	if(QueryPerformanceFrequency((LARGE_INTEGER*)&tickPerSecond))
	{
		secondPerTick=1.0f/tickPerSecond;
		useQueryPerformance=true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	}
	else
	{
		secondPerTick=0.001;
		useQueryPerformance=false;
		lastTime=timeGetTime();
	}
	currentTime=0;
	FPSCounter=0;
	waitFPSUpdate=0;
	TPF=0.05;
	numTPFArrElement=0;
}
TimeManager::~TimeManager(){};
void TimeManager::LimitFPS(float FPSLimit)
{
	float waitNextFrame=0;
	//Chờ lần kế tiếp
	while(waitNextFrame<1.0f/FPSLimit)
	{
		if(useQueryPerformance)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		}
		else 
			currentTime=timeGetTime();
		waitNextFrame=(currentTime-lastTime)*secondPerTick;
	}
	lastTime=currentTime;

	if(waitNextFrame<0.1)
	{
		if(numTPFArrElement<10)
			numTPFArrElement++;
		memcpy(TPFArray+1,TPFArray,sizeof(TPFArray)-sizeof(int));
		TPFArray[0]=waitNextFrame;
	}
	TPF=0;
	for(int i=0;i<numTPFArrElement;i++)
	{
		TPF+=TPFArray[i];
	}
	TPF=TPF/numTPFArrElement;

	//Tính FPS
	waitFPSUpdate+=waitNextFrame;
	FPSCounter++;
	if(waitFPSUpdate>1)
	{
		FPS=FPSCounter;
		FPSCounter=0;
		waitFPSUpdate=0;
	}
}