#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

ros::Publisher marker_pub;
visualization_msgs::Marker marker;


void checkLocationCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    vector<float> goal1 = {0.0, -6.0};
    vector<float> goal2 = {1.0, 0.0};
    // check velocity of robot less than 0.0001
    if (abs(msg->pose.pose.position.x - goal1[0]) < 1.0 && abs(msg -> pose.pose.position.y - goal1[1]) < 1.0) {
        if (abs(msg->twist.twist.linear.x) < 0.0001 && abs(msg -> twist.twist.angular.z) < 0.0001)
        {
            if (!fistGoalReached)
            {
                ROS_INFO("First Goal Reached");
                fistGoalReached = true;
                sleep(5);
                ROS_INFO("Item Picked up");
                marker.action = visualization_msgs::Marker::DELETE;
                marker_pub.publish(marker);
            }
            
        }
    }
    if (fistGoalReached && !secondGoalReached) {
        // ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
        if (abs(msg->pose.pose.position.x - goal2[0]) < 1.0 && abs(msg -> pose.pose.position.y - goal2[1]) < 1.0)
        {
            if (abs(msg->twist.twist.linear.x) < 0.0001 && abs(msg -> twist.twist.angular.z) < 0.0001)
            {
                if (fistGoalReached && !secondGoalReached) {
                    ROS_INFO("Second Goal Reached");
                    secondGoalReached = true;
                    sleep(5);
                    ROS_INFO("Item Dropped off");
                    marker.pose.position.x = 0.0;
                    marker.pose.position.y = 0.0;
                    marker.action = visualization_msgs::Marker::ADD;
                    marker_pub.publish(marker);
                    ros::shutdown();
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    // Set the frame ID and timestamp.
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type
    marker.type = shape;

    // Set the marker action.
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.
    marker.pose.position.x = 0.0;
    marker.pose.position.y = -6.0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 0.0;

    // Set the scale of the marker
    marker.scale.x = 0.4;
    marker.scale.y = 0.4;
    marker.scale.z = 0.4;

    // Set the color
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    while (marker_pub.getNumSubscribers() < 1)
    {
        if (!ros::ok())
        {
            return 0;
        }
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
    }
    ROS_INFO("Place Object");
  	marker_pub.publish(marker);
  	sleep(5);
    ROS_INFO("Object Picked Up");
  	marker.action = visualization_msgs::Marker::DELETE;
  	marker_pub.publish(marker);
  	sleep(5);
  	ROS_INFO("Drop off object");
  	marker.action = visualization_msgs::Marker::ADD;
  	marker.pose.position.x = 0.0;
    marker.pose.position.y = 0.0;
  	marker_pub.publish(marker);
    return 0;
}

