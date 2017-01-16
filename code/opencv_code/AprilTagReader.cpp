#include "AprilTagReader.h"



AprilTagReader::AprilTagReader(int camera_id, int width, int height, float focal, float cx, float cy, float tagSize) :
cap(camera_id), cx(cx), cy(cy), tagSize(tagSize)
{
    this->focal = focal * (float) height / (float) width;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
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



std::vector<TagData> const AprilTagReader::getTags(){
	
	if(!(this->current_image.cols > 0 && this->current_image.cols > 0))
		cap >> this->current_image;
		
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
    std::vector<TagData> tagPos;
    for (int i = 0; i < zarray_size(detections); ++i) {
        apriltag_detection_t *det;
        zarray_get(detections, i, &det);
        
        matd_t *m = homography_to_pose(det->H, this->focal, this->focal, this->cx, this->cy);
        
        TagData data;

        data.position[0]=matd_get(m, 0,3)*this->tagSize/2;
        data.position[1]=matd_get(m, 1,3)*this->tagSize/2;
        data.position[2]=matd_get(m, 2,3)*this->tagSize/2;


        for(int l=0;l<3;++l)
            for(int c=0; c<3; ++c)
                data.orientation[l][c]=matd_get(m, l,c);

        data.tagId=det->id;
        tagPos.push_back(data);

    }
    zarray_destroy(detections);

    return tagPos;
}
