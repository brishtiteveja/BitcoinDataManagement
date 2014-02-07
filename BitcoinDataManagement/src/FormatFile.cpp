/*
 * FormatFile.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: zehadyzbdullahkhan
 */

#include "FormatFile.h"


string FormatFile::numToString(long int num){
	ostringstream convert;
	convert << num;

	//hello
	string res = convert.str();
	return res;
}

int FormatFile::stringToInt(string s){
	return atoi(s.c_str());
}

double FormatFile::stringToDouble(string s){
	return atof(s.c_str());
}


//2013-12-25 08:59:39
time_t FormatFile::convertToEpochtime(string realTime){
	struct tm timeInfo;
	timeInfo.tm_year = atoi(realTime.substr(0,4).c_str()) - 1900;
	timeInfo.tm_mon = atoi(realTime.substr(5,2).c_str()) - 1;
	timeInfo.tm_mday = atoi(realTime.substr(8,2).c_str());
	timeInfo.tm_hour = atoi(realTime.substr(11,2).c_str());
	timeInfo.tm_min = atoi(realTime.substr(14,2).c_str());
	timeInfo.tm_sec = atoi(realTime.substr(17,2).c_str());
	//cout << timeInfo.tm_year << " " << timeInfo.tm_mon << " " << timeInfo.tm_mday << " " << timeInfo.tm_hour << " " << timeInfo.tm_min << " " << timeInfo.tm_sec << endl;
	time_t epochTime = mktime(&timeInfo);
	//cout << epochTime << endl;
	return epochTime;
}

struct tm* FormatFile::convertToUnixtime(time_t epochTime){
	struct tm *t = localtime(&epochTime);
	t -> tm_year += 1900;
	t -> tm_mon  += 1;
	return t;
}

void FormatFile::formatAddressFile(){
	ifstream addrFile;

	addrFile.open(string(MAC_PATH + "addresses.txt").c_str(),ifstream::in);

	ofstream addrOutFile;
	addrOutFile.open(string(MAC_PATH + "addressesn.txt").c_str(),ofstream::out);
	if(addrFile.is_open()){
		string line;

		while(getline(addrFile,line)){
			istringstream iss(line);
			long int addrID;
			string addr;

			while(iss >> addrID){
				iss >> addr;

				if(addr != "" && addr != "-X-X-X-"){
					addrOutFile << addrID << "\t" << addr << endl;
				}else{
					addrOutFile << addrID << "\t" << "unknown" << endl;
				}
				addr = "-X-X-X-";
			}
		}
	}


}

void FormatFile::formatTxOutFile(){
	ifstream txOutFile;

	txOutFile.open(string(BITCOINPROCESSEDPATH + "txout.txt").c_str(),ifstream::in);

	ofstream txOutOutFile;
	txOutOutFile.open(string(BITCOINPROCESSEDPATH + "txoutn.txt").c_str(),ofstream::out);

	int cnt = 0;
	if(txOutFile.is_open()){
			string line;
			cout << "hello" << endl;
			while(getline(txOutFile,line)){
				cnt++;
//				if(cnt == 30)
//					break;
				istringstream iss(line);
				string txOutID, addrID, value;

				while(iss >> txOutID >> addrID){
					iss >> value;

					if(value != "" && value != "-X-X-X-"){
						cout << txOutID << "\t" << addrID << "\t" << value << endl;
						txOutOutFile << txOutID << "\t" << addrID << "\t" << value << endl;
					}else{
						cout << txOutID << "\t" << addrID << "\t" << 0 << endl;
						txOutOutFile << txOutID << "\t" << addrID << "\t" << 0 << endl;
					}
					value = "-X-X-X-";
				}
			}
		}

}
