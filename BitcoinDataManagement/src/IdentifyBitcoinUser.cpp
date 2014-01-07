/*
 * IdentifyBitcoinUser.cpp
 *
 *  Created on: Jan 5, 2014
 *      Author: zehadyzbdullahkhan
 */

#include "IdentifyBitcoinUser.h"

struct addrTXrep{
	long int addrID;
	long int txID;
	long int txIn_startPos;
	long int txOut_startPos;
	bool txIn;
	bool r_flag;
};

vector<bool> GotUserID;
mlili userID;

vector<addrTXrep> AT;

void recursiveIdentify(long int A);

void IdentifyBitcoinUsers(){
	ifstream txFileName;
	txFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/tx.txt").c_str(),ifstream::in);
	ifstream txInFileName;
	txInFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/txin.txt").c_str(),ifstream::in);
	ifstream txOutFileName;
	txOutFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/txout.txt").c_str(),ifstream::in);
	ifstream addrFileName;
	addrFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/addresses.txt").c_str(),ifstream::in);
	ifstream ATInFileName;
//	ATInFileName.open(string(MAC_PATH + "AT.rtf").c_str(),ifstream::in);

//	ofstream ATOutFileName;
//	ATOutFileName.open(string(MAC_PATH+"AT.rtf").c_str(),ofstream::out);

	ofstream useridFileName;
	useridFileName.open(string(MAC_PATH+"userid3.txt").c_str(),ofstream::out);


	long int txID,blockID;
	int n_inputs,n_outputs;
	long int stopper = 0;
	bool MovePastFlagIn = false;
	bool MovePastFlagOut = false;

	//populate the AT vector with transactions and addresses
	while(txFileName >> txID >> blockID >> n_inputs >> n_outputs && !txFileName.eof()){
			stopper++;
//			cout << "tx = " << txID << " " << blockID << " " << " " << n_inputs << " " << n_outputs << endl;
			long int txInID,txOutID;
			long int addrID;
			long int value;

			int cnt = 0;
			if(txInFileName.is_open()){
				while(n_inputs != 0 && !txInFileName.eof()){
					if(MovePastFlagIn == false){
						txInFileName >> txInID >> addrID >> value;
					}else{
						MovePastFlagIn = false;
					}

					if(txInID == txID){
//						cout << "txIn = " << txInID << " " << addrID << " " << value << endl;
						addrTXrep tmp;
						tmp.addrID = addrID;
						tmp.txID = txID;
						tmp.txIn = true;
						tmp.r_flag = false;
						tmp.txIn_startPos = AT.size() - cnt; //where the first txin address start from
						tmp.txOut_startPos = -1;
						AT.push_back(tmp);
						cnt++;
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
//						cout << "txOut = " << txOutID << " " << addrID << " " << value << endl;
						addrTXrep tmp;
						tmp.addrID = addrID;
						tmp.txID = txID;
						tmp.txIn = false;  //Not an input transaction
						tmp.r_flag = false;
						tmp.txIn_startPos = -1;
						tmp.txOut_startPos = AT.size() - cnt; // where the first txout start from
						AT.push_back(tmp);
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
//				cout << "txOutFile is not open." << endl;
			}
//			stopper++;
//			if(stopper == 100000)
//				break;
		}

//
//	ATFileName.close();
//

//	addrTXrep tmp;
//	cout << "hello" << endl;
//
//////	while(
//	ATInFileName >> tmp.addrID >> tmp.txID >> tmp.r_flag >> tmp.txIn >> tmp.txIn_startPos >> tmp.txOut_startPos ;//&& !ATInFileName.eof()
//////			//){
//		cout << tmp.addrID << "\t" << tmp.txID << "\t" << tmp.txIn << "\t" << tmp.r_flag << "\t" << tmp.txIn_startPos << "\t" << tmp.txOut_startPos << endl;
//////		AT.push_back(tmp);
//////	}

	long int addrID,lastAddrID;
	string addr;
	addrFileName >> addrID;
	while(addrFileName >> addrID >> addr){
	}
	lastAddrID = addrID;
	GotUserID = vector<bool>(lastAddrID+1,false);
	userID[0] = 0;
	GotUserID[0] = true;
	long int current_user_id = 0;

//	cout << lastAddrID << endl;
//
//start user contraction
	long int txSize = AT.size();
	for(long int r = 0; r < txSize;r++){ 				// search through all the txs
		vli addrStack;
		if(AT[r].r_flag == false && AT[r].txIn == true){
			addrTXrep tmpTX = AT[r];
			long int currentTXID = tmpTX.txID;
			current_user_id++;							//increase the user_id
			cout << current_user_id << endl;

			//Go through consecutive input txin
			do{
				AT[r].r_flag = true;					//row visited
				cout << "TXIN = " << AT[r].txID << " addrID = " << AT[r].addrID << " got Current User ID = " << current_user_id << endl;
				addrStack.push_back(tmpTX.addrID);		//push the address of the tx
				userID[tmpTX.addrID] = current_user_id;
				GotUserID[tmpTX.addrID] = true;
				if(AT[r+1].txIn == true){
					cout << "Next Input TX." << endl;
					r++;
					tmpTX = AT[r];
				}else{
					cout << "break" << endl;
					break;
				}
			}while(tmpTX.txID == currentTXID);

			for(long int s=r+1; s < txSize; s++){  // search through all other input transactions
//				cout << "For IN TX: searching from pos " << s << endl;
				if(AT[s].r_flag == false && AT[s].txIn == true){
					//cout << "TXIN found" << endl;
					tmpTX = AT[s];
					currentTXID = AT[s].txID;

					long int txInStartPos = s;
					int cnt = 0;
					//Go through all the consecutive txin s' from s~ and see if at least one address matches with any one address of the stack
					do{
						if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) != addrStack.end()){ //find whether address exists in address stack
							cnt++;
							cout << "Address Matched. Count = " << cnt << "times." << endl;
						}
						if(AT[s+1].txIn == true){
							s++;
							tmpTX = AT[s];
						}else{
							break;
						}
					}while(tmpTX.txID == currentTXID);

					if(cnt != 0){  //if atleast one address matches, all these txin addresses are actually owned by the current user
						for(long int k = txInStartPos; k <= s;k++){
							cout << "Giving all address ids userid " << current_user_id << " from txin pos=" << txInStartPos << endl;
							tmpTX = AT[k];
							//push addresses if already not exists
							if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) == addrStack.end()){
								cout << "Push input address id = " << tmpTX.addrID << " into addrStack." << endl;
								cout << "Address got Current User ID = " << current_user_id << endl;
								userID[tmpTX.addrID] = current_user_id;
								GotUserID[tmpTX.addrID] = true;
								addrStack.push_back(tmpTX.addrID);
							}
							AT[k].r_flag = true;  //make it visited
						}
					}
				}//endif
			}//endfor
			cout << "clearing the address stack(Input addr)." << addrStack.size() <<  endl;
			addrStack.clear();//clear the address stack as we have searched the whole file
		}//endif
		/*// for output addresses in the output txs after consecutive input txs
		else if(AT[r].r_flag == false && AT[r].txIn== false){
			addrTXrep tmpTX = AT[r];
			if(GotUserID[tmpTX.addrID] == false){  					// if user id for this output address not yet determined
				long int currentTXID = tmpTX.txID;
				////????? determine whether change address or not , if change address don't
				current_user_id++;									//increase the user_id				cout << "Output addrID = " << tmpTX.addrID << " Candidate for new userID. Id incremented to " << current_user_id << endl;
				AT[r].r_flag = true;								//row visited
				addrStack.push_back(tmpTX.addrID);					//push the address of the tx
				userID[tmpTX.addrID] = current_user_id;
				cout << "New Output address. Received user id " << current_user_id << endl;
				GotUserID[tmpTX.addrID] = true;


				for(long int s=r+1; s < txSize; s++){  // search through all other input transactions to match address
//					cout << "For Out TX: searching from pos " << s << endl;
					if(AT[s].r_flag == false && AT[s].txIn == true){
//						cout << "Entered" << endl;
						tmpTX = AT[s];
						currentTXID = AT[s].txID;

						int cnt = 0;
						long int txOutStartPos = s;
						//Go through all the consecutive txin s' from r+1~ and see if at least one address matches with any one address of the stack
						do{
							if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) != addrStack.end()){ //find whether address exists in address stack
								cnt++;
							}
							if(AT[s+1].txIn == true){
								s++;
								tmpTX = AT[s];

							}else{
								break;
							}
						}while(tmpTX.txID == currentTXID);

						if(cnt != 0){  //if atleast one address matches, all these txin addresses are actually owned by the current user
							cout << "Output Address Matched. Count = " << cnt << "times." << endl;
							for(long int k = txOutStartPos; k <= s;k++){
								cout << "Giving all address ids userid(output) " << current_user_id << " from txin pos=" << txOutStartPos << endl;
								tmpTX = AT[k];
								//push addresses if already not exists
								if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) == addrStack.end()){
									cout << "Push output address id = " << tmpTX.addrID << " into addrStack." << endl;
									cout << "Address got Current User ID = " << current_user_id << endl;
									userID[tmpTX.addrID] = current_user_id;
									GotUserID[tmpTX.addrID] = true;
									addrStack.push_back(tmpTX.addrID);
								}
								AT[k].r_flag = true;  //make it visited
							}
						}
					}//endif
				}//endfor
				cout << "clearing the address stack(Output addr). of size " << addrStack.size() <<  endl;
				addrStack.clear(); //clear the address stack as we have searched the whole file
			}//endif
			else{
				cout << "This output address already got user id." << endl;
			}
		}*/
	}

	tr(userID,u){
		useridFileName << u->first << "\t" << u->second << endl;
	}
}


