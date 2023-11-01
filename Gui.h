#pragma once

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Common.h"

class Gui
{
public:
	Gui() {};
	
	void initialise(GLFWwindow* window);
	void update(bool& useTexture, bool& wireFrame, float& translation, float& scaling, float& rotation, float* viewRotation, Material& material, Light& light, const char* msg);
	void render();

	~Gui() {};
};

