/*
 * createBitcoinGraph.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zehadyzbdullahkhan
 */
#include "CreateBitcoinGraph.h"

void CreateBitcoinGraph::createUserGraph(){
	ifstream txFileName;
	txFileName.open(string(BITCOINPROCESSEDPATH + "tx.txt").c_str(),ifstream::in);
	ifstream txInFileName;
	txInFileName.open(string(BITCOINPROCESSEDPATH + "txin.txt").c_str(),ifstream::in);
	ifstream txOutFileName;
	txOutFileName.open(string(BITCOINPROCESSEDPATH + "txoutn.txt").c_str(),ifstream::in);
	ifstream txUnixTimeFileName;
	txUnixTimeFileName.open(string(BITCOINPROCESSEDPATH + "txtimeunix.txt").c_str(),ifstream::in);
	ifstream userMap1FileName;
	userMap1FileName.open(string(BITCOINPROCESSEDPATH + "computed/user contraction/useridh1.txt").c_str(),ifstream::in);
	ifstream userMap2FileName;
	userMap2FileName.open(string(BITCOINPROCESSEDPATH + "computed/user contraction/useridh2.txt").c_str(),ifstream::in);


	ofstream userGraphEdgeh1File;
	userGraphEdgeh1File.open(string(BITCOINPROCESSEDPATH + "computed/usergraph_h1n.txt").c_str(),ofstream::out);
	ofstream userGraphEdgeh2File;
	userGraphEdgeh2File.open(string(BITCOINPROCESSEDPATH + "computed/usergraph_h2n.txt").c_str(),ofstream::out);


	mlili userMap;
	mlili userMap2;

	cout << "Unix time File." << endl;
	long int txID;
	long int unixt;
	string tmp;

	mlili unix_time;
	int cnt = 0;
	while(txUnixTimeFileName >> tmp >> txID >> unixt && !txUnixTimeFileName.eof()){
		unix_time[txID] = unixt;
		cnt++;
		if(cnt % 1000000 == 0)
			cout << "TXID = " << txID << " time = " << unix_time[txID] << endl;
	}

	cout << "Heuristics 1 User Map." << endl;
	long int addrID, userID;
//	long int addrFrom,addrTo;
	cnt = 0;

	while(userMap1FileName >> addrID >> userID && !userMap1FileName.eof()){
		userMap[addrID] = userID;
		cnt++;
		if(cnt % 1000000 == 0)
			cout << "addr1 = " << addrID << " userID1 = " << userID << endl;
	}

	cout << "Heuristics 2 User Map." << endl;
	cnt = 0;
	while(userMap2FileName >> addrID >> userID && !userMap2FileName.eof()){
		userMap2[addrID] = userID;
		cnt++;
		if(cnt % 1000000 == 0)
			cout << "addr = " << addrID << " userIDh2 = " << userID << endl;
	}

	cout << "Start creating user graph." << endl;


	long int blockID,n_inputs,n_outputs;
//	long int stopper = 0;
	bool MovePastFlagIn = false;
	bool MovePastFlagOut = false;
	while(txFileName >> txID >> blockID >> n_inputs >> n_outputs && !txFileName.eof()){
//		stopper++;
//		cout << "tx = " << txID << " " << blockID << " " << " " << n_inputs << " " << n_outputs << endl;
		long int txInID,txOutID;
		long int addrID;
		double value;

		int cnt = 0;
		long int inUserID_h1;
		long int inUserID_h2;
		if(txInFileName.is_open()){
			while(n_inputs != 0 && !txInFileName.eof()){
				if(MovePastFlagIn == false){
					txInFileName >> txInID >> addrID >> value;
				}else{
					MovePastFlagIn = false;
				}

				if(txInID == txID){
//					cout <<"txIn = " << txInID << " " << addrID << " " << value << endl;
					cnt++;
				}
				if(cnt == n_inputs){
					//Getting the input transaction user
					inUserID_h1 = userMap[addrID];
					inUserID_h2 = userMap2[addrID];
					break;
				}
				if(txInID > txID){
					//need to move a line back
					MovePastFlagIn = true;
					break;
				}
			}
		}else{
			cout <<"txInFile is not open." << endl;
		}

		cnt = 0;
		vli outAddrStack;
		vd valueStack;
		if(txOutFileName.is_open()){
			while(n_outputs != 0  && !txOutFileName.eof()){
				if(MovePastFlagOut == false){
					txOutFileName >> txOutID >> addrID >> value;
					outAddrStack.push_back(addrID);
					valueStack.push_back(value);
				}else{
					MovePastFlagOut = false;
				}
				if(txOutID == txID){
//					cout << "txOut = " << txOutID << " " << addrID << " " << value << endl;
					cnt++;
				}

				if(cnt == n_outputs)
					break;
				if(txOutID > txID){
					//need to move a line back
					MovePastFlagOut = true;
					break;
				}
			}
		}else{
			cout << "txOutFile is not open." << endl;
		}

		cnt = 0;
		for(unsigned long int i = 0; i < outAddrStack.size();i++){
			userGraphEdgeh1File << txID << "\t" << inUserID_h1 << "\t" << userMap[outAddrStack[i]] << "\t" <<
					valueStack[i] << "\t" << unix_time[txID] << endl;
			userGraphEdgeh2File << txID << "\t" << inUserID_h2 << "\t" << userMap2[outAddrStack[i]] << "\t" <<
					valueStack[i] << "\t" << unix_time[txID] << endl;
			cnt++;
			if(cnt % 1000 == 0){
				cout << txID << "\t" << inUserID_h1 << "\t" << userMap[outAddrStack[i]] << "\t" <<
					valueStack[i] << "\t" << unix_time[txID] << endl;
				cout << txID << "\t" << inUserID_h2 << "\t" << userMap2[outAddrStack[i]] << "\t" <<
					valueStack[i] << "\t" << unix_time[txID] << endl;
			}
		}

//		stopper++;
//		if(stopper == 10000)
//			break;
	}

}

