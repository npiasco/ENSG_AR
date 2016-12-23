#include "AprilTagReader.h"






int main()
{

    AprilTagReader reader;


    do{
        
        cv::imshow("Tag Detections", reader.getImage());
        reader.getTags();

    }while(cv::waitKey(1)<0);
        



    return 0;
}