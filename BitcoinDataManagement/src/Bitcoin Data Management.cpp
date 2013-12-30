//============================================================================
// Name        : Bitcoin.cpp
// Author      : Dhrubo Khan Ananda
// Version     :
// Copyright   : Your copyright notice: This is all free ..
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "BitcoinDataManagement.h"

//convert integer to string
string convertInt(int number)
{
    if (number == 0)
        return "0";
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

int execute() {
	//input and output file specification
	ifstream ifs("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/BitcoinTransactionNetworkDataset/MyData/user_edges_2011-07-13.txt");
	ofstream ofs("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/BitcoinTransactionNetworkDataset/MyData/user_edges_for_PA.txt");

	string s;
	si timeAndLineNum; //pair storing time and line number
	vsi timesAndLineNums; //vector of such pairs
	vs savedLines;//storing the entire file in string vectors
	vs prefinalLines; // string vector to store with increasing time
	vs finalLines;    // storing only unique from->to transactions
//	vi markLine;              *****what's wrong with vector<int>

	int c = 0;
	int lineNumber = 0;

	string tmpString;
	while(ifs >> s){
		c++;
		if(c < 4)			// not the timestamp
			tmpString += s + "\t";  //adding from node, to node and bitcoin value to the data row

		if(c == 4){        //when it's timestamp
			int year,month,day,hour,min,sec;
			sscanf(s.c_str(),"%d-%d-%d-%d-%d-%d",&year,&month,&day,&hour,&min,&sec);
			//cout << year <<" " << month <<" " << day <<" " << hour <<" " << min <<" " << sec << endl;

			//converting to unix time
			struct tm* time_info;
			time_info -> tm_year = year;
			time_info -> tm_mon = month;
			time_info -> tm_mday = day;
			time_info -> tm_hour = hour;
			time_info -> tm_min = min;
			time_info -> tm_sec = sec;

			time_t unix_time = mktime(time_info); //converting to Unix time

			int time = unix_time;
			string t = convertInt(time);

			tmpString += t;//adding the unix time to the temporary string to complete creating each data row
			//cout << tmpString << endl;
			savedLines.push_back(tmpString); //saving the data row
			tmpString.clear();

			timeAndLineNum.first = s;
			timeAndLineNum.second = lineNumber++;
			timesAndLineNums.push_back(timeAndLineNum);

			c = 0;
		}
	}

	sort(timesAndLineNums.begin(),timesAndLineNums.end()); //sorting the pair vector according to the increasing time

	//printing out the data according to the increasing time
	tr(timesAndLineNums,i){
		int N = i -> second;
		ofs << savedLines[N] << endl;
	//	prefinalLines.push_back(savedLines[N]);
	}


	//vector storing index for data row with same from -> to node
//	int len = prefinalLines.size();

//	for(int i = 0; i < len - 1;i++){
//		cout << "hello" << endl;
//		int fromi, toi;
//		sscanf(prefinalLines[i].c_str(),"%d\t%d*",&fromi,&toi);
//		cout << fromi << " " << toi << " " << endl;
//		for(int j = prefinalLines.size() - 1 ; j > i;j--){
//			int fromj, toj;
//			sscanf(prefinalLines[j].c_str(),"%d\t%d*",&fromj,&toj);
//			if(fromi == fromj && toi == toj){
//				markLine.push_back(j);
//			}
//		}
//	}
//	//removing duplicates (from->to) from the prefinalLines vector
//	for(int i=0;i < (int)prefinalLines.size();i++){
//		if(find(markLine.begin(),markLine.end(),i) == markLine.end()){ // if current index i is not found in the markedLine index vector choose that
//			finalLines.push_back(prefinalLines[i]);
//		}
//	}
//
//	tr(prefinalLines,row){
//		ofs << *row << endl;
//	}

	//closing
	ifs.close();
	ofs.close();

	return 0;
}


