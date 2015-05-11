#include "Base.h"

#include "common.h"


Base* Base::m_currentScene = 0;
Base::Base()
{
	
}


Base::~Base()
{
}

void Base::display()
{
	m_currentScene->selfDisplay();
}

