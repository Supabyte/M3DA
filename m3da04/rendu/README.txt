*********************************************
M3DA - TP B-splines/NURBS
Bruno Ordozgoiti
*********************************************

======= Remarques =======
Les fonctions de tracé ont été mis en GLView. L'interaction avec le vecteur nodal n'est pas toujours mis en oeuvre.

La classe MainWindow a été modifiée afin d'ajouter des nouveaux boutons.

A cause de la mise en oeuvre de les fonctions d'interaction et de tracé, il y a de fonctions qui ne respecte pas l'en-tête proposée dans l'ennoncé (plusieurs fonctions ont comme parametre on objet Nurbs, et le degré fait partie de la clase GLView). 

======= Interactions ======= 
-L'utilisateur peut déplacer les points de contrôle en faisant "click & drag". 
-L'utilisateur peut modifier le poids de chaque point en le selectionnant (click gauche sur le point), puis saisant la nouvelle valeur dans la case correspondant et en cliquant sur "Set weight".
-L'utilisateur peut modifier le degré de la courbe en saisant la nouvelle valeur dans la case correspondant et en cliquant sur "Set degree" (pas possible pour le courbes dont le vecteur nodal est fixé).

======= Difficultés ======= 
-La definition des courbes est un peu dense, et sa assimilation exige du temps.

======= E1Q5 ======= 
Les valeurs de k qui influenceront la courbe seront ceux dont la fonction recursive vaut 1 pour au moins un des termes de la somme de la formule de Cox de Boor. Le plus grande la valeur de p, le plus grande l'intervale du vecteur nodal qui peut verifier la condition qui fourni la valeur 1 au cas d'arret.

Ça veut dire que, au moins pour ce vecteur nodal, si t est dans l'interval [t_i, t_i+1[, les points qu'influenceront la courbe en t seront les points de contrôle P_k tels que k <= i et k + p >= i.

Soit t = 3.5 et le vecteur nodal = [1,2,3,4,5,6,7], alors
pour p=1 la courbe sera influencée par P_1 et P_2 
	(t est dans [t_2, t_3[, 
		1 <= 2, 1+1 >= 2,
		2 <= 2, 2+1 >= 2)

pour p=2 la courbe sera influencée par P_0, P_1 et P_2 
	(t est dans [t_2, t_3[, 
		0 <= 2, 0+2 >= 2, 
		1 <= 2, 1+2 >= 2, 
		2 <= 2, 2+2 >= 2)

pour p=3 la courbe sera influencée par P_0, P_1 et P_2 
	(t est dans [t_2, t_3[, 
		0 <= 2, 0+3>= 2, 
		1 <= 2, 1+3 >= 2, 
		2 <= 2, 2+3 >= 2)


======= E1Q13 ======= 
La courbe doit avoir degré 3 et avoir comme vecteur nodal, par exemple, [0,0,0,0,0,1,1,1,1].
