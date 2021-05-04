#ifndef RAT
#define RAT

#include "maze.h"

class Rat {
private:
	double mX;
	double mY;
	double mMoveSpeed;
	double mDegrees;

public:
	Rat();
	Rat(double x, double y);
	void Draw();
	double GetRadians();
	void MoveForward(Maze &pMaze);
	void RotateLeft();
	void RotateRight();
};

#endif