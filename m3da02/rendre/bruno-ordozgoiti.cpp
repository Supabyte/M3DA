/* --------------------------------------------------------------------------
Mise en correspondance de points d'interet detectes dans deux images
Copyright (C) 2010, 2011  Universite Lille 1

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Inclure les fichiers d'entete
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#include "glue.hpp"
#include "prenom-nom.hpp"
#include <iostream>
using namespace std;
// -----------------------------------------------------------------------
/// \brief Detecte les coins.
///
/// @param mImage: pointeur vers la structure image openCV
/// @param iMaxCorners: nombre maximum de coins detectes
/// @return matrice des coins
// -----------------------------------------------------------------------
Mat iviDetectCorners(const Mat& mImage,
                     int iMaxCorners) {
//    double tx = mImage.cols, ty = mImage.rows;
    Mat mCorners;
    goodFeaturesToTrack(mImage, mCorners, iMaxCorners, 0.01, 0);
    Mat newCorners = mCorners.t();
    newCorners.resize(3);
    newCorners.at<double>(2,1) = 0;

    Mat nCorners = Mat::eye(3, mCorners.rows, CV_64F);
    for(int i = 0; i < mCorners.rows; i++) {
        Point2f p = mCorners.at<Point2f>(i);
        nCorners.at<double>(0, i) = p.x;
        nCorners.at<double>(1, i) = p.y;
        nCorners.at<double>(2, i) = 1;
    }

    // Retour de la matrice
    return nCorners;
}

// -----------------------------------------------------------------------
/// \brief Initialise une matrice de produit vectoriel.
///
/// @param v: vecteur colonne (3 coordonnees)
/// @return matrice de produit vectoriel
// -----------------------------------------------------------------------
Mat iviVectorProductMatrix(const Mat& v) {
    // A modifier !
    Mat mVectorProduct = Mat::eye(3, 3, CV_64F);

    mVectorProduct.at<double>(0,0) = 0;
    mVectorProduct.at<double>(0,1) = -v.at<double>(2);
    mVectorProduct.at<double>(0,2) = v.at<double>(1);

    mVectorProduct.at<double>(1,0) = v.at<double>(2);
    mVectorProduct.at<double>(1,1) = 0;
    mVectorProduct.at<double>(1,2) = -v.at<double>(0);

    mVectorProduct.at<double>(2,0) = -v.at<double>(1);
    mVectorProduct.at<double>(2,1) = v.at<double>(0);
    mVectorProduct.at<double>(2,2) = 0;

    // Retour de la matrice
    return mVectorProduct;
}

// -----------------------------------------------------------------------
/// \brief Initialise et calcule la matrice fondamentale.
///
/// @param mLeftIntrinsic: matrice intrinseque de la camera gauche
/// @param mLeftExtrinsic: matrice extrinseque de la camera gauche
/// @param mRightIntrinsic: matrice intrinseque de la camera droite
/// @param mRightExtrinsic: matrice extrinseque de la camera droite
/// @return matrice fondamentale
// -----------------------------------------------------------------------
Mat iviFundamentalMatrix(const Mat& mLeftIntrinsic,
                         const Mat& mLeftExtrinsic,
                         const Mat& mRightIntrinsic,
                         const Mat& mRightExtrinsic) {
    Mat mFundamental = Mat::eye(3, 3, CV_64F);
    Mat mHomography = Mat::eye(3, 3, CV_64F);
    Mat mOrigin1 = Mat::eye(4, 1, CV_64F);
    Mat mLeftExtInv = Mat::eye(4, 4, CV_64F);

    Mat p1 = mLeftIntrinsic*mLeftExtrinsic.rowRange(0,3);
    Mat p2 = mRightIntrinsic*mRightExtrinsic.rowRange(0,3);

    cout << "mRightIn" << endl;
    cout << mRightIntrinsic << endl;
    cout << "mRightEx" << endl;
    cout << mRightExtrinsic << endl;
    cout << "0,3" << endl;
    cout << mRightExtrinsic.rowRange(0,3) << endl;

    mHomography = p2*(p1.inv(DECOMP_SVD));
    mLeftExtInv = mLeftExtrinsic.inv();
    mOrigin1 = mLeftExtInv.colRange(3,4);


    mFundamental = iviVectorProductMatrix(p2*mOrigin1)*mHomography;

    // Retour de la matrice fondamentale
    return mFundamental;
}

// -----------------------------------------------------------------------
/// \brief Initialise et calcule la matrice des distances entres les
/// points de paires candidates a la correspondance.
///
/// @param mLeftCorners: liste des points 2D image gauche
/// @param mRightCorners: liste des points 2D image droite
/// @param mFundamental: matrice fondamentale
/// @return matrice des distances entre points des paires
// -----------------------------------------------------------------------
Mat iviDistancesMatrix(const Mat& m2DLeftCorners,
                       const Mat& m2DRightCorners,
                       const Mat& mFundamental) {

    Mat epiLinesPi1 = mFundamental.t()*m2DRightCorners;
    Mat epiLinesPi2 = mFundamental*m2DLeftCorners;
    Mat mDistances = Mat::eye(m2DLeftCorners.cols, epiLinesPi2.cols, CV_64F);

    for(int i = 0; i < m2DRightCorners.cols; i++) {
        for(int j = 0; j < epiLinesPi2.cols; j++) {
            double a = epiLinesPi2.at<double>(0, j);
            double b = epiLinesPi2.at<double>(1, j);
            double c = epiLinesPi2.at<double>(2, j);
            double x = m2DRightCorners.at<double>(0, i);
            double y = m2DRightCorners.at<double>(1, i);
            double distance = (abs(a*x+b*y+c))/(sqrt(a*a+b*b));

            a = epiLinesPi1.at<double>(0, i);
            b = epiLinesPi1.at<double>(1, i);
            c = epiLinesPi1.at<double>(2, i);
            x = m2DLeftCorners.at<double>(0, j);
            y = m2DLeftCorners.at<double>(1, j);
            distance += (abs(a*x+b*y+c))/(sqrt(a*a+b*b));

            mDistances.at<double>(i, j) = distance;
        }
    }

    // Retour de la matrice fondamentale
    return mDistances;
}

// -----------------------------------------------------------------------
/// \brief Initialise et calcule les indices des points homologues.
///
/// @param mDistances: matrice des distances
/// @param fMaxDistance: distance maximale autorisant une association
/// @param mRightHomologous: liste des correspondants des points gauche
/// @param mLeftHomologous: liste des correspondants des points droite
/// @return rien
// -----------------------------------------------------------------------
void iviMarkAssociations(const Mat& mDistances,
                         double dMaxDistance,
                         Mat& mRightHomologous,
                         Mat& mLeftHomologous) {

    int homologousCount = 0;
    int hiddenFromLeft = 0;
    int hiddenFromRight = 0;

    mRightHomologous = Mat::ones(mDistances.cols, 1, CV_8S)*-1;
    mLeftHomologous = Mat::ones(mDistances.cols, 1, CV_8S)*-1;

    for(int i = 0; i < mDistances.rows; i++){
        double min = mDistances.at<double>(i, 0);
        double minIndex = 0;
        for(int j = 1; j < mDistances.cols; j++){
            if(mDistances.at<double>(i, j) < min){
                min = mDistances.at<double>(i, j);
                minIndex = j;
                if(min < dMaxDistance){
                    mRightHomologous.at<int8_t>(minIndex) = i;
                    mLeftHomologous.at<int8_t>(i) = minIndex;
                }
            }


        }
    }

    std::cout << "Right Homologous " << std::endl;
    std::cout << mRightHomologous << std::endl;

    std::cout << "Left Homologous" << std::endl;
    std::cout << mLeftHomologous << std::endl;

}
