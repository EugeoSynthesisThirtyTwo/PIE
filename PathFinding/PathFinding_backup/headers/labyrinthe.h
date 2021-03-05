#pragma once

#include <iostream>
#include <string>

class Laby
{
public:
	const int w, h;
	const int true_w, true_h;
	bool** grid = nullptr;

public:
	Laby(int w, int h);

	~Laby();

private:
	static bool* getDirections(bool** passages, int x, int y, int w, int h);

	static bool** create2Darray(int h, int w);

	static void delete2Darray(bool** arr, int h);

	static std::string getCharMur(bool haut, bool bas, bool gauche, bool droite);

public:
	std::string toString() const;
};