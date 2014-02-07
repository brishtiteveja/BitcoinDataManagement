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
//		long int txInSize = AT.size();

		for(list<addrTXrep>::iterator it=AT.begin(); it != AT.end();it++){ 				// search through all the tx ins
					vli addrStack;
					addrTXrep tmpTX = *it;
					long int currentTXID = tmpTX.txID;
					current_user_id++;							//increase the user_id
					cout << current_user_id << endl;

					//Go through consecutive input txins
					do{
						cout << "TXIN = " << it->txID << " addrID = " << it->addrID << " got Current User ID = " << current_user_id << endl;
						addrStack.push_back(tmpTX.addrID);		//push the address of the tx
						userID[tmpTX.addrID] = current_user_id;
						GotUserID[tmpTX.addrID] = true;
						it = AT.erase(it);
						if(it->txID == currentTXID){
							cout << "Next Address in the same Input TX." << endl;
							tmpTX = *it;
						}else{
							break;
						}
					}while(tmpTX.txID == currentTXID);

					for(list<addrTXrep>::iterator it2=it; it2 != AT.end();){  // search through all other input transactions
		//					cout << "For IN TX: searching from pos " << s << endl;
//							cout << "TXIN found" << endl;
							tmpTX = *it2;
							currentTXID = it2->txID;

							list<addrTXrep>::iterator txInStartPos = it2;
							int cnt = 0;
							//Go through all the consecutive txin s' from s~ and see if at least one address matches with any one address of the stack
							do{
								if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) != addrStack.end()){ //find whether address exists in address stack
									cnt++;
									cout << "Address Matched. Count = " << cnt << "times." << endl;
								}
								it2++;
								if(it2->txID == currentTXID){
									tmpTX = *it2;
								}else{
									break;
								}
							}while(tmpTX.txID == currentTXID);

							if(cnt != 0){  //if atleast one address matches, all these txin addresses are actually owned by the current user
								list<addrTXrep>::iterator k;
								cout << "Giving non determined address ids userid " << current_user_id << endl ;//<< " from txin pos=" << txInStartPos  << endl;
								for(k = txInStartPos;k !=it2 ;){
									tmpTX = *k;
									//push addresses if already not exists
									if(find(addrStack.begin(),addrStack.end(),tmpTX.addrID) == addrStack.end()){
										cout << "Push input address id = " << tmpTX.addrID << " into addrStack." << endl;
										cout << "Address got Current User ID = " << current_user_id << endl;
										userID[tmpTX.addrID] = current_user_id;
										GotUserID[tmpTX.addrID] = true;
										addrStack.push_back(tmpTX.addrID);
									}else{
										cout << "This address id already got user id." << endl;
									}
									k = AT.erase(k);
								}
								if(it == txInStartPos){
									it = it2;
								}
							}
					}//endfor
//					it--; //getting back
					cout << "clearing the address stack(Input addr)." << addrStack.size() <<  endl;
					addrStack.clear();//clear the address stack as we have searched the whole file
					cout << "current size of the txin list: " << AT.size() << endl;
			}


//		while(txOutFileName >> txInID >> addrID >> value){
//			addrTXrep tmp;
//			tmp.txID = txInID;
//			tmp.addrID = addrID;
//			tmp.value = value;
//			tmp.r_flag = false;
//			break;
//			ATT.push_back(tmp);
//		}
//
//		long int txOutSize = ATT.size();
//		// for output addresses in the output txs after consecutive input txs
//		for(long int r = 0; r < txOutSize;r++){
//			addrTXrep tmpTX = AT[r];
//			if(GotUserID[tmpTX.addrID] == false){  					// if user id for this output address not yet determined
////				long int currentTXID = tmpTX.txID;
//				////????? determine whether change address or not , if change address don't
//				current_user_id++;	//increase the user_id				cout << "Output addrID = " << tmpTX.addrID << " Candidate for new userID. Id incremented to " << current_user_id << endl;
//				userID[tmpTX.addrID] = current_user_id;
//				cout << "New Output address. Received user id " << current_user_id << endl;
//				GotUserID[tmpTX.addrID] = true;
//			}
//			else{
//				cout << "This output address already got user id." << endl;
//			}
//		}

		ofstream useridOutFileName;
		useridOutFileName.open(string(MAC_PATH+"userid2.txt").c_str(),ofstream::out);
		tr(userID,u){
			useridOutFileName << u->first << "\t" << u->second << endl;
		}

}