//	long int addrID,lastAddrID;
//	string addr;
//	addrFileName >> addrID;
//	while(addrFileName >> addrID >> addr){
//	}
//	lastAddrID = addrID;
//
//	//start contraction
//	GotUserID = vector<bool>(lastAddrID+1,false);
//	userID.push_back(0);//userID.size() is the current userID
//
//	for(long int A = 1; A <= lastAddrID;A++ ){
//		if(GotUserID[A] == false){ // If userid not determined yet
//			userID[A] = userID.size();
//			recursiveIdentify(A);
//		}
//	}

void recursiveIdentify(long int A){
	//Find all the tx associated with this address
		vector<long int> tx_A_id,row_id;
		long int txSize = AT.size();
		for(long int r = 0; r < txSize;r++){ // search through each row in AT
			addrTXrep tmp = AT[r];
			if(tmp.r_flag == false){  // if that row is not visited yet
				if(tmp.txIn == true && tmp.addrID == A ){  // if this is an input tx and address id of tx match with Address A
					tx_A_id.push_back(tmp.txID);   // push tx id associated with A
				}
			}
		}

		long int tx_A_size = tx_A_id.size();
		for(long int t=0; t <= tx_A_size; t++){ // all tx associated with A
			long int txID = tx_A_id[t];
			addrTXrep tmpID = AT[txID];
			if(tmpID.txIn == true){  // if this transaction is an input transaction

			}
		}

		tx_A_id.clear();
}
