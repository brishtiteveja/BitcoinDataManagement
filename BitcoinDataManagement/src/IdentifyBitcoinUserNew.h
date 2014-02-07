/*
 * IdentifyBitcoinUserNew.h
 *
 *  Created on: Jan 10, 2014
 *      Author: zehadyzbdullahkhan
 */

#ifndef IDENTIFYBITCOINUSERNEW_H_
#define IDENTIFYBITCOINUSERNEW_H_

#include "CommonHeaders.h"

class IdentifyBitcoinUserNew {
	//same user map
	mlili userMap;
	mlililist sameUMap;
public:
	void IdentifyBTCUser();
	long int mergeUserID(long int u);
};

#endif /* IDENTIFYBITCOINUSERNEW_H_ */
