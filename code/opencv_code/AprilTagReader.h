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

typedef struct tagData
{
    int tagId;
    float position[3];
    float orientation[3][3];
} TagData;


class AprilTagReader
{
public:

    AprilTagReader(int camera_id=0, int width=640, int height=480, float focal=817.18087220476332, float cx=319.5, float cy=239.5, float tagSize=16.5);

    ~AprilTagReader();

    cv::Mat const getImage();

    std::vector<TagData> const getTags();

private:

    cv::Mat current_image;
    cv::VideoCapture cap;
    float focal, cx, cy, tagSize;

    apriltag_family_t *tf;
    apriltag_detector_t *td;

};
