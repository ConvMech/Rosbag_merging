#include "header.h"

int main(){
	const char* list[] = {"/home/tommy/bagfile/2018-03-21-23-12-18.bag","/home/tommy/bagfile/2018-03-21-23-13-12.bag"};
	string outputLocation = "/home/tommy/bagfile/api_output_test2.bag";
	vector<string> bagLocation (list, list + sizeof(list)/sizeof(list[0]));
	mergeBag merge(bagLocation);
	merge.readTopics();
	merge.listTopics();
	return 0;
}
