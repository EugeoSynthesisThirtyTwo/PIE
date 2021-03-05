#pragma once

struct Ressources
{
private:
	static bool initialized;
	static const char* error;

public:
	/* TODO declarer les ressources ici */

public:
	Ressources() = delete;

	/*
	  charge le contenu du dossier ressources
	  renvoie 0 si il n'y a eu aucune erreur
	*/
	static int init();

	/*
	  decharge les ressources
	*/
	static void quit();

	/*
	  renvoie les details de la derniere erreur
	*/
	static const char* GetError();
};