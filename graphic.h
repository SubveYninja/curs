#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <Windows.h>

struct vector3d {

	double x;
	double y;
	double z;
	double w;

};

class graphic
{
private:
	float steps = 80;

	int z_range[2] = { 40, 580 };
	int a_range[2] = { 10, 90 };

	double f[2] = { -M_PI, M_PI };

	double lemni_x(double kf, double f);
	double lemni_y(double kf, double f);
	double lemni_t(double kf, double f);

public:

	std::vector<vector3d> picture;
	std::vector<vector3d> pictureP;

	void DrawGraph(HDC hdc, HPEN hPen);

	void MultiplyP(double* atm);
	void Multiply(double* atm);

	void GetGraph(vector3d center);
	void GetAxis(vector3d center);

	void xMove(float dx, double* atm);
	void yMove(float dy, double* atm);
	void zMove(float dz, double* atm);

	void Scaling(double h, double* atm);

	void RotateX(float angle, double* atm);
	void RotateY(float angle, double* atm);
	void RotateZ(float angle, double* atm);


	void GetPerspicere(double* atm);

};

