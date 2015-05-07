#include <iostream>
#include <tchar.h>
#include <windows.h>

//#define FRAGMENT_TEST
//#define TEST1
#define FRAGMENT_TEST2

#ifdef FRAGMENT_TEST
#include "fragment_test.h"
#endif

#ifdef TEST1
#include "test1.h"
#endif

#ifdef FRAGMENT_TEST2
#include "fragment_test2.h"
#endif


int _tmain(int argc, TCHAR* argv[])
{
	
	
	glutInit(&argc, argv);
	

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutInitDisplayMode(  fragtest2::windowmode );

	glutCreateWindow("3D Effects Demo");



	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	
	fragtest2::init();
	glutDisplayFunc(fragtest2::display);
	//glutKeyboardFunc(fragtest2::keyboard);
	//glutReshapeFunc();
	glutMainLoop();



	return 0;
}