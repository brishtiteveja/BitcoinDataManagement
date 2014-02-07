/*
 * computeOverBitcoinData.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: zehadyzbdullahkhan
 */
#include "ComputeOverBitcoinData.h"


void ComputeOverBitcoinData::compute(){
	ifstream txFileName;
	txFileName.open(string(BITCOINPROCESSEDPATH + "tx.txt").c_str(),ifstream::in);
	ifstream txInFileName;
	txInFileName.open(string(BITCOINPROCESSEDPATH + "txin.txt").c_str(),ifstream::in);
	ifstream txOutFileName;
	txOutFileName.open(string(BITCOINPROCESSEDPATH + "txoutn.txt").c_str(),ifstream::in);
	ifstream txutimeFileName;
	txutimeFileName.open(string(BITCOINPROCESSEDPATH + "txtimeunix.txt").c_str(),ifstream::in);

	ofstream balanceFileName;
	balanceFileName.open(string(MAC_PATH + "computed/balances.txt").c_str(),ofstream::out);
	ofstream degreeFileName;
	degreeFileName.open(string(MAC_PATH + "computed/degree.txt").c_str(),ofstream::out);


	mlili addrBalanceMap;
	mlili inDegMap;
	mlili outDegMap;


	//taking output from txOutFileName

	long int txID;
	long int blockID,n_inputs,n_outputs;
//	long int stopper = 0;
	bool MovePastFlagIn = false;
	bool MovePastFlagOut = false;
	while(txFileName >> txID >> blockID >> n_inputs >> n_outputs && !txFileName.eof()){
//		stopper++;
		cout << "tx = " << txID << " " << blockID << " " << " " << n_inputs << " " << n_outputs << endl;
		long int txInID,txOutID;
		long int addrID;
		double value;


		int cnt = 0;
		if(txInFileName.is_open()){
			while(n_inputs != 0 && !txInFileName.eof()){
				if(MovePastFlagIn == false){
					txInFileName >> txInID >> addrID >> value;
				}else{
					MovePastFlagIn = false;
				}

				if(txInID == txID){
					cout <<"txIn = " << txInID << " " << addrID << " " << value << endl;
					cnt++;
					//increase out degree of the input address
					outDegMap[addrID] += n_outputs;
					//decrease balance of the input address
					addrBalanceMap[addrID] -= value;
				}
				if(cnt == n_inputs){
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
					cout << "txOut = " << txOutID << " " << addrID << " " << value << endl;
					cnt++;
					//increase in degree of output address
					inDegMap[addrID] += n_inputs;
					addrBalanceMap[addrID] += value;
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

//	tr(inDegMap,it){
//		cout << "addr = " << it->first << " indeg = " << it->second << endl;
//	}
//	tr(outDegMap,it){
//			cout << "addr = " << it->first << " outdeg = " << it->second << endl;
//	}
//	tr(addrBalanceMap,it){
//			cout << "addr = " << it->first << " balance = " << it->second << endl;
//	}

	ifstream addressFileName;
	addressFileName.open("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin dataset/addresses.txt",ifstream::in);

	long int addrID;
	string addr;
	addressFileName >> addrID;
	balanceFileName << addrID << "\t" << addrBalanceMap[addrID] << endl;
	degreeFileName << addrID << "\t" << inDegMap[addrID] << "\t" << outDegMap[addrID] << endl;
	while(addressFileName >> addrID >> addr){
		balanceFileName << addrID << "\t" << addrBalanceMap[addrID] << endl;
//		cout<< "balance  " << addrID << "\t" << addrBalanceMap[addrID] << endl;
		degreeFileName << addrID << "\t" << inDegMap[addrID] << "\t" << outDegMap[addrID] << endl;
//		cout << "degree  " << addrID << "\t" << addrBalanceMap[addrID] << endl;
	}

	txInFileName.close();
	txOutFileName.close();
	txFileName.close();
	addressFileName.close();
	degreeFileName.close();
}

