// LineDraw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <GL\freeglut.h>
#include <GL\glut.h>
#include <iostream>


using namespace std;
//variabel global
int mode = 0;
int x1 = 0, y_1 = 0, x2 = 0, y2 = 0, r = 0;
//identifier fungsi
void function();
void DDA();
void Bresenham();
void Circle();

void init();
void display();



//  posisi window di layar
int window_x;
int window_y;

//  ukuran window
int window_width = 480;
int window_height = 480;

//  judul window
char *judul_window = "Garis";

void main(int argc, char **argv)
{
	cout << "1.DDA\n2.Bresenham\n3.Lingkaran\nMode : ";
	cin >> mode;
	cout << "\nMasukkan x1 : ";
	cin >> x1;
	cout << "\nMasukkan y_1 : ";
	cin >> y_1;
	if (mode == 3) {
		cout << "\nMasukkan r : ";
		cin >> r;
		if (r<1) {
			cout << "error" << endl;
			cout << "\nMasukkan r : ";
			cin >> r;
		}
	}
	else {
		cout << "\nMasukkan x2 : ";
		cin >> x2;
		cout << "\nMasukkan y2 : ";
		cin >> y2;
	}
	//  inisialisasi GLUT (OpenGL Utility Toolkit)
	glutInit(&argc, argv);
	// set posisi window supaya berada di tengah 
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
	glutInitWindowSize(window_width, window_height); //set ukuran window 
	glutInitWindowPosition(window_x, window_y); //set posisi window

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // set display RGB dan double buffer
	glutCreateWindow(judul_window); //set judul window


	init(); //jalankan fungsi init 
	glutDisplayFunc(display); //  set fungsi display
	glutMainLoop(); // set loop pemrosesan GLUT
}

//fungsi pemilihan algoritma
void function() { 
	switch (mode)
	{
	case 1:		DDA();
		break;
	case 2:		Bresenham();
		break;
	case 3:		Circle();
		break;
	default:	break;
	}
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //set warna background 
	glColor3f(1.0, 1.0, 1.0); //set warna titik
	glPointSize(2.0); //set ukuran titik
	glMatrixMode(GL_PROJECTION); //set mode matriks yang digunakan 
	glLoadIdentity(); // load matriks identitas
	gluOrtho2D(0.0, 960.0, 0.0, 720.0); // set ukuran viewing window
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clear color
	function(); //jalankan fungsi bresenham
	glutSwapBuffers(); //swap buffer 
}

//algoritma DDA
void DDA() {
	int dx, dy, step;
	float x,y,x_inc,y_inc;

	x = (float)x1;
	y = (float)y_1;

	dx = x2 - x1;
	dy = y2 - y_1;
	if (abs(dx) > abs(dy)) {
		step = abs(dx);
	}
	else {
		step = abs(dy);
	}

	x_inc = (float)dx / (float)step;
	y_inc = (float)dy / (float)step;

	//gambar titik awal
	glBegin(GL_POINTS);
	glVertex2i((int)x, (int)y);

	//perulangan untuk menggambar titik-titik 
	while (x != (float)x2 && y!=(float)y2) {
		x += x_inc;
		y += y_inc;
		glVertex2i((int)x, (int)y);
	}

	glEnd();
	glFlush();
}

//Algortima Bresenham
void Bresenham() {
	int dx, dy, x, y, p,d2,dydx2;
	bool m1 = false;

	x = x1;
	y = y_1;

	dx = abs(x2 - x1);
	dy = abs(y2 - y_1);
	if (dx<dy) {
		m1 = true;
		d2 = 2 * dx;
		dydx2 = 2*(dx-dy);
		p = d2 - dy;
	}
	else {
		d2 = 2 * dy;
		dydx2 = 2 * (dy - dx);
		p = d2 - dx;
	}


	//gambar titik awal
	glBegin(GL_POINTS);
	glVertex2i(x, y);

	//perulangan untuk menggambar titik-titik 
	//m1 jika m>=1
	if (m1) {
		while (x != x2 && y != y2) {
			if (y_1 > y2) {
				y--;
			}
			else y++;
			if (p < 0) {
				p += d2;
			}
			else
			{

				if (x1>x2) {
					x--;
				}
				else {
					x++;
				}

				p += dydx2;
			}
			glVertex2i(x, y);
		}
	}
	else {
		while (x != x2 && y != y2) {
			if (x1 > x2) {
				x--;
			}
			else {
				x++;
			}
			if (p < 0) {
				p += d2;
			}
			else
			{
				if (y_1 > y2) {
					y--;
				}
				else y++;

				p += dydx2;
			}
			glVertex2i(x, y);
		}
	}

	glEnd();
	glFlush();
}

//fungsi menggambar refleksi titik di semua oktan
void drawRelfection(int cx, int cy,int x, int y) {

	glVertex2i(cx + x, cx + y);
	glVertex2i(cx + x, cx - y);
	glVertex2i(cx - x, cx + y);
	glVertex2i(cx - x, cx - y);
	glVertex2i(cx + y, cx + x);
	glVertex2i(cx + y, cx - x);
	glVertex2i(cx - y, cx + x);
	glVertex2i(cx - y, cx - x);
}

//algoritma menggambar lingkaran
void Circle() {
	int p, x, y;

	p = 1 - r;
	x = 0;
	y = r;

	glBegin(GL_POINTS);
	drawRelfection(x1,y_1,x,y);

	while (x <= y) {
		x++;
		if (p < 0) {
			p += 2 * x + 1;
		}
		else
		{
			y--;
			p += 2*(x-y)+1;
		}
		drawRelfection(x1, y_1, x, y);
	}

	glEnd();
	glFlush();
}