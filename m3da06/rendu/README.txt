J'ai essayé de mettre en place une architecture flexible. La classe Implicit représent des surfaces implicites. La classe ImplicitObject sert à représenter des objets comme des blobs ou soft objects. 

Pour ajouter une nouvelle type de surface au logiciel il suffit de créer une classe qui hérite d'Implicit et rédefinir la fonction eval(). 

Pour ajouter des objects comme les blobs il suffit de faire une classe qui hérite d'ImplicitObject. Après, on doit ajouter ces objets a l'objet du type Implicit qu'on utilise. 

Ce que l'utilisateur peut faire:

-Dans la fenêtre il y à 3 boutons, qui nous permettent de tracer un cercle, des blobs ou des soft objects déjà définis.

-Il peut aussi appuyer sur différentes touches:
-F: Afficher la surface complet.
-V: Afficher les valeurs de la fonction dans chaque point de la grille.
-P: Afficher les points de la surface evalués.
-+/-: Augmenter/diminuer la resolution de la grille.

Problèmes:
-Les soft objects ne semblent se représenter correctement.

