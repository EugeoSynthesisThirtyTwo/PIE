#pragma once

#include <string>

#include "better_vector.h"

/*
	Une grille 2D de booléen.
	true correspond à un obstacle,
	false correspond à une case accessible.
*/
class Grid
{
private:
	uint32_t width, height;
	char* grid;
	int size;

public:
	/*
		Créé une grille de taille width * height.
		Toutes les cases sont initialisées à false.
	*/
	Grid(int width, int height);

	Grid(const Grid& other);

	Grid(Grid&& other) noexcept;

	void operator=(const Grid& other);

	void operator=(Grid&& other) noexcept;

	/*
		Serialise la grille dans un buffer.
	*/
	void serialize(BetterVector<char>& buffer) const;

	/*
		Créé la grille à partir d'un buffer (buffer),
		et d'une certaine position dans le buffer (cursor).
	*/
	Grid(const char* buffer, int& cursor);

	~Grid();

	/*
		Récupère la valeur de la grille à la
		position (x, y).
	*/
	bool at(int x, int y) const;

	/*
		Modifie la valeur de la grille à la
		position (x, y);
	*/
	void set(int x, int y, bool value);

	/*
		Vérifie si (x, y) est une position valide.
	*/
	bool isInside(int x, int y) const;

	/*
		Remplie toute la grille avec une valeur (value).
	*/
	void clear(bool value);

	/*
		Renvoie une grille chargée depuis un fichier.
		Si le fichier n'a pas pu être ouvert, le programme
		s'arrête.
	*/
	static Grid load(std::string file);

	/*
		Sauvegarde la grille dans un fichier.
	*/
	void save(std::string file) const;

	/*
		Renvoie width.
	*/
	int getWidth() const;

	/*
		Renvoie height.
	*/
	int getHeight() const;
};