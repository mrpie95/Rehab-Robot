#include "Window.h"
#include <iostream>

Window::Window(): name("memes"), width(800), height(600), xPos(0), yPos(0)
{
}

Window::Window(const char* name, int width, int height, int xPos, int yPos): name(name), width(width), height(height), xPos(xPos), yPos(yPos)
{
}


Window::~Window()
{
	SDL_GL_DeleteContext(openglContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = SDL_CreateWindow(name, xPos, yPos, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	openglContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew failed to init" << std::endl;
	}

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);


}

SDL_Window * Window::getWindow()
{
	return window;
}

SDL_GLContext Window::getOpenGLContext()
{
	return openglContext;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

void Window::updateWindowParams()
{
	SDL_GetWindowSize(window, &width, &height);
}

void Window::FlipBuffers()
{
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}
