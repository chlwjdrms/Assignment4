#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"


const int width = 1500;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawCircle(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue) {
	for (int i = i4; i <= i5; i++) {
		for (int j = j4; j <= j5; j++) {
			int r = (i5 - i4) / 2;
			int a = (i - (i4 + i5) / 2)*(i - (i4 + i5) / 2) + (j - (j4 + j5) / 2)*(j - (j4 + j5) / 2);
			if (a <= r*r && a >= (r - 3)*(r - 3)) {
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}
void isCircle(int i1, int i2, int j1, int j2, double posx, double posy) {
	j1 = j1;
	j2 = j2;
	if (posx >= i1 && posx <= i2 && height - posy >= j1 && height - posy <= j2)
		drawCircle(i1, j1, i2, j2, 0.0f, 0.0f, 1.0f);
	else
		drawCircle(i1, j1, i2, j2, 1.0f, 0.0f, 0.0f);
}
void drawCircleInSlash(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = -2; i < 2; i++) {
		drawLine(k1, l1 + i, k2, l2 + i, 1.0f, 0.0f, 0.0f);
	}
}
void drawCircleInCircle(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = k1; i <= k2; i++) {
		for (int j = l1; j <= l2; j++) {
			int r = (k2 - k1) / 2;
			int a = (i - (k1 + k2) / 2)*(i - (k1 + k2) / 2) + (j - (l1 + l2) / 2)*(j - (l1 + l2) / 2);
			if (a <= r*r && a >= (r - 8)*(r - 8)) {
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}
void drawCircleInRect(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = k1; i <= k2; i++) {
		for (int j = l1; j <= l2; j++) {
			if (!(i > k1 + 2 && i < k2 - 2 && j > l1 + 2 && j < l2 - 2)) {
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}
void drawCircleInX(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = -2; i < 2; i++) {
		drawLine(k1, l1 + i, k2, l2 + i, 1.0f, 0.0f, 0.0f);
	}
	for (int i = -2; i < 2; i++) {
		drawLine(k1, l2 + i, k2, l1 + i, 1.0f, 0.0f, 0.0f);
	}
}
void drawCircleInDownArrow(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = l1; i < l2; i++) { // 세로 직선
		drawPixel((k1+k2)/2, i, red, green, blue);
	}
	// 화살표 끝
	drawLine((k1 + k2) / 2 - (l2 - l1)/5, l1 + (l2 - l1) / 5, (k1 + k2) / 2, l1, 1.0f, 0.0f, 0.0f);
	drawLine((k1 + k2) / 2, l1, (k1 + k2) / 2 + (l2 - l1) / 5, l1 + (l2 - l1) / 5, 1.0f, 0.0f, 0.0f);
}
void drawCircleInUpArrow(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = l1; i < l2; i++) { // 세로 직선
		drawPixel((k1 + k2) / 2, i, red, green, blue);
	}
	// 화살표 끝
	drawLine((k1 + k2) / 2, l2, (k1 + k2) / 2 + (l2 - l1) / 5, l2 - (l2 - l1) / 5, 1.0f, 0.0f, 0.0f);
	drawLine((k1 + k2) / 2 - (l2 - l1) / 5, l2 - (l2 - l1) / 5, (k1 + k2) / 2, l2, 1.0f, 0.0f, 0.0f);
}
void drawCircleInRightArrow(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = k1; i < k2; i++) { // 가로 직선
		drawPixel(i, (l1 + l2) / 2, red, green, blue);
	}
	// 화살표 끝
	drawLine(k2 - (k2 - k1) / 5, (l1 + l2) / 2 + (l2 - l1) / 5, k2, (l1 + l2) / 2, 1.0f, 0.0f, 0.0f);
	drawLine(k2 - (k2 - k1) / 5, (l1 + l2) / 2 - (l2 - l1) / 5, k2, (l1 + l2) / 2, 1.0f, 0.0f, 0.0f);
}
void drawCircleInLeftArrow(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = k1; i < k2; i++) { // 가로 직선
		drawPixel(i, (l1 + l2) / 2, red, green, blue);
	}
	// 화살표 끝
	drawLine(k1, (l1 + l2) / 2, k1 + (k2 - k1) / 5, (l1 + l2) / 2 - (l2 - l1) / 5, 1.0f, 0.0f, 0.0f);
	drawLine(k1, (l1 + l2) / 2, k1 + (k2 - k1) / 5, (l1 + l2) / 2 + (l2 - l1) / 5, 1.0f, 0.0f, 0.0f);
}
void drawCircleInDownLine(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = l1; i < l2; i++) { // 세로 직선
		drawPixel((k1 + k2) / 2, i, red, green, blue);
	}
}
void drawCircleInA(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue, double xpos, double ypos) {
	isCircle(i4, i5, j4, j5, xpos, ypos);

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = k1 + (k2 - k1) / 4; i < k2 - (k2 - k1) / 4; i++) { // 가로 직선
		drawPixel(i, (l1 + l2) / 2, red, green, blue);
	}
	// 화살표 끝
	drawLine((k1 + k2) / 2, l2, k2, l1, 1.0f, 0.0f, 0.0f);
	drawLine(k1, l1, (k1 + k2) / 2, l2, 1.0f, 0.0f, 0.0f);
}


