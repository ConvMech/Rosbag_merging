#include "header.h"

int main(){
	const char* list[] = {"/home/tommy/bagfile/important/2018-04-10-03-05-00.bag","/home/tommy/bagfile/important/2018-04-10-04-51-31.bag"};
	string outputLocation = "/home/tommy/bagfile/api_output_test2.bag";
	vector<string> bagLocation (list, list + sizeof(list)/sizeof(list[0]));
	mergeBag merge(bagLocation,outputLocation);
	merge.readTopics();
	//merge.listTopics();
	merge.merge();
	return 0;
}
