#pragma once
#include"../My3Dproject/engine/include/constant/includefile.h"
#include"../My3Dproject/engine/include/unit/box.h"
#include"engine\include\render\shader.h"
#include"../My3Dproject/engine/include/root.h"
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
// Set up vertex data (and buffer(s)) and attribute pointers
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
// World space positions of our cubes
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
int main()
{
	/*if (true)
	{
		return test();
	}*/
	auto render = myrender::Root::getInstance()->getRender();
	render->Init_Render();
	auto viewport = myrender::Root::getInstance()->getViewPort();
	int shader = render->IncludeShader("transform");
	render->LoardVertexArry(vertices, sizeof(vertices));
	render->SetTexture("./resource/image/container.jpg");
	render->SetTexture("./resource/image/awesomeface.png");
	std::vector<myrender::Box*> boxlist;
	for (size_t i = 0; i < 10; i++)
	{
		auto box = new myrender::Box();
		GLfloat angle = 20.0f * i;
		box->SetShader(shader);
		box->MadeModelMat(cubePositions[i], angle, glm::vec3(1.0f, 0.3f, 0.5f));
		boxlist.push_back(box);
	}
	render->BlindTexture();
	render->UseShder(); // don't forget to activate/use the shader before setting uniforms!
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
	auto render = myrender::Render::getInstance();
	render->Init_Render();
	// Build and compile our shader program
	int shader = render->IncludeShader("transform");
	GLuint VBO, VAO;
	VAO = render->LoardVertexArry(vertices, sizeof(vertices));
	GLuint texture1;
	GLuint texture2;
	texture1 = render->SetTexture("./resource/image/container.jpg");
	texture2 = render->SetTexture("./resource/image/awesomeface.png");
	glm::mat4 view = get();
	glm::mat4 projection = get();
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)960 / (GLfloat)720, 0.1f, 100.0f);
	glm::mat4 model[10];
	for (size_t i = 0; i < 10; i++)
	{
		model[i] = get();
		model[i] = glm::translate(model[i], cubePositions[i]);
		GLfloat angle = i*20.0f;
		model[i] = glm::rotate(model[i], angle, glm::vec3(1.0f, 0.3f, 0.5f));
	}
	render->BlindTexture();
	// Game loop
	while (true)
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render->setShaderproperty(shader, "view", view);
		render->setShaderproperty(shader, "projection", projection);
		render->UseShder();
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			render->setShaderproperty(shader, "model", model[i]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Swap the screen buffers
		//glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}