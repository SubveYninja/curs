#include "graphic.h"



double graphic::lemni_x(double kf, double f) {

	return lemni_t(kf, f) * cos(f);

}

double graphic::lemni_y(double kf, double f) {

	return lemni_t(kf, f) * sin(f);

}

double graphic::lemni_t(double kf, double f) {

	return kf * sqrt(2 * cos(2 * f));

}


void graphic::GetGraph(vector3d center) {

	double h = 80;
	double kf;

	for (int i = this->z_range[0]; i < this->z_range[1]; i += 60) {

		kf = tan((this->a_range[0] + ((static_cast<double>(i) - this->z_range[0]) * (this->a_range[1] - this->a_range[0]) / (this->z_range[1] - this->z_range[0]))) * M_PI / 180);

		for (double j = this->f[0]; j < this->f[1]; j += (this->f[1] - this->f[0]) / steps) {
			vector3d pic;
			pic.z = center.z + i;
			pic.w = 1;

			pic.x = center.x + lemni_x(kf, j) * h;
			pic.y = center.y + lemni_y(kf, j) * h;

			this->picture.push_back(pic);
		}
	}
}


void graphic::xMove(float dx, double* atm) {

	atm[12] = dx;
	Multiply(atm);

}

void graphic::yMove(float dy, double* atm) {

	atm[13] = dy;
	Multiply(atm);

}

void graphic::zMove(float dz, double* atm) {

	atm[14] = dz;
	Multiply(atm);

}

void graphic::Scaling(double h, double* atm) {


	atm[15] = 1 / h;
	Multiply(atm);

}



void graphic::DrawGraph(HDC hdc, HPEN hPen) {


	MoveToEx(hdc, static_cast<int>(pictureP.front().x), static_cast<int>(pictureP.front().y), NULL);

	int p = 0;

	for (int i = this->z_range[0]; i < this->z_range[1]; i += 60) {

		hPen = CreatePen(PS_SOLID, 0.5, RGB(255.0 - (255.0 / 540.0 * i), 255.0 - (255.0 / 540.0 * i), 255));
		SelectObject(hdc, hPen);

		MoveToEx(hdc, static_cast<int>(this->pictureP.at(p).x), static_cast<int>(this->pictureP.at(p).y), NULL);

		for (double j = this->f[0]; j < this->f[1]; j += (this->f[1] - this->f[0]) / steps) {
			LineTo(hdc, static_cast<int>(this->pictureP.at(p).x), static_cast<int>(this->pictureP.at(p).y));
			p++;

			if (pictureP.size() > p + steps) {
				MoveToEx(hdc, static_cast<int>(this->pictureP.at(p - 1).x), static_cast<int>(this->pictureP.at(p - 1).y), NULL);
				LineTo(hdc, static_cast<int>(this->pictureP.at(p + steps - 1).x), static_cast<int>(this->pictureP.at(p + steps - 1).y));
				MoveToEx(hdc, static_cast<int>(this->pictureP.at(p - 1).x), static_cast<int>(this->pictureP.at(p - 1).y), NULL);
			}

		}
		LineTo(hdc, static_cast<int>(this->pictureP.at(p - steps).x), static_cast<int>(this->pictureP.at(p - steps).y));

	}

	MoveToEx(hdc, static_cast<int>(this->pictureP.at(p - 1).x), static_cast<int>(this->pictureP.at(p - 1).y), NULL);
	LineTo(hdc, static_cast<int>(this->pictureP.at(p - steps + 1).x), static_cast<int>(this->pictureP.at(p - steps + 1).y));


}

void graphic::MultiplyP(double* atm) {

	pictureP.clear();

	int it = 0;

	for (auto& a : this->picture) {

		vector3d newPnt = { 0, 0, 0, 0 };

		newPnt.x += a.x * atm[0];
		newPnt.x += a.y * atm[4];
		newPnt.x += a.z * atm[8];
		newPnt.x += a.w * atm[12];

		newPnt.y += a.x * atm[1];
		newPnt.y += a.y * atm[5];
		newPnt.y += a.z * atm[9];
		newPnt.y += a.w * atm[13];

		newPnt.z += a.x * atm[2];
		newPnt.z += a.y * atm[6];
		newPnt.z += a.z * atm[10];
		newPnt.z += a.w * atm[14];

		newPnt.w += a.x * atm[3];
		newPnt.w += a.y * atm[7];
		newPnt.w += a.z * atm[11];
		newPnt.w += a.w * atm[15];


		this->pictureP.push_back(newPnt);

		this->pictureP.back().x /= this->pictureP.back().w;
		this->pictureP.back().y /= this->pictureP.back().w;
		this->pictureP.back().z /= this->pictureP.back().w;
		this->pictureP.back().w /= this->pictureP.back().w;

	}

}

void graphic::Multiply(double* atm) {

	for (auto& a : this->picture) {

		vector3d newPnt = { 0, 0, 0, 0 };

		newPnt.x += a.x * atm[0];
		newPnt.x += a.y * atm[4];
		newPnt.x += a.z * atm[8];
		newPnt.x += a.w * atm[12];

		newPnt.y += a.x * atm[1];
		newPnt.y += a.y * atm[5];
		newPnt.y += a.z * atm[9];
		newPnt.y += a.w * atm[13];

		newPnt.z += a.x * atm[2];
		newPnt.z += a.y * atm[6];
		newPnt.z += a.z * atm[10];
		newPnt.z += a.w * atm[14];

		newPnt.w += a.x * atm[3];
		newPnt.w += a.y * atm[7];
		newPnt.w += a.z * atm[11];
		newPnt.w += a.w * atm[15];

		a = newPnt;

		a.x /= a.w;
		a.y /= a.w;
		a.z /= a.w;
		a.w /= a.w;

	}

}

void graphic::GetPerspicere(double* atm) {

	atm[11] = 0;
	atm[12] = sin(20.705 * M_PI / 180);
	atm[13] = -cos(20.705 * M_PI / 180) * sin(22.208 * M_PI / 180);
	atm[14] = cos(20.705 * M_PI / 180) * cos(22.208 * M_PI / 180);
	MultiplyP(atm);
}

void graphic::RotateX(float angle, double* atm) {
	atm[5] = cos(angle * M_PI / 180);
	atm[6] = sin(angle * M_PI / 180);
	atm[9] = -sin(angle * M_PI / 180);
	atm[10] = cos(angle * M_PI / 180);
	Multiply(atm);
}

void graphic::RotateY(float angle, double* atm) {


	atm[0] = cos(angle * M_PI / 180);
	atm[2] = -sin(angle * M_PI / 180);
	atm[8] = sin(angle * M_PI / 180);
	atm[10] = cos(angle * M_PI / 180);
	Multiply(atm);
}

void graphic::RotateZ(float angle, double* atm) {
	atm[0] = cos(angle * M_PI / 180);
	atm[1] = sin(angle * M_PI / 180);
	atm[4] = -sin(angle * M_PI / 180);
	atm[5] = cos(angle * M_PI / 180);
	Multiply(atm);
}

