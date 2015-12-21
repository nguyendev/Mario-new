#ifndef _DXAUDIO_H
#define _DXAUDIO_H

#include "dsutil.h"

//primary DirectSound object
extern CSoundManager *dsound;

//function prototypes
class Audio
{
	static Audio* m_instance;
public:
	static Audio* getInstance();
	Audio(){};
	void initialize(HWND);
	CSound *LoadSound(char*);
	void PlaySound(CSound *);
	void LoopSound(CSound *);
	void StopSound(CSound *);
};

#endif

