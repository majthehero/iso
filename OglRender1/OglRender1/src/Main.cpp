#include <iostream>

#include <GL\glew.h>
#include <GLFW/glfw3.h>


struct Vertex {
	float x; // position
	float y;
	char p;  // probability (alpha for dither)
	char r;  // red, green, blue
	char g;
	char b;
};

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cerr << "GLFW create window fail." << std::endl;
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Print openGL version */
	std::cout << glGetString(GL_VERSION) << std::endl;

	/* Init glew after we have a valid gl context */
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "glewInit fail" << std::endl;
		return -1;
	}

	/* Vertexbuffers, vertex atributes setup */
	struct Vertex vBuffer[6];
	glCreateBuffers(1, (GLuint*)vBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, (GLuint)vBuffer);
	// !todo: smthg not quite right. missing some setup. do make a triangle and write shaders.

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Draw trianle to see it working */
		// legacy - test and debug only.
		/*glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, -0.5);
		glVertex2f( 0.0,  0.5);
		glVertex2f( 0.5, -0.5);
		glEnd();*/

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();


	/* Quit */
	std::cout << "Quit" << std::endl;
	std::cin.get();
	
	return 0;
}




