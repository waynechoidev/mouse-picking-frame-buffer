#include <iostream>

#include "Window.h"
#include "Gui.h"
#include "Sphere.h"
#include "Box.h"
#include "Skybox.h"
#include "Program.h"
#include "UniformBuffer.h"
#include "Texture.h"
#include "Cubemap.h"
#include "Camera.h"
#include "Common.h"
#include <memory>

const int WIDTH = 1920;
const int HEIGHT = 1080;

int main()
{
	Window mainWindow = Window(WIDTH, HEIGHT);
	mainWindow.initialise();
	Gui gui = Gui();
	gui.initialise(mainWindow.getWindow());

	Program mainProgram = Program();
	mainProgram.createFromFiles("main.vert", "main.frag");
	GLuint isPickedUniform = glGetUniformLocation(mainProgram.getID(), "isPicked");

	Program cubemapProgram = Program();
	cubemapProgram.createFromFiles("skybox.vert", "skybox.frag");

	Program pickProgram = Program();
	pickProgram.createFromFiles("main.vert", "pick.frag");
	GLuint indexColorUniform = glGetUniformLocation(pickProgram.getID(), "indexColor");

	UniformBuffer UBO = UniformBuffer(mainProgram.getID());
	UBO.genVertexBuffers();
	UBO.genFragmentBuffers();
	
	Sphere sphere = Sphere(1.0f);
	sphere.initialise();
	sphere.setIndexColor(255, 0, 0);
	Texture earthTexture = Texture();
	earthTexture.initialise("textures/map.jpg");

	Box box = Box(glm::vec3(1.5f));
	box.initialise();
	box.setIndexColor(0, 255, 0);
	Texture boxTexture = Texture();
	boxTexture.initialise("textures/box.jpg");

	Cubemap cubemap = Cubemap();
	std::vector<std::string> faces;
	faces.push_back("textures/LancellottiChapel/right.jpg");
	faces.push_back("textures/LancellottiChapel/left.jpg");
	faces.push_back("textures/LancellottiChapel/top.jpg");
	faces.push_back("textures/LancellottiChapel/bottom.jpg");
	faces.push_back("textures/LancellottiChapel/front.jpg");
	faces.push_back("textures/LancellottiChapel/back.jpg");
	cubemap.initialise(faces);
	Skybox skybox = Skybox(20.0f);
	skybox.initialise();

	// Frame buffer for picking
	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Control
	bool useTexture = true;
	bool wireFrame = false;

	// Model
	glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scaling = { 0.4f, 0.4f, 0.4f };
	glm::vec3 rotation = { 0.5f, 0.5f, 0.0f };

	// Projection
	float aspectRatio = (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

	// View
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec3(0.0f, 0.0f, -1.0f));

	// Material
	Material material;
	material.ambient = 0.1f;
	material.shininess = 1.0f;
	material.diffuse = 1.0f;
	material.specular = 1.0f;
	
	// Light
	Light light;
	light.position = { 0.0f, 0.0f, 2.0f };
	light.direction = { 0.0f, 0.0f, -1.0f };
	light.strength = 1.0;
	light.fallOffStart = 0.0f;
	light.fallOffEnd = 10.0f;
	light.spotPower = 1.0f;
	light.isDirectional = 1;
	light.isPoint = 0;
	light.isSpot = 0;
	light.useBlinnPhong = true;


	unsigned char pickedColor[3];
	glm::mat4 sphereModel(1.0f);
	glm::mat4 boxModel(1.0f);
	const char* msg;
	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (sphere.checkIndexColor(pickedColor)) msg = "Earth";
		else if (box.checkIndexColor(pickedColor)) msg = "Box";
		else msg = "N/A";
		gui.update(useTexture, wireFrame, translation.x, scaling.x, rotation.x, camera.getRotation(), material, light, msg);

		glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_LINE : GL_FILL);
		glEnable(GL_CULL_FACE);
		mainWindow.clear(0.0f, 0.0f, 0.0f, 1.0f);

		// Model
		sphereModel = glm::mat4(1.0f);
		sphereModel = glm::translate(sphereModel, glm::vec3(translation.x - 0.7f, translation.y, translation.z));
		sphereModel = glm::scale(sphereModel, scaling);
		sphereModel = glm::rotate(sphereModel, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		sphereModel = glm::rotate(sphereModel, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		sphereModel = glm::rotate(sphereModel, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		boxModel = glm::mat4(1.0f);
		boxModel = glm::translate(boxModel, glm::vec3(translation.x + 0.7f, translation.y, translation.z));
		boxModel = glm::scale(boxModel, scaling);
		boxModel = glm::rotate(boxModel, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		boxModel = glm::rotate(boxModel, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		boxModel = glm::rotate(boxModel, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Start to check pick
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		pickProgram.use();

		// Draw index color for sphere
		UBO.bindVertexBuffers(sphereModel, projection, camera.calculateViewMatrix());
		auto sphereIndexColor = sphere.getIndexColor();
		glUniform3f(indexColorUniform, (GLfloat)sphereIndexColor[0]/255, (GLfloat)sphereIndexColor[1]/255, (GLfloat)sphereIndexColor[2]/255);
		sphere.draw();

		// Draw index color for box
		UBO.bindVertexBuffers(boxModel, projection, camera.calculateViewMatrix());
		auto boxIndexColor = box.getIndexColor();
		glUniform3f(indexColorUniform, (GLfloat)boxIndexColor[0] / 255, (GLfloat)boxIndexColor[1] / 255, (GLfloat)boxIndexColor[2] / 255);
		box.draw();

		// Get color from frame buffer
		glm::vec2 cursor = mainWindow.getCursor();
		int x = (int)cursor.x;
		int y = (int)cursor.y;
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pickedColor);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// Start to draw main objects
		mainProgram.use();
		UBO.bindFragmentBuffers(useTexture, camera.getPosition(), material, light);

		// Draw sphere
		UBO.bindVertexBuffers(sphereModel, projection, camera.calculateViewMatrix());
		earthTexture.use();
	
		glUniform1i(isPickedUniform, sphere.checkIndexColor(pickedColor));
		sphere.draw();

		// Draw box
		UBO.bindVertexBuffers(boxModel, projection, camera.calculateViewMatrix());
		boxTexture.use();
		glUniform1i(isPickedUniform, box.checkIndexColor(pickedColor));
		box.draw();
		
		// Draw skybox
		glDepthMask(GL_FALSE);
		cubemapProgram.use();
		cubemap.use();
		skybox.draw();
		glDepthMask(GL_TRUE);

		gui.render();

		// Initialise
		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		mainWindow.swapBuffers();
	}
}

