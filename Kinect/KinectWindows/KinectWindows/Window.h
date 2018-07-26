#pragma once
#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <OpenNI.h>
#include <NiTE.h>

class Window
{
private:
	const char* name;
	int width;
	int height; 
	const int yPos;
	const int xPos;
	SDL_Window* window;
	SDL_GLContext openglContext;

public:
	Window();
	Window(const char* name,int width, int height, int xPos, int yPos);

	~Window();

	void init();

	SDL_Window* getWindow();
	SDL_GLContext getOpenGLContext();

	int getWidth();
	int getHeight();
	void updateWindowParams();
	void FlipBuffers();
};