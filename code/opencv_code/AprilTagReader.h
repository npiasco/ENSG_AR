#include <iostream>
#include <map>
#include <vector>

#include "opencv2/opencv.hpp"

#include "apriltag.h"
#include "tag36h11.h"
#include "tag36h10.h"
#include "tag36artoolkit.h"
#include "tag25h9.h"
#include "tag25h7.h"
#include "common/getopt.h"
#include "common/homography.h"

typedef std::vector<double> dvec3;
typedef std::vector<dvec3> dvec3x3;
typedef std::map<int, std::pair<dvec3, dvec3x3> > posT;

/**
* Structure de donnée contenant les informations relatives aux tags détectés.
*
* @param tagId = le numéro du tag (de 0 à 36)
* @param position = le vecteur position du tag par rapport à la caméra
* @param orientation = la matrice de rotation du tag par rapport à la caméra
*
**/
typedef struct tagData
{
    int tagId;
    float position[3];
    float orientation[3][3];
} TagData;


class AprilTagReader
{
public:
    /**
    * Constructeur de la classe
    * 
    * @param camera_id = numéro de la caméra à ouvire (dev/videoX)
    * @param width = largeur désirée de l'image' (en pixel)
    * @param height = hauteur désirée de l'image' (en pixel)
    * @param focal = distance focal de la caméra (en pixel)
    * @param cx = position en x du centre optique (en pixel)
    * @param cy = position en y du centre optique (en pixel)
    * @param tagSize = taille du tag (en cm)
    *
    **/
    AprilTagReader(int camera_id=0, int width=640, int height=480, float focal=817.18087220476332, float cx=319.5, float cy=239.5, float tagSize=16.5);

    /**
    * Destructeur
    *
    **/
    ~AprilTagReader();

    /**
    * Méthode pour récupérer la prochaine image de la caméra
    *
    * @return = la dernière image
    *
    **/
    cv::Mat const getImage();

    /**
    * Méthode pour récupérer la pose des tags détecter dans la dernière image capturé avec la méthode getImage
    *
    * @return = un tableau de TagData
    *
    **/
    std::vector<TagData> const getTags();

private:

    cv::Mat current_image;
    cv::VideoCapture cap;
    float focal, cx, cy, tagSize;

    apriltag_family_t *tf;
    apriltag_detector_t *td;

};
