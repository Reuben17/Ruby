#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "FontManager.h"
#include "../audio/SoundManager.h"

namespace Ruby { namespace Graphics {

#define MAX_KEYS		1024
#define MAX_BUTTONS		32

class Window
{
private:
	const char* m_Title;
	int m_Width, m_Height;
	GLFWwindow* m_Window;
	bool m_Closed;
	bool m_Keys[MAX_KEYS];
	bool m_KeyState[MAX_KEYS];
	bool m_KeyTyped[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	bool m_MouseState[MAX_BUTTONS];
	bool m_MouseClicked[MAX_BUTTONS];
	double mx, my;
public:
	Window(const char * title,int width,int height);
	~Window();
	void Clear() const;
	bool Closed() const;
	void Update();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	bool isKeyPressed(unsigned int keycode) const;
	bool isKeyTyped(unsigned int keycode) const;
	bool isMouseButtonPressed(unsigned int button) const;
	bool isMouseButtonClicked(unsigned int button) const;
	void getMousePosition(double& x,double& y) const;
private:
	bool Init();
	friend static void window_resize(GLFWwindow* window, int width, int height);
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};

} }