void drawOnPixelBuffer(double xpos, double ypos)
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing

	//위치 변수
	const int i0 = 50, i1 = 200, j0 = 50, j1 = 200;
	const int i2 = 50, i3 = 200, j2 = 300, j3 = 450;

	const int i4 = 250, i5 = 400, j4 = 300, j5 = 450;
	const int i6 = 250, i7 = 400, j6 = 50, j7 = 200;

	const int i8 = 450, i9 = 600, j8 = 50, j9 = 200;
	const int i10 = 450, i11 = 600, j10 = 300, j11 = 450;

	const int i12 = 650, i13 = 800, j12 = 50, j13 = 200;
	const int i14 = 650, i15 = 800, j14 = 300, j15 = 450;

	const int i16 = 850, i17 = 1000, j16 = 50, j17 = 200;
	const int i18 = 850, i19 = 1000, j18 = 300, j19 = 450;

	// 그림 생성
	drawCircleInCircle(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f, xpos, ypos);
	drawCircleInSlash(i2, j2, i3, j3, 1.0f, 0.0f, 0.0f, xpos, ypos);

	drawCircleInRect(i4, j4, i5, j5, 1.0f, 0.0f, 0.0f, xpos, ypos);
	drawCircleInX(i6, j6, i7, j7, 1.0f, 0.0f, 0.0f, xpos, ypos);

	drawCircleInDownArrow(i8, j8, i9, j9, 1.0f, 0.0f, 0.0f, xpos, ypos);
	drawCircleInUpArrow(i10, j10, i11, j11, 1.0f, 0.0f, 0.0f, xpos, ypos);

	drawCircleInRightArrow(i12, j12, i13, j13, 1.0f, 0.0f, 0.0f, xpos, ypos);
	drawCircleInLeftArrow(i14, j14, i15, j15, 1.0f, 0.0f, 0.0f, xpos, ypos);

	drawCircleInDownLine(i16, j16, i17, j17, 1.0f, 0.0f, 0.0f, xpos, ypos);
	drawCircleInA(i18, j18, i19, j19, 1.0f, 0.0f, 0.0f, xpos, ypos);





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

							  //»ï°¢Çü ÁÂÇ¥
	float vertices[] =
	{
		0.0, 0.5, 0.0, //top corner
		-0.5, -0.5, 0.0, //bottom left corner
		0.5, -0.5, 0.0 //bottom right corner
	};


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		double xpos, ypos;
		

		glfwGetCursorPos(window, &xpos, &ypos);

		
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer(xpos, ypos);
		

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