void CreateBitcoinGraph::createGraphFromTXedge(){
	ifstream txEdgeFileName;
	txEdgeFileName.open(string(MAC_PATH + "txedge.txt").c_str(),ifstream::in);
	ifstream userMapFileName;
	userMapFileName.open(string(MAC_PATH + "computed/user contraction/new/useridh1.txt").c_str(),ifstream::in);
	ifstream userMap2FileName;
	userMap2FileName.open(string(MAC_PATH + "computed/user contraction/new/useridh2.txt").c_str(),ifstream::in);

	ofstream txUserEdgeFileName;
	txUserEdgeFileName.open(string(MAC_PATH + "computed/txuseredge_h1.txt").c_str(),ofstream::out);
	ofstream txUserEdge2FileName;
	txUserEdge2FileName.open(string(MAC_PATH + "computed/txuseredge_h2.txt").c_str(),ofstream::out);

	mmii edge;
	mii userMap;
	mii userMap2;

	cout << "Heuristics 1" << endl;
	int txID, addrID, userID;
	int addrFrom,addrTo;
	int cnt = 0;

	/*
	while(userMapFileName >> addrID >> userID && !userMapFileName.eof()){
		userMap[addrID] = userID;
		cnt++;
		if(cnt % 1000000 == 0)
			cout << "addr = " << addrID << " userID = " << userID << endl;
	}

	cnt = 0;




	while(txEdgeFileName >> txID >> addrFrom >> addrTo){
		int userFrom = userMap[addrFrom];
		int userTo = userMap[addrTo];
		cnt++;
		if(cnt % 1000000 == 0)
			cout << "userFrom = " << userFrom << " userTo = " << userTo << endl;
		txUserEdgeFileName << txID << "\t" << userFrom << "\t" <<userTo << endl;
	}
*/
	cout << "Heuristics 2" << endl;
	cnt = 0;

	while(userMap2FileName >> addrID >> userID && !userMap2FileName.eof()){
		userMap2[addrID] = userID;
		cnt++;
		if(cnt % 1000000 == 0)
			cout << "addr = " << addrID << " userIDh2 = " << userID << endl;
	}

	cnt = 0;

	txEdgeFileName.close();
	txEdgeFileName.open(string(MAC_PATH + "txedge.txt").c_str(),ifstream::in);

	while(txEdgeFileName >> txID >> addrFrom >> addrTo){
		int userFrom = userMap2[addrFrom];
		int userTo = userMap2[addrTo];
		cnt++;
		if(cnt % 1000000 == 0)
			cout << "userFrom2 = " << userFrom << " userTo2 = " << userTo << endl;
		txUserEdge2FileName << txID << "\t" << userFrom << "\t" <<userTo << endl;
	}

	txEdgeFileName.close();
	userMapFileName.close();
	txUserEdgeFileName.close();
	userMap2FileName.close();
	txUserEdge2FileName.close();
}

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

