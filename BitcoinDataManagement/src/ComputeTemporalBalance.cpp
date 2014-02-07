/*
 * ComputeTemporalBalance.cpp
 *
 *  Created on: Jan 27, 2014
 *      Author: zehadyzbdullahkhan
 */

#include "ComputeTemporalBalance.h"

void ComputeTemporalBalance::compTemporalBalance(){
	ifstream txFileName;
	txFileName.open(string(BITCOINPROCESSEDPATH + "tx.txt").c_str(),ifstream::in);
	ifstream txInFileName;
	txInFileName.open(string(BITCOINPROCESSEDPATH + "txin.txt").c_str(),ifstream::in);
	ifstream txOutFileName;
	txOutFileName.open(string(BITCOINPROCESSEDPATH + "txoutn.txt").c_str(),ifstream::in);
	ifstream txUnixTimeFileName;
	txUnixTimeFileName.open(string(BITCOINPROCESSEDPATH + "txtimeunix.txt").c_str(),ifstream::in);

	ifstream userMap1FileName;
	userMap1FileName.open((BITCOINPROCESSEDPATH + "computed/user contraction/useridh1.txt").c_str(),ifstream::in);
	ifstream userMap2FileName;
	userMap2FileName.open((BITCOINPROCESSEDPATH + "computed/user contraction/useridh2.txt").c_str(),ifstream::in);

	mlili userMap1;
	mlili userMap2;

//	cout << "Unix time File." << endl;
	long int txID;
	long int unixt;
	string tmp;

	mlili unix_time;
	int cnt = 0;
//	while(txUnixTimeFileName >> tmp >> txID >> unixt && !txUnixTimeFileName.eof()){
//		unix_time[txID] = unixt;
////		cnt++;
////		if(cnt % 1000000 == 0)
////			cout << "TXID = " << txID << " time = " << unix_time[txID] << endl;
//	}
//


	cout << "Heuristics 1 User Map." << endl;
	long int addrID, userID;
//	long int addrFrom,addrTo;
	cnt = 0;

	while(userMap1FileName >> addrID >> userID && !userMap1FileName.eof()){
		userMap1[addrID] = userID;
//		cnt++;
//		if(cnt % 1000000 == 0)
//			cout << "addr1 = " << addrID << " userID1 = " << userID << endl;
	}

//	cout << "Heuristics 2 User Map." << endl;
//	cnt = 0;
//	while(userMap2FileName >> addrID >> userID && !userMap2FileName.eof()){
//		userMap2[addrID] = userID;
////		cnt++;
////		if(cnt % 1000000 == 0)
////			cout << "addr = " << addrID << " userIDh2 = " << userID << endl;
//	}

	cout << "Temporal In Out Balance Map." << endl;
	//time
	// 2013-01-01 unixtime:1356998400
	// 2013-01-14 unixtime:1358121600
	// 2014-01-10 unixtime:1389312000
	// biweekly length = 1123200
	long int unix201314time[14] = {1356998400,1359676800,1362096000,1364774400,1367366400,1370044800,1372636800,
				1375315200,1377993600,1380585600,1383264000,1385856000,1388534400};
	long int start_time = 1356998400;
	long int end_time = 1389312000;
	long int time_diff = 1123200 * 2; // 4 weeks
	bool MovePastFlagTX = false;

	mlid userInBalanceMap;  // in balance of each user at time
	mlid userOutBalanceMap; // out balance of each user at time
	mlili userInDegMap;
	mlili userOutDegMap;
	long int time,k;
	for(k=0; k < 13 ;k++){
		time=unix201314time[k];
		cout << "Time = " << time << endl;
		ofstream userInBalance;
		userInBalance.open(string(BITCOINPROCESSEDPATH + "computed/balanceMonthly2013/inBalance_" + f.numToString(time) +".txt").c_str(),ofstream::out);

		ofstream userInDeg;
		userInDeg.open(string(BITCOINPROCESSEDPATH + "computed/degMonthly2013/inDeg_" + f.numToString(time) +".txt").c_str(),ofstream::out);

		ofstream userOutBalance;
		userOutBalance.open(string(BITCOINPROCESSEDPATH + "computed/balanceMonthly2013/outBalance_" + f.numToString(time) +".txt").c_str(),ofstream::out);

		ofstream userOutDeg;
		userOutDeg.open(string(BITCOINPROCESSEDPATH + "computed/degMonthly2013/outDeg_" + f.numToString(time) +".txt").c_str(),ofstream::out);


		long int max_tx_id = -1;
		long int tx_id,tx_time;
		string tmp;
		while(txUnixTimeFileName >> tmp >> tx_id >> tx_time && !txUnixTimeFileName.eof()){
			if(tx_time >= time){
				max_tx_id = tx_id;
				cout << "Upto time = " << time << endl;
				break;
			}
		}

		long int txID;
		long int blockID,n_inputs,n_outputs;
		long int txInID,txOutID;
		long int addrID;
		double value;
	//	long int stopper = 0;
		bool MovePastFlagIn = false;
		bool MovePastFlagOut = false;

		int fs ;
		bool f = true;;
		while(!txFileName.eof())
		{
			if(MovePastFlagTX == false){
				txFileName >> txID >> blockID >> n_inputs >> n_outputs;
			}else{
				MovePastFlagTX = false;
			}
			if(f){
				fs = txID;
				f = false;
			}
			if(txID >= max_tx_id){
				MovePastFlagTX = true;
				cout << "From tx " << fs << " to tx " << txID << endl;
				break;
			}

//		stopper++;
//			cout << "tx = " << txID << " " << blockID << " " << " " << n_inputs << " " << n_outputs << endl;

			int cnt = 0;
			if(txInFileName.is_open()){
				while(n_inputs != 0 && !txInFileName.eof()){
					if(MovePastFlagIn == false){
						txInFileName >> txInID >> addrID >> value;
					}else{
						MovePastFlagIn = false;
					}

					if(txInID == txID){
//						cout <<"txIn = " << txInID << " " << addrID << " " << value << endl;
						cnt++;
					}
					if(cnt == n_inputs){
						//decrease balance of the input address
						userOutBalanceMap[userMap1[addrID]] = userOutBalanceMap[userMap1[addrID]] + value;
						userOutDegMap[userMap1[addrID]] = userOutDegMap[userMap1[addrID]] + n_outputs;
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
			if(txOutFileName.is_open()){
				while(n_outputs != 0  && !txOutFileName.eof()){
					if(MovePastFlagOut == false){
						txOutFileName >> txOutID >> addrID >> value;
					}else{
						MovePastFlagOut = false;
					}
					if(txOutID == txID){
//						cout << "txOut = " << txOutID << " " << addrID << " " << value << endl;
						cnt++;
						if(txID > 23992643){
							cout << value << endl;
							if(userInBalanceMap[userMap1[addrID]] == 0){
								cout << "No balance." << endl;
								cout << "txOut = " << txOutID << " " << addrID << " " << value << endl;
							}
						}
						userInBalanceMap[userMap1[addrID]] = userInBalanceMap[userMap1[addrID]] + value;
						userInDegMap[userMap1[addrID]] = userInDegMap[userMap1[addrID]] + n_inputs;
						//increase in degree of output address

						//correcting movepast flag
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
	//		stopper++;
	//		if(stopper == 10000)
	//			break;
		}

		int cn = 0;
		tr(userInBalanceMap,u){
			cn++;
			if(cn == 1000000)
				cout << u->first << "\t" << u->second << endl;
			userInBalance << u->first << "\t" << u->second << endl;
		}
		cn = 0;
		tr(userInDegMap,u){
			cn++;
			if(cn == 1000000)
				cout << u->first << "\t" << u->second << endl;
			userInDeg << u->first << "\t" << u->second << endl;
		}

		cn = 0;
		tr(userOutBalanceMap,u){
			cn++;
			if(cn == 1000000)
				cout << u->first << "\t" << u->second << endl;
			userOutBalance << u->first << "\t" << u->second << endl;
		}

		cn = 0;
		tr(userOutDegMap,u){
			cn++;
			if(cn == 1000000)
				cout << u->first << "\t" << u->second << endl;
			userOutDeg << u->first << "\t" << u->second << endl;
		}

		userInBalance.close();
		userInDeg.close();

		userOutBalance.close();
		userOutDeg.close();
	}

	txFileName.close();
	txInFileName.close();
	txOutFileName.close();
	txUnixTimeFileName.close();
	userMap1FileName.close();
	userMap2FileName.close();
}

