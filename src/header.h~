#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Imu.h>
#include <boost/foreach.hpp>
#include "ros/ros.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <string>

#define foreach BOOST_FOREACH

using namespace std;

class mergeBag{
	private:
		vector<vector<string> > topics;
		vector<string> bagLocation;
		string outputLocation;
		int bagNumber;
	public:
		mergeBag(const vector<string>& inBagLocation, string inOutputLocation);
		void readTopics();
		void listTopics();
		void rewriteOne(int bagIndex);
		void merge();
};

void GetStdoutFromCommand(string cmd, string& result) {
	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
				pclose(stream);
			}
	result = data;
}


void mergeBag::merge(){
	for (int i = 0; i < bagNumber; ++i){
		cout<<"rewriting Bag:"<<bagLocation[i]<<endl;
		rewriteOne(i);
	}
	cout<<"refining timestamp"<<endl;
	string res;
	GetStdoutFromCommand("rosrun bag_api refine_time.py", res);
	cout<<res<<endl;
	cout<<"merging finished"<<endl;
}

mergeBag:: mergeBag(const vector<string>& inBagLocation, string inOutputLocation){
	bagLocation = inBagLocation;
	bagNumber = inBagLocation.size();
	outputLocation = inOutputLocation;
}

void mergeBag:: rewriteOne(int bagIndex){
	string location = bagLocation[bagIndex];
	rosbag::Bag input(location);
	rosbag::Bag output;
	if (bagIndex != 0){
		output.open(outputLocation, rosbag::bagmode::Append);
	}
	else{
		output.open(outputLocation, rosbag::bagmode::Write);
	}	
	rosbag::View topic_view(input, rosbag::TopicQuery(topics[bagIndex]));
	string numberStr = to_string(bagIndex);
	ros::Duration time_offset(10);
	BOOST_FOREACH(rosbag::MessageInstance const message, topic_view) {
		output.write(message.getTopic() + numberStr, message.getTime(), message, message.getConnectionHeader()); 
	}
	output.close();
}

void mergeBag:: readTopics(){ // read the topics from each bagfile.
	for (int i = 0; i < bagNumber; ++i){		
		string location = bagLocation[i];
		rosbag::Bag bag_read;
		bag_read.open(location, rosbag::bagmode::Read);		
		rosbag::View view(bag_read);
		vector<const rosbag::ConnectionInfo *> connection_infos = view.getConnections();
		vector<string> single_bag;
		BOOST_FOREACH(const rosbag::ConnectionInfo *info, connection_infos) {
			single_bag.push_back(info->topic);
		}
		topics.push_back(single_bag);
		bag_read.close();
	}
}

void mergeBag:: listTopics() { // print all the topics we have
	for (int i = 0; i < bagNumber; ++i){
		cout<<endl<<"Bag: "<<bagLocation[i]<<endl;
		for(int j = 0; j < 50; ++j) {
			cout<<"*";
		}
		cout<<endl;
		for (int j = 0;  j < topics[i].size(); ++j){
			cout<<topics[i][j]<<endl;
		}
	}
}
