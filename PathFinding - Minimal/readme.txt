Ceci est une version graphique de l'algorithme de path finding A*.
Pour ouvrir le projet, lancez la solution visual studio "PathFinding.sln".
Compilez le projet.
Supposons que l'executable s'appelle "PathFinding.exe".

Pour calculer le chemin le plus court d'un point
(x_start, y_start) à un point (x_end, y_end) sur une certaine grille,
executez la commande suivante:

./PathFinding map.bin x_start y_start x_end y_end path.txt

"map.bin" est le fichier dans lequelle est sauvegardée la grille.
"path.txt" est le fichier de sortie dans lequel le chemin est écrit.

Le chemin est écrit sous la forme d'une suite de chiffres
aux 8 directions suivantes:

7  0  1
6  x  2
5  4  3

Pour créer la grille et la sauvegarder dans le fichier map.bin,
vous pouvez par exemple utiliser le projet "PathFinding - Graphique".
Ou alors vous pouvez créer un nouvel objet Grid de la taille désirée,
pour modifier les cases une par une en appellant la méthode "set",
puis sauvegarder la grille avec la méthode "save".

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