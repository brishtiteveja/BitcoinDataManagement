/*
 * FormatFile.h
 *
 *  Created on: Jan 18, 2014
 *      Author: zehadyzbdullahkhan
 */

#ifndef FORMATFILE_H_
#define FORMATFILE_H_

#include "CommonHeaders.h"

class FormatFile {
public:
	void formatAddressFile();
	void formatTxOutFile();
	void formatTxTimeFile();
	string numToString(long int num);
	int stringToInt(string s);
	double stringToDouble(string s);
	time_t convertToEpochtime(string realTime);
	struct tm* convertToUnixtime(time_t epochTime);


	FormatFile(){

	};
	~FormatFile(){

	};
};

#endif /* FORMATFILE_H_ */
