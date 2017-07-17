#include "OpenGLContext.hpp"
/////////////////////////////////////////////////////////////////
//	GLContextWinapi Definitions
/////////////////////////////////////////////////////////////////
bool h3d::GLContextWinapi::createContext(HWND hwnd,ContextSettings cs)
{
	this->m_hwnd = hwnd;
	m_hdc = GetDC(m_hwnd); //Get device context

	// set Pixelformatdescriptor
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags			= PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | 
						  PFD_DRAW_TO_WINDOW;
	pfd.iPixelType		= PFD_TYPE_RGBA;
	pfd.cColorBits		= 32;
	pfd.cDepthBits		= 32;
	pfd.iLayerType		= PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (nPixelFormat == 0)
		return false;

	BOOL bResult = SetPixelFormat(m_hdc, nPixelFormat, &pfd);
	if (!bResult) 
		return false;

	HGLRC tempOGLContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, tempOGLContext);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
		return false;

	int attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 5,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hrc = wglCreateContextAttribsARB(m_hdc, NULL, attributes);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempOGLContext);
		wglMakeCurrent(m_hdc, m_hrc);
	}
	else
		m_hrc = tempOGLContext;

	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

	return true;
}