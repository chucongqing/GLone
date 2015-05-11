#pragma once
#include "Camera.h"
#include "MyControls.h"

#define KEYBORD_ON

class Base
{
public:
	Base();
	virtual ~Base();

	virtual void init() = 0;
	virtual void selfDisplay() = 0;
	static void display();
	
	static Base* m_currentScene;
protected:
	
};

	

