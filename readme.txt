Le dossier PathFinding est une implémentation graphique le l'algorihme "a star".

La solution visual studio se trouve dans le dossier PathFinding.

Le fichiers sources se trouvent dans le dossier PathFinding/PathFinding/src
et PathFinding/PathFinding/headers.

L'algorithme "a star" en lui même correspond aux fichiers:
	- node.h
	- node.cpp
	- grid.h
	- grid.cpp
	- astar.h
	- astar.cpp

Les dépendences de la SDL (.dll, .lib, .h) se trouvent dans le dossier
PathFinding/Dependencies/SDL2.

Lors de la distribution du programme, les fichiers .dll doivent être
dans le même dossier que l'exécutable.

----------------------------------- Controles ----------------------------------------

Une fois le programme lancé, vous avez accès aux commandes suivantes:
	- appuyez sur '1' pour effacer la grille
	- appuyez sur '2' pour remplir la grille
	- appuyez sur 'S' pour sauvegarder la grille dans le fichier 'map.bin'
	- appuyez sur 'L' pour charger la grille depuis le fichier 'map.bin'
	- faites un clic gauche sur une case pour la remplir
	- faites un clic droit sur une case pour la vider
	- maintenez le clic molette pour choisir la case de départ et d'arrivée