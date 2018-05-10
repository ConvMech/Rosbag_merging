#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Imu.h>
#include <boost/foreach.hpp>
#include "ros/ros.h"

#define foreach BOOST_FOREACH

using namespace std;

class mergeBag{
	private:
		vector<vector<string> > topics;
		vector<string> bagLocation;
		string outputLocation;
		int bagNumber;
	public:
		mergeBag(const vector<string>& inBagLocation);
		void readTopics();
		void listTopics();
};

mergeBag:: mergeBag(const vector<string>& inBagLocation, string inOutputLocation){
	bagLocation = inBagLocation;
	bagNumber = inBagLocation.size();
	outputLocation = inOutputLocation;
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
