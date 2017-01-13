#include "AprilTagReader.h"






int main()
{

    AprilTagReader reader(1);

    do{
        
        cv::imshow("Tag Detections", reader.getImage());

    }while(cv::waitKey(1)<0);


    return 0;
}
