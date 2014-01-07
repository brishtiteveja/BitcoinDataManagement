/*
 * IdentifyBitcoinUserEfficient.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: zehadyzbdullahkhan
 */

#include "IdentifyBitcoinUserEfficient.h"

void IdentifyBitcoinUserEfficient::identifyBitcoinUser(){
		ifstream txFileName;
		txFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/tx.txt").c_str(),ifstream::in);
		ifstream txInFileName;
		txInFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/txin.txt").c_str(),ifstream::in);
		ifstream txOutFileName;
		txOutFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/txout.txt").c_str(),ifstream::in);
		ifstream addrFileName;
		addrFileName.open(string(MAC_BITCOIN_PATH + "bitcoin dataset main/addresses.txt").c_str(),ifstream::in);
		ifstream ATInFileName;
		//Get already existing user ids
		ifstream useridFileName;
		useridFileName.open(string(MAC_PATH+"userid2.txt").c_str(),ifstream::in);


		long int txInID,addrID,value;
	//	long int stopper = 0;

		//populate the AT vector with transactions and addresses
		while(txInFileName >> txInID >> addrID >> value){
			addrTXrep tmp;
			tmp.txID = txInID;
			tmp.addrID = addrID;
			tmp.value = value;
			tmp.r_flag = false;
			AT.push_back(tmp);
		}

		long int lastAddrID;
		string addr;
		addrFileName >> addrID;
		//Find total address id
		while(addrFileName >> addrID >> addr){
		}
		lastAddrID = addrID;

		GotUserID = vector<bool>(lastAddrID+1,false);

		userID[0] = 0;
		GotUserID[0] = true;
		long int current_user_id = 0;

//		long int addr_id, user_id;
//		//if partial userid contraction file exists
//		while(!useridFileName.eof() && useridFileName >> addr_id >> user_id){
//			userID[addr_id] = user_id;
//			current_user_id++;
//			GotUserID[addr_id] = true;
//		}

		//start user contraction
		long int txInSize = AT.size();
		for(long int r = 0; r < txInSize;r++){ 				// search through all the txs
				vli addrStack;
				if(AT[r].r_flag == false){
					addrTXrep tmpTX = AT[r];
					long int currentTXID = tmpTX.txID;
					current_user_id++;							//increase the user_id
					cout << current_user_id << endl;

					//Go through consecutive input txin
					do{
						AT[r].r_flag = true;					//row visited
//						cout << "TXIN = " << AT[r].txID << " addrID = " << AT[r].addrID << " got Current User ID = " << current_user_id << endl;
						addrStack.push_back(tmpTX.addrID);		//push the address of the tx
						userID[tmpTX.addrID] = current_user_id;
						GotUserID[tmpTX.addrID] = true;
						if(AT[r+1].txID == currentTXID){
//							cout << "Next Address in the same Input TX." << endl;
							r++;
							tmpTX = AT[r];
						}else{
							break;
						}
					}while(tmpTX.txID == currentTXID);

					for(long int s=r+1; s < txInSize; s++){  // search through all other input transactions
		//				cout << "For IN TX: searching from pos " << s << endl;
						if(AT[s].r_flag == false){
							//cout << "TXIN found" << endl;
							tmpTX = AT[s];
							currentTXID = AT[s].txID;

							long int txInStartPos = s;
							int cnt = 0;
							//Go through all the consecutive txin s' from s~ and see if at least one address matches with any one address of the stack
							do{
								if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) != addrStack.end()){ //find whether address exists in address stack
									cnt++;
//									cout << "Address Matched. Count = " << cnt << "times." << endl;
								}
								if(AT[s+1].txID == currentTXID){
									s++;
									tmpTX = AT[s];
								}else{
									break;
								}
							}while(tmpTX.txID == currentTXID);

							if(cnt != 0){  //if atleast one address matches, all these txin addresses are actually owned by the current user
								for(long int k = txInStartPos; k <= s;k++){
//									cout << "Giving all address ids userid " << current_user_id << " from txin pos=" << txInStartPos << endl;
									tmpTX = AT[k];
									//push addresses if already not exists
									if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) == addrStack.end()){
//										cout << "Push input address id = " << tmpTX.addrID << " into addrStack." << endl;
//										cout << "Address got Current User ID = " << current_user_id << endl;
										userID[tmpTX.addrID] = current_user_id;
										GotUserID[tmpTX.addrID] = true;
										addrStack.push_back(tmpTX.addrID);
									}
									AT[k].r_flag = true;  //make it visited
								}
							}
						}//endif
					}//endfor
//					cout << "clearing the address stack(Input addr)." << addrStack.size() <<  endl;
					addrStack.clear();//clear the address stack as we have searched the whole file
				}//endif
			}


		while(txOutFileName >> txInID >> addrID >> value){
			addrTXrep tmp;
			tmp.txID = txInID;
			tmp.addrID = addrID;
			tmp.value = value;
			tmp.r_flag = false;
			break;
			ATT.push_back(tmp);
		}

		long int txOutSize = ATT.size();
		// for output addresses in the output txs after consecutive input txs
		for(long int r = 0; r < txOutSize;r++){
			addrTXrep tmpTX = AT[r];
			if(GotUserID[tmpTX.addrID] == false){  					// if user id for this output address not yet determined
//				long int currentTXID = tmpTX.txID;
				////????? determine whether change address or not , if change address don't
				current_user_id++;	//increase the user_id				cout << "Output addrID = " << tmpTX.addrID << " Candidate for new userID. Id incremented to " << current_user_id << endl;
				userID[tmpTX.addrID] = current_user_id;
				cout << "New Output address. Received user id " << current_user_id << endl;
				GotUserID[tmpTX.addrID] = true;
			}
			else{
				cout << "This output address already got user id." << endl;
			}
		}

		ofstream useridOutFileName;
		useridOutFileName.open(string(MAC_PATH+"userid2.txt").c_str(),ofstream::out);
		tr(userID,u){
			useridOutFileName << u->first << "\t" << u->second << endl;
		}

}


