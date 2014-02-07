/*
 * IdentifyBitcoinUserEfficient.h
 *
 *  Created on: Jan 7, 2014
 *      Author: zehadyzbdullahkhan
 */

#ifndef IDENTIFYBITCOINUSEREFFICIENT_H_
#define IDENTIFYBITCOINUSEREFFICIENT_H_

#include "CommonHeaders.h"

class IdentifyBitcoinUserEfficient{
private:
	struct addrTXrep{
		long int addrID;
		long int txID;
		long int value;
	};
	vector<bool> GotUserID;
	mlili userID;
	list<addrTXrep> AT;//input
	vector<addrTXrep> ATT;//output

public:
	IdentifyBitcoinUserEfficient(){

	}
	~IdentifyBitcoinUserEfficient(){

	}
	void identifyBitcoinUser();
};

#endif /* IDENTIFYBITCOINUSEREFFICIENT_H_ */
