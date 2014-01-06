/*
 * createBitcoinGraph.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zehadyzbdullahkhan
 */
#include "CreateBitcoinGraph.h"

////unique pair in multimap
//template<class T1, class T2>
//typename multimap<T1,T2>::const_iterator find_pair(const multimap<T1,T2>& mmap, const pair<T1,T2>& p){
//	typename multimap<T1,T2>::const_iterator it;
//	std::pair<it,it> range = mmap.equal_range(p.first);
//
//	for(it k = range.first; k != range.second; ++k){
//		if(k->second == p.second){
//			return k;
//		}
//	}
//
//	return mmap.end();
//}

void createGraph(){
	ifstream txEdgeFileName;
	txEdgeFileName.open((MAC_BITCOIN_PATH + "bitcoin dataset main/bitcoin_computed/txedge.txt").c_str(),ifstream::in);
	ifstream userMapFileName;
	userMapFileName.open((MAC_BITCOIN_PATH + "bitcoin dataset main/bitcoin_computed/contraction.txt").c_str(),ifstream::in);

	mmii edge;
	mii userMap;

	int cnt = 0;

	int txID, addrID, userID;
	while(userMapFileName >> addrID >> userID && !userMapFileName.eof()){
		userMap[addrID] = userID;
		cnt++;
		if(cnt % 10000 == 0)
			cout << "addr = " << addrID << " userID = " << userID << endl;
	}

	cnt = 0;

	int addrFrom,addrTo;
	ofstream txUserEdgeFileName;
	txUserEdgeFileName.open(string(MAC_BITCOIN_PATH + "Bitcoin_Data/txuseredge.txt").c_str(),ofstream::out);

	while(txEdgeFileName >> txID >> addrFrom >> addrTo){
		int userFrom = userMap[addrFrom];
		int userTo = userMap[addrTo];
		cnt++;
		if(cnt % 10000 == 0)
			cout << "userFrom = " << userFrom << " userTo = " << userTo << endl;
		txUserEdgeFileName << txID << "\t" << userFrom << "\t" <<userTo << endl;
	}

}


