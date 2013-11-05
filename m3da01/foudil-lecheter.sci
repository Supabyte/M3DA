// -----------------------------------------------------------------------
/// \brief Calcule un terme de contrainte a partir d'une HomograpHie.
///
/// \param H: matrice 3*3 définissant l'HomograpHie.
/// \param i: premiere colonne.
/// \param j: deuxieme colonne.
/// \return vecteur definissant le terme de contrainte.
// -----------------------------------------------------------------------
function v = ZhangConstraintTerm(H, i, j)
//
H = H';
   v = [H(i,1)*H(j,1), H(i,1)*H(j,2)+ H(i,2)*H(j,1), H(i,2)*H(j,2),H(i,3)*H(j,1)+H(i,1)*H(j,3), H(i,3)*H(j,2)+ H(i,2)*H(j,3), H(i,3)*H(j,3)];
 

//
 
endfunction

// -----------------------------------------------------------------------
/// \brief Calcule deux equations de contrainte a partir d'une HomograpHie
///
/// \param H: matrice 3*3 définissant l'HomograpHie.
/// \return matrice 2*6 definissant les deux contraintes.
// -----------------------------------------------------------------------
function v = ZhangConstraints(H)
  v = [ZhangConstraintTerm(H, 1, 2); ...
    ZhangConstraintTerm(H, 1, 1) - ZhangConstraintTerm(H, 2, 2)];
endfunction

// -----------------------------------------------------------------------
/// \brief Calcule la matrice des parametres intrinseques.
///
/// \param b: vecteur resultant de l'optimisation de ZHang.
/// \return matrice 3*3 des parametres intrinseques.
// -----------------------------------------------------------------------
function A = IntrinsicMatrix(b)
//
  v0 = (b(2)*b(4) - b(1)*b(5))/(b(1)*b(3)-b(2)^2); 
  lambda = b(6)-((b(4)^2+v0*(b(2)*b(4)-b(1)*b(5)))/b(1)) ;
  alph =sqrt(lambda/b(1));
  bet = sqrt((lambda*b(1))/(b(1)*b(3)-b(2)^2)); 
 // bet=sqrt(lambda/b(1));
  gam =-(b(2)*alph^2*bet)/lambda;
  u0 =(gam*v0/bet)-(b(4)*alph^2/lambda); 
  
 
 // Intrinsic Matrix 
  A=[alph,gam,u0; 0,bet,v0; 0,0,1];
  
  
  
endfunction

// -----------------------------------------------------------------------
/// \brief Calcule la matrice des parametres extrinseques.
///
/// \param iA: inverse de la matrice intrinseque.
/// \param H: matrice 3*3 definissant l'HomograpHie.
/// \return matrice 3*4 des parametres extrinseques.
// -----------------------------------------------------------------------
function E = ExtrinsicMatrix(iA, H)
  // A modifier!
  
  lambda=1/norm(inv(A)*H(:,1));
disp(lambda);
  r1=lambda*inv(A)*H(:,1);
  r2=lambda*inv(A)*H(:,2);
  r3=produitvectoriel(r1,r2);
  t=lambda*inv(A)*H(:,3);
  E=[r1 r2 r3 t];
 // E = rand(3, 4);
endfunction

function [v]=produitvectoriel(v1,v2)
v(1) = v1(2)*v2(3) - v1(3)*v2(2)
v(2) = v1(3)*v2(1) - v1(1)*v2(3)
v(3) = v1(1)*v2(2) - v1(2)*v2(1)
endfunction

