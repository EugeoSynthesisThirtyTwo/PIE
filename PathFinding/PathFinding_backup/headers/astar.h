#pragma once

#include <vector>
#include <algorithm>
#include "grid.h"
#include "node.h"

class AStar
{
private:
	static constexpr float SQRT_2 = 1.41421356237f;

public:
	Grid& grid;
	
private:
	Node** nodes;
	std::vector<Node*> priority;

public:
	std::vector<Node*> explored;

public: AStar(Grid& grid);

public: ~AStar();

public: std::vector<std::pair<int, int>> findPath(int xstart, int ystart, int xend, int yend);

public: void resetNodes();
};