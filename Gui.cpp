#include "Gui.h"

void Gui::initialise(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	//io.FontGlobalScale = 1.5f;
	io.FontGlobalScale = 2.0f;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void Gui::update(bool& useTexture, bool& wireFrame, float& translation, float& scaling, float& rotation, float* viewRotation, Material& material, Light& light, const char* msg)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Scene Control");

	// Print framerate
	ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
	ImGui::Checkbox("Use Texture", &useTexture);
	//ImGui::Checkbox("Wire Frame", &wireFrame);

	//ImGui::Text("Model");
	//ImGui::SliderFloat3("Translation", &translation, -2.0f, 2.0f);
	//ImGui::SliderFloat3("Rotation", &rotation, -3.14f, 3.14f);
	//ImGui::SliderFloat3("Scaling", &scaling, 0.1f, 2.0f);

	//ImGui::Text("View");
	//ImGui::SliderFloat3("View rotation", viewRotation, -3.14f, 3.14f);

	//ImGui::Text("Material");
	//ImGui::SliderFloat("Diffuse", &material.diffuse, 0.0f, 1.0f);
	//ImGui::SliderFloat("Specular", &material.specular, 0.0f, 1.0f);

	//ImGui::Text("Light");
	//ImGui::Checkbox("Use Blinn Phong", &light.useBlinnPhong);
	//if (ImGui::RadioButton("Directional Light", light.isDirectional == 1))
	//{
	//	light.isDirectional = 1;
	//	light.isPoint = 0;
	//	light.isSpot = 0;
	//}
	//ImGui::SameLine();
	//if (ImGui::RadioButton("Point Light", light.isPoint == 1))
	//{
	//	light.isDirectional = 0;
	//	light.isPoint = 1;
	//	light.isSpot = 0;
	//}
	//ImGui::SameLine();
	//if (ImGui::RadioButton("Spot Light", light.isSpot == 1))
	//{
	//	light.isDirectional = 0;
	//	light.isPoint = 0;
	//	light.isSpot = 1;
	//}
	//ImGui::SliderFloat3("Light Position", &light.position[0], -2.0f, 2.0f);
	//ImGui::SliderFloat("Fall off start", &light.fallOffStart, 0.0f, 5.0f);
	//ImGui::SliderFloat("Fall off end", &light.fallOffEnd, 0.0f, 10.0f);
	//ImGui::SliderFloat("Spot power", &light.spotPower, 1.0f, 512.0f);

	ImGui::Text("Picked: %s", msg);

	ImGui::End();
}

void Gui::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
