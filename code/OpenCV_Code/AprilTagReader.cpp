#include "AprilTagReader.h"



AprilTagReader::AprilTagReader(int camera_id) : cap(camera_id)
{
    this->tf = tag36h11_create();
    this->td = apriltag_detector_create();
    apriltag_detector_add_family(this->td, this->tf);
}

AprilTagReader::~AprilTagReader()
{
    apriltag_detector_destroy(this->td);
    tag36h11_destroy(this->tf);
}

cv::Mat const AprilTagReader::getImage()
{
    cap >> this->current_image;
    cv::Mat copy;
    this->current_image.copyTo(copy);
    return copy;
}

posT const AprilTagReader::getTags(){

    cv::Mat gray;
    cv::cvtColor(this->current_image, gray, cv::COLOR_BGR2GRAY);

    // Make an image_u8_t header for the Mat data
    image_u8_t im = { .width = gray.cols,
        .height = gray.rows,
        .stride = gray.cols,
        .buf = gray.data
    };

    zarray_t *detections = apriltag_detector_detect(this->td, &im);
    std::cout << zarray_size(detections) << " tags detected" << std::endl;

    // Draw detection outlines
    posT tagPos;
    for (int i = 0; i < zarray_size(detections); ++i) {
        apriltag_detection_t *det;
        zarray_get(detections, i, &det);
        
        matd_t *m = homography_to_pose(det->H, 817.18087220476332, 817.18087220476332, 319.5, 239.5);
        
        dvec3 trans;
        dvec3x3 rot;

        std::cout << "x = " << -matd_get(m, 0,3)*16.5/2 << "cm ";
        trans.push_back(-matd_get(m, 0,3)*16.5/2);
        std::cout << "y = " << -matd_get(m, 1,3)*16.5/2 << "cm ";
        trans.push_back(-matd_get(m, 1,3)*16.5/2);
        std::cout << "z = " << -matd_get(m, 2,3)*16.5/2 << "cm" << std::endl;
        trans.push_back(-matd_get(m, 2,3)*16.5/2);

        for(int l=0;l<3;++l)
        {
            dvec3 tmp;
            for(int c=0; c<3; ++c)
                tmp.push_back(matd_get(m, l,c));
            rot.push_back(tmp);
        }


        tagPos[i]=std::pair<dvec3,dvec3x3>(trans, rot);

    }
    zarray_destroy(detections);

    return tagPos;
}
