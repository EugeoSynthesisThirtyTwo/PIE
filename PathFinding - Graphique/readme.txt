Ceci est une version graphique de l'algorithme de path finding A*.
Pour ouvrir le projet, lancez la solution visual studio "PathFinding.sln".
Executez le programme et vous verrez une grille apparaitre.

Modification de la grille :
	- Appuyez sur le bouton gauche de la souris sur une case pour y placer un obstacle.
	- Appuyez sur le bouton droite de la souris sur une case pour y enlever un obstacle.
	- Appuyez sur la touche "&" pour réinitialiser la grille.
	- Appuyez sur la touche "é" pour remplir la grille avec des obstacles.
	- Les obstacles sont représentés par des cases bleus.

Calcul du chemin :
	- Maintenez le clic molette d'une case à une autre pour calculer le chemin le plus
	court entre ces deux cases.
	- Le chemin est automatiquement sauvegardé dans le fichier path.txt

Sauvegarde de la grille :
	- Appuyez sur la touche S du clavier pour sauvegarder votre grille
	dans le fichier "map.bin".
	- Appuyez sur la touche L du clavier pour charger votre grille
	depuis le fichier "map.bin".

Les sources sont dans le dossier PathFinding/src
Les headers sont dans le dossier PathFinding/headers
Si vous voulez savoir comment utiliser une classe, veuillez vous référer
aux commentaires du fichier header associé.

L'algorithme "a star" en lui même correspond aux fichiers:
	- node.h
	- node.cpp
	- grid.h
	- grid.cpp
	- astar.h
	- astar.cpp

Les dépendences de la SDL (.dll, .lib, .h) se trouvent dans le dossier
Dependencies/SDL2.