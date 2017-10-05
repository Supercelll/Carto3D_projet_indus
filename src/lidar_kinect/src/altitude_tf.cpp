#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Float64.h>


void poseCallback(const std_msgs::Float64& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(0.0, 0.0, msg.data) );
  /*tf::Quaternion q;
  q.setX(msg.pose.pose.orientation.x);
  q.setY(msg.pose.pose.orientation.y);
  q.setZ(msg.pose.pose.orientation.z);
  q.setW(msg.pose.pose.orientation.w);
  double roll, pitch, yaw;
  tf::Matrix3x3(q).getRPY(roll, pitch, yaw);
  q.setRPY(roll, pitch, 0);
  transform.setRotation(q);*/
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_footprint", "base_stabilized"));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_broadcaster");
  //if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  //turtle_name = argv[1];

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/mavros/global_position/rel_alt", 10, &poseCallback);

  ros::spin();
  return 0;
};


