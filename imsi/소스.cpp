#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 1400;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i, j;
	if (i0 == i1)
	{
		for (j = j0;j <= j1;j++)
			drawPixel(i0, j, red, green, blue);
	}
	else
	{
		if (j0 == j1)
		{
			for (i = i0; i <= i1; i++)
				drawPixel(i, j0, red, green, blue);
		}
		else
		{
			for (i = i0; i <= i1; i++)
			{
				if (j0 < j1)
				{
					for (j = j0;j <= j1;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0)
							drawPixel(i, j, red, green, blue);
					}
				}
				else
				{
					for (j = j1;j <= j0;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0)
							drawPixel(i, j, red, green, blue);
					}
				}
			}
		}
	}
}

void drawThick(const int& i0, const int& j0, const int& i1, const int& j1, const int t, const float& red, const float& green, const float& blue)
{
	int i, j, k;
	if (i0 == i1)
	{
		for (j = j0;j <= j1;j++)
			for (k = i0 - t;k <= i0 + t;k++)
				drawPixel(k, j, red, green, blue);
	}
	else
	{
		if (j0 == j1)
		{
			for (i = i0; i <= i1; i++)
				for (k = j0 - t;k <= j0 + t;k++)
					drawPixel(i, k, red, green, blue);
		}
		else
		{
			for (i = i0; i <= i1; i++)
			{
				if (j0 < j1)
				{
					for (j = j0;j <= j1;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0)
						{
							for (k = -t;k <= t;k++)
							{
								drawPixel(i + k, j, red, green, blue);
								drawPixel(i, j + k, red, green, blue);
							}
						}
					}
				}
				else
				{
					for (j = j1;j <= j0;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0)
						{
							for (k = -t;k <= t;k++)
							{
								drawPixel(i + k, j, red, green, blue);
								drawPixel(i, j + k, red, green, blue);
							}
						}
					}
				}
			}
		}
	}
}
 
void drawRect(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i, j;
	for (i = i0;i <= i1;i++)
		drawPixel(i, j0, red, green, blue);
	for (i = i0;i <= i1;i++)
		drawPixel(i, j1, red, green, blue);
	for (j = j0;j <= j1;j++)
		drawPixel(i0, j, red, green, blue);
	for (j = j0;j <= j1;j++)
		drawPixel(i1, j, red, green, blue);
}

void drawRectF(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i, j;
	for (i = i0;i <= i1;i++)
	{
		for (j = j0;j <= j1;j++)
		{
			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawCirc(const int& i0, const int& j0, const int& r, const float& red, const float& green, const float& blue)
{
	int i, j;
	int a, b;

	for (i = i0 - r;i <= i0 + r;i++)
	{
		for (j = j0 - r;j <= j0 + r;j++)
		{
			a = ((i - i0)*(i - i0)) + ((j - j0)*(j - j0));
			b = r*r;
			if (a < b&&a >= b - 2 * r + 1)
			{
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	for (int i = 0; i < width*height; i++)
	{
		pixels[i * 3 + 0] = 1.0f; // red 
		pixels[i * 3 + 1] = 1.0f; // green
		pixels[i * 3 + 2] = 1.0f; // blue
	}
	drawThick(50, 50, 150, 450, 2, 1.0f, 0.0f, 0.0f);
	drawRect(200, 50, 300, 450, 1.0f, 0.5f, 0.0f);
	drawRectF(350, 50, 450, 450, 1.0f, 1.0f, 0.0f);
	drawLine(500, 50, 500, 450, 0.0f, 0.9f, 0.0f);
	drawLine(500, 50, 600, 50, 0.0f, 0.9f, 0.0f);
	drawLine(500, 450, 600, 50, 0.0f, 0.9f, 0.0f);
	drawLine(700, 50, 900, 50, 0.0f, 0.0f, 1.0f);
	drawLine(650, 300, 700, 50, 0.0f, 0.0f, 1.0f);
	drawLine(900, 50, 950, 300, 0.0f, 0.0f, 1.0f);
	drawLine(650, 300, 800, 450, 0.0f, 0.0f, 1.0f);
	drawLine(800, 450, 950, 300, 0.0f, 0.0f, 1.0f);
	drawCirc(1200, 250, 170, 1.0f, 0.0f, 1.0f);
	

	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
