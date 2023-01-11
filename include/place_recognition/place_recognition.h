#ifndef PLACE_RECOGNITION_H_
#define PLACE_RECOGNITION_H_

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2/utils.h>

#include "dbow3/vocabulary/vocabulary.h"
#include "dbow3/database/database.h"
#include "place_recognition/images.h"

namespace place_recognition
{
class PlaceRecognition
{
public:
    PlaceRecognition();
    void process();

private:
    void image_callback(const sensor_msgs::ImageConstPtr& msg);

    void load_reference_images();
    void calc_features(Image& image,std::string name,cv::Mat img);

    void create_database();

    std::vector<std::string> split(std::string& input,char delimiter);

    // node handler
    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;

    // subscriber
    ros::Subscriber img_sub_;

    // publisher
    ros::Publisher img_pub_;
    ros::Publisher pose_pub_;

    // database
    dbow3::Database db;

    // detector
    cv::Ptr<cv::Feature2D> detector_;

    // Reference
    std::vector<Images> reference_images_;

    // buffer
    std::string file_path_;

    // param
    std::string DIR_PATH_;
    std::string REFERENCE_FILE_PATH_;
	std::string MODE_;
	// bool IS_DEBUG_;
    int HZ_;
};
} // namespace place_recognition

#endif	// PLACE_RECOGNITION_H_