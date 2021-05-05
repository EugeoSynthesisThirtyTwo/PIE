#pragma once

#include <vector>

#include "grid.h"
#include "node.h"

/*
	Algorithme A* pour trouver le chemin le plus
	court sur une grille. Les déplacements diagonaux
	sont autorisés.
*/
class AStar
{
private:
	static constexpr float SQRT_2 = 1.41421356237f;

public:
	Grid& grid;
	
private:
	int widthNodes, heightNodes;
	Node** nodes;
	std::vector<Node*> priority;

public:
	std::vector<Node*> explored;

public:
	/* grid : la grille sur laquelle vous voulez calculer le chemin */
	AStar(Grid& grid);
	
	~AStar();

	/*
		cherche le chemin le plus court
		pour aller du point (xstart, ystart)
		jusqu'au point (xend, yend)

		Renvoie un tableau de coordonnées (x, y) correspondant
		au chemin calculé.
	*/
	std::vector<std::pair<int, int>> findPath(int xstart, int ystart, int xend, int yend);

private:
	void resetNodes();

	void deleteNodes();
};