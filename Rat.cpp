#include "Rat.h"
#include "graphics.h"
#include <cstdlib>
#include "glut.h"
#include <cmath>

Rat::Rat() {
	mMoveSpeed = .005;
	mDegrees = 90;
	mX = 2.5;
	mY = 2;
}

Rat::Rat(double x, double y) {
	mMoveSpeed = 0.005;
	mDegrees = 90;
	mX = x;
	mY = y;
}


double Rat::GetRadians() {
	double radians = mDegrees * 3.1415926 / 180.0;
	return radians;
}

void Rat::MoveForward(Maze& pMaze) {
	double radians = GetRadians();
	double dx = std::cos(radians);
	double dy = std::sin(radians);

	if (pMaze.IsSafe(mX + dx * mMoveSpeed, mY + dy * mMoveSpeed, .25)) {
		mX += dx * mMoveSpeed;
		mY += dy * mMoveSpeed;
	}
}

void Rat::Draw() {
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated(mDegrees, 0, 0, 1);
	glScaled(.5, .5, 1.0);
	DrawTriangle(.5, 0, -.3, .2, -.3, -.2);
	glPopMatrix();
}

void Rat::RotateLeft() {
	mDegrees += .5;
}

void Rat::RotateRight() {
	mDegrees -= .5;
}
