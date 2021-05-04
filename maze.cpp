#include <vector>
#include <cstdlib>
#include "glut.h"
#include "graphics.h"
#include "maze.h"

Cell::Cell()
{
	left = top = right = bottom = true;
	visited = false;
}
void Cell::Draw(int x, int y)
{
	glColor3d(0, 0, 0);
	if (left)
		DrawLine(x, y, x, y + 1);
	if (top)
		DrawLine(x, y + 1, x + 1, y + 1);
	if (right)
		DrawLine(x + 1, y + 1, x + 1, y);
	if (bottom)
		DrawLine(x + 1, y, x, y);
}



Maze::Maze()
{

}

// begins the recursive version of RemoveWalls, as well as creates a start and end point at the top and bottom of the maze
void Maze::RemoveWalls()
{
	int i = rand() % WIDTH; // srand(time(NULL)) had an error?
	RemoveWallsR(i, 0);

	// Remove wall at top and bottom (for entrance & exit)
	i = rand() % WIDTH;
	cells[i][0].bottom = false;
	mBottomCell = i;
	i = rand() % WIDTH;
	cells[i][HEIGHT - 1].top = false;
}

void Maze::RemoveWallsR(int i, int j)
{
	cells[i][j].visited = true;

	while (true)
	{
		// record legal possibilitites between LEFT, UP, RIGHT, DOWN
		enum MOVES { LEFT, UP, RIGHT, DOWN };
		std::vector<MOVES> moves;

		// check for a legal LEFT move
		if (i - 1 >= 0 && !cells[i - 1][j].visited)
		{
			moves.push_back(LEFT);
		}
		// check for legal RIGHT move
		if (i + 1 < WIDTH && !cells[i+1][j].visited) {
			moves.push_back(RIGHT);
		}
		// check for legal DOWN move
		if (j - 1 >= 0 && !cells[i][j - 1].visited) {
			moves.push_back(DOWN);
		}
		// check for legal UP move
		if (j + 1 < HEIGHT && !cells[i][j + 1].visited) {
			moves.push_back(UP);
		}


		if (moves.size() == 0)
		{
			return;
		}

		// pick which direction randomly, then recursive call.
		int r = rand() % moves.size();

		if (moves[r] == LEFT)
		{
			cells[i][j].left = false;
			cells[i - 1][j].right = false;
			RemoveWallsR(i - 1, j);
		}
		if (moves[r] == RIGHT) {
			cells[i][j].right = false;
			cells[i + 1][j].left = false;
			RemoveWallsR(i + 1, j);
		}
		if (moves[r] == DOWN) {
			cells[i][j].bottom = false;
			cells[i][j - 1].top = false;
			RemoveWallsR(i, j - 1);
		}
		if (moves[r] == UP) {
			cells[i][j].top = false;
			cells[i][j + 1].bottom = false;
			RemoveWallsR(i, j + 1);
		}

	}

}
void Maze::Draw()
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			cells[i][j].Draw(i, j);
}

// returns true if a circle at 'x, y' and radius 'r' isn't passing through a wall
bool Maze::IsSafe(double x, double y, double r) {
	int i = int(x); // cells are 1x1, this is used to create the offset from the 0,0 coord relative to the cell
	int j = int(y);

	double xOffset = x - i;
	double yOffset = y - j;

	// all corners count as walls
	if (xOffset + r > 1 && yOffset + r > 1)
		return false;
	if (xOffset - r < 0 && yOffset + r > 1)
		return false;
	if (xOffset + r > 1 && yOffset - r < 0)
		return false;
	if (xOffset - r < 0 && yOffset - r < 0)
		return false;

	// checking vs each wall of the cell (if it exists)
	if (cells[i][j].right && xOffset + r > 1)
		return false;
	if (cells[i][j].bottom && yOffset - r < 0)
		return false;
	if (cells[i][j].left && xOffset - r < 0)
		return false;
	if (cells[i][j].top && yOffset + r > 1)
		return false;

	// after all other tests, return true
	return true;
}
