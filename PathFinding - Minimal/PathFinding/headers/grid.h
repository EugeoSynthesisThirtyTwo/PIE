#pragma once

#include <string>

#include "better_vector.h"

/*
	Une grille 2D de bool�en.
	true correspond � un obstacle,
	false correspond � une case accessible.
*/
class Grid
{
private:
	uint32_t width, height;
	char* grid;
	int size;

public:
	/*
		Cr�� une grille de taille width * height.
		Toutes les cases sont initialis�es � false.
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
		Cr�� la grille � partir d'un buffer (buffer),
		et d'une certaine position dans le buffer (cursor).
	*/
	Grid(const char* buffer, int& cursor);

	~Grid();

	/*
		R�cup�re la valeur de la grille � la
		position (x, y).
	*/
	bool at(int x, int y) const;

	/*
		Modifie la valeur de la grille � la
		position (x, y);
	*/
	void set(int x, int y, bool value);

	/*
		V�rifie si (x, y) est une position valide.
	*/
	bool isInside(int x, int y) const;

	/*
		Remplie toute la grille avec une valeur (value).
	*/
	void clear(bool value);

	/*
		Renvoie une grille charg�e depuis un fichier.
		Si le fichier n'a pas pu �tre ouvert, le programme
		s'arr�te.
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