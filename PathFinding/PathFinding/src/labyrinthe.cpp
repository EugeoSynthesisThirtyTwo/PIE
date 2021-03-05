#include "labyrinthe.h"

Laby::Laby(int w, int h)
	: w(w), h(h), true_w(2 * w + 1), true_h(2 * h + 1)
{
	grid = create2Darray(true_h, true_w);
	bool** passage = create2Darray(h, w);

	for (int y = 0; y < true_h; y++)
		for (int x = 0; x < true_w; x++)
			grid[y][x] = x % 2 && y % 2;

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			passage[y][x] = false;

	int x = std::rand() % w;
	int y = std::rand() % h;

	passage[y][x] = true;

	int* chemin_x = new int[w * h];
	int* chemin_y = new int[w * h];
	int indexPassage = 0;
	chemin_x[indexPassage] = x;
	chemin_y[indexPassage] = y;

	while (indexPassage != -1)
	{
		bool* directions = Laby::getDirections(passage, x, y, w, h);
		int nbDirections = 0;

		for (int i = 0; i < 4; i++)
			if (directions[i])
				nbDirections++;

		if (nbDirections > 0)
		{
			int choix = std::rand() % nbDirections;
			int direction = 0;

			while (choix > 0 || !directions[direction])
			{
				if (directions[direction])
					choix--;

				direction++;
			}

			switch (direction)
			{
				case 0:
					grid[2 * y + 1][2 * x] = true;
					x--;
					break;
				case 1:
					grid[2 * y][2 * x + 1] = true;
					y--;
					break;
				case 2:
					x++;
					grid[2 * y + 1][2 * x] = true;
					break;
				case 3:
					y++;
					grid[2 * y][2 * x + 1] = true;
					break;
			}

			indexPassage++;
			chemin_x[indexPassage] = x;
			chemin_y[indexPassage] = y;
			passage[y][x] = true;
		}
		else
		{
			indexPassage--;

			if (indexPassage != -1)
			{
				x = chemin_x[indexPassage];
				y = chemin_y[indexPassage];
			}
		}

		delete[] directions;
	}

	delete[] chemin_x;
	delete[] chemin_y;
	delete2Darray(passage, h);
}

Laby::~Laby()
{
	delete2Darray(grid, true_h);
}

bool* Laby::getDirections(bool** passages, int x, int y, int w, int h)
{
	bool* directions = new bool[4];

	directions[0] = x > 0 ? !passages[y][x - 1] : false;
	directions[1] = y > 0 ? !passages[y - 1][x] : false;
	directions[2] = x < w - 1 ? !passages[y][x + 1] : false;
	directions[3] = y < h - 1 ? !passages[y + 1][x] : false;

	return directions;
}

bool** Laby::create2Darray(int h, int w)
{
	bool** arr = new bool* [h];

	for (int y = 0; y < h; y++)
		arr[y] = new bool[w];

	return arr;
}

void Laby::delete2Darray(bool** arr, int h)
{
	for (int y = 0; y < h; y++)
		delete[] arr[y];

	delete[] arr;
}

std::string Laby::getCharMur(bool haut, bool bas, bool gauche, bool droite)
{
	if (haut && bas && gauche && droite)
		return "-+-";
	else if (haut && bas && gauche)
		return "-| ";
	else if (haut && bas && droite)
		return " |-";
	else if (haut && gauche && droite)
		return "-|-";
	else if (bas && gauche && droite)
		return "-|-";
	else if (haut && droite)
		return " |-";
	else if (haut && gauche)
		return "-| ";
	else if (droite && bas)
		return " |-";
	else if (gauche && bas)
		return "-| ";
	else if (gauche && droite)
		return "---";
	else if (haut || bas)
		return " | ";
	else if (gauche)
		return "-- ";
	else if (droite)
		return " --";
	else
		return " + ";
}

std::string Laby::toString() const
{
	std::string str("");
	bool haut, bas, gauche, droite;

	for (int y = 0; y < true_h; y++)
	{
		std::string ligne("");

		for (int x = 0; x < true_w; x++)
		{
			if (grid[y][x])
				ligne += "   ";
			else
			{
				haut = y > 0 ? !grid[y - 1][x] : false;
				bas = y < true_h - 1 ? !grid[y + 1][x] : false;
				gauche = x > 0 ? !grid[y][x - 1] : false;
				droite = x < true_w - 1 ? !grid[y][x + 1] : false;
				ligne += getCharMur(haut, bas, gauche, droite);
			}
		}

		str += ligne + "\n";
	}

	return str;
}