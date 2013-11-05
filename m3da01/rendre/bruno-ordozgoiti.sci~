// -----------------------------------------------------------------------
/// \brief Calcule un terme de contrainte a partir d'une homographie.
/// \param H: matrice 3*3 définissant l'homographie.
///
/// \param i: premiere colonne.
/// \param j: deuxieme colonne.
/// \return vecteur definissant le terme de contrainte.
// -----------------------------------------------------------------------
function v = ZhangConstraintTerm(H, i, j)
  //Il faut transposer la matrice H pour utiliser la notation de Zhang
  H = H';
  v = [H(i,1)*H(j,1), H(i,1)*H(j,2)+H(i,2)*H(j,1),H(i,2)*H(j,2),H(i,3)*H(j,1)+H(i,1)*H(j,3),H(i,3)*H(j,2)+H(i,2)*H(j,3),	H(i,3)*H(j,3)];
endfunction

// -----------------------------------------------------------------------
/// \brief Calcule deux equations de contrainte a partir d'une homographie
///
/// \param H: matrice 3*3 définissant l'homographie.
/// \return matrice 2*6 definissant les deux contraintes.
// -----------------------------------------------------------------------
function v = ZhangConstraints(H)
  v = [ZhangConstraintTerm(H, 1, 2); ...
    ZhangConstraintTerm(H, 1, 1) - ZhangConstraintTerm(H, 2, 2)];
endfunction

// -----------------------------------------------------------------------
/// \brief Calcule la matrice des parametres intrinseques.
///
/// \param b: vecteur resultant de l'optimisation de Zhang.
/// \return matrice 3*3 des parametres intrinseques.
// -----------------------------------------------------------------------
function A = IntrinsicMatrix(b)
  //b: 11=1, 12=2, 22=3, 13=4, 23=5, 33=6
  v0 = (b(2)*b(4) - b(1)*b(5)) / (b(1)*b(3) - b(2)*b(2)) ;
  lambda = b(6) - ( b(4)*b(4) + v0* (b(2)*b(4) - b(1)*b(5) )) / b(1);
  alpha= sqrt(lambda/ b(1));
  beta = sqrt( lambda*b(1) / (b(1)*b(3)-b(2)*b(2)) );
  gamma = -b(2)*alpha*alpha*beta/lambda;
  u0 = gamma * v0/beta - b(4)*alpha*alpha/lambda;

  A = [	alpha, 	gamma, 	u0;
	0, 	beta, 	v0;
	0, 	0, 	1];

endfunction

// -----------------------------------------------------------------------
/// \brief Calcule la matrice des parametres extrinseques.
///
/// \param iA: inverse de la matrice intrinseque.
/// \param H: matrice 3*3 definissant l'homographie.
/// \return matrice 3*4 des parametres extrinseques.
// -----------------------------------------------------------------------
function E = ExtrinsicMatrix(iA, H)
  h1 = H(:,1);
  h2 = H(:,2);
  h3 = H(:,3);
  vAux = iA*h1;
  lambda = 1/sqrt(vAux'*vAux);
  r1 = lambda*iA*h1;
  r2 = lambda*iA*h2;
  r3 = produitvectoriel(r1,r2);
  t = lambda*iA*h3;
  E = [r1,r2,r3,t];

endfunction


function [v]=produitvectoriel(v1,v2)
v(1) = v1(2)*v2(3) - v1(3)*v2(2)
v(2) = v1(3)*v2(1) - v1(1)*v2(3)
v(3) = v1(1)*v2(2) - v1(2)*v2(1)
endfunction
