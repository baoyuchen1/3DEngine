#pragma once
#include"../My3Dproject/engine/include/constant/includefile.h"
#include"../My3Dproject/engine/include/unit/box.h"
#include"engine\include\render\shader.h"
#include"../My3Dproject/engine/include/root.h"
#include"engine\include\render\lighting.h"
#include"engine\include\camera\camera.h"
// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
using namespace myrender;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int test();
glm::mat4 get();
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLfloat vertices[] = {
	// Positions          // Normals           // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
// Positions all containers
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
std::vector<myrender::Box*> boxlist;
int main()
{
	if (false)
	{
		return test();
	}
	auto render = myrender::Root::getInstance()->getRender();
	render->Init_Render();
	auto viewport = myrender::Root::getInstance()->getViewPort();

	render->LoardVertexArry(vertices, sizeof(vertices));
	render->CreatNewLighting(lightPos, lightColor,Lighting_type::POINTLIGHTING);
	myrender::PointLighting* lighting;
	lighting = (myrender::PointLighting*)render->GetLightByIndex(0);
	lighting->SetAmbient(VEC3(0.2f, 0.2f, 0.2f));
	lighting->SetDiffuse(VEC3(0.5f, 0.5f, 0.5f));
	lighting->SetSpecular(VEC3(1.0f, 1.0f, 1.0f));
	lighting->SetConstant(1.0f);
	lighting->SetLinear(0.09f);
	lighting->SetQuadratic(0.032f);
	render->CreatNewLighting(lightPos, lightColor, Lighting_type::DIRECTIONLIGHTING);
	myrender::DirectionLighting* dl;
	dl = (myrender::DirectionLighting*)render->GetLightByIndex(0);
	dl->SetAmbient(VEC3(0.2f, 0.2f, 0.2f));
	dl->SetDiffuse(VEC3(0.5f, 0.5f, 0.5f));
	dl->SetSpecular(VEC3(1.0f, 1.0f, 1.0f));
	dl->SetDirection(VEC3(-0.2f, -1.0f, -0.3f));
	myrender::Lighting::SetVAO();



	int diffuese = render->SetTexture("./resource/image/container2.jpg");
	int specular = render->SetTexture("./resource/image/container2_specular.jpg");
	for (size_t i = 0; i < 10; i++)
	{
		auto box = new myrender::Box();
		GLfloat angle = 20.0f * i;
		box->MadeModelMat(cubePositions[i], angle, glm::vec3(1.0f, 0.3f, 0.5f));
		box->InitMaterial(diffuese, specular, 32);
		boxlist.push_back(box);
	}
	render->ReadyForDraw();
	while (!viewport->WindowShouldClose())
	{
		for (auto &it : boxlist)
		{
			it->Draw();
		}
		render->Draw();
	}
	render->Release();
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

glm::mat4 get()
{
	glm::mat4 m = glm::mat4::mat();
	GLfloat t[] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};
	m = glm::make_mat4x4(t);
	return m;
}


int test()
{ // glfw: initialize and configure

	auto render = myrender::Root::getInstance()->getRender();
	render->Init_Render();
	auto viewport = myrender::Root::getInstance()->getViewPort();
	// Build and compile our shader program
	Shader lightingShader("./resource/shader/pointlighting.vs", "./resource/shader/pointlighting.fs");
	Shader lampShader("./resource/shader/transform.vs", "./resource/shader/transform.fs");
	// First, set the container's VAO (and VBO)
	GLuint VBO, containerVAO;
	render->LoardVertexArry(vertices, sizeof(vertices));
	containerVAO = 1;
	VBO = 1;
	Lighting::SetVBO(1);
	myrender::Lighting::SetVAO();


	// Diffuse map
	
	int diffuseMap = render->SetTexture("./resource/image/container2.jpg");
	int specularMap = render->SetTexture("./resource/image/container2_specular.png");

	// Set texture units
	lightingShader.use();
	glUniform1i(glGetUniformLocation(lightingShader.GetID(), "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.GetID(), "material.specular"), 1);


	// Game loop
	while (!viewport->WindowShouldClose())
	{

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.use();
		GLint lightPosLoc = glGetUniformLocation(lightingShader.GetID(), "light.position");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.GetID(), "viewPos");
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		// Set lights properties
		glUniform3f(glGetUniformLocation(lightingShader.GetID(), "light.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.GetID(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.GetID(), "light.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.GetID(), "light.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.GetID(), "light.linear"), 0.09);
		glUniform1f(glGetUniformLocation(lightingShader.GetID(), "light.quadratic"), 0.032);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.GetID(), "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.GetID(), "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.GetID(), "view");
		GLint projLoc = glGetUniformLocation(lightingShader.GetID(), "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// Bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// Draw the container (using container's vertex attributes)
		/*glBindVertexArray(containerVAO);
		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);*/

		// Draw 10 containers with the same VAO and VBO information; only their world space coordinates differ
		glm::mat4 model;
		glBindVertexArray(1);
		for (GLuint i = 0; i < 10; i++)
		{
			model = get();
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.GetID(), "model");
		viewLoc = glGetUniformLocation(lampShader.GetID(), "view");
		projLoc = glGetUniformLocation(lampShader.GetID(), "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = get();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(2);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		viewport->SwapBuffers();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
	return 0;
}

