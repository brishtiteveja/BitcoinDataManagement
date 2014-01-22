/*
 * IdentifyBitcoinUserNew.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: zehadyzbdullahkhan
 */

#include "IdentifyBitcoinUserNew.h"


void IdentifyBitcoinUserNew::IdentifyBTCUser(){
	ifstream txFileName;
	txFileName.open(string(BITCOINPROCESSEDPATH + "tx.txt").c_str(),ifstream::in);
	ifstream txInFileName;
	txInFileName.open(string(BITCOINPROCESSEDPATH + "txin.txt").c_str(),ifstream::in);
	ifstream txOutFileName;
	txOutFileName.open(string(BITCOINPROCESSEDPATH + "txoutn.txt").c_str(),ifstream::in);
	ifstream addrFileName;
	addrFileName.open(string(BITCOINPROCESSEDPATH + "addresses.txt").c_str(),ifstream::in);
	ifstream ATInFileName;
	//	ATInFileName.open(string(MAC_PATH + "AT.rtf").c_str(),ifstream::in);

	//	ofstream ATOutFileName;
	//	ATOutFileName.open(string(MAC_PATH+"AT.rtf").c_str(),ofstream::out);

	ofstream userIDFileName;
	userIDFileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/useridnew3.txt").c_str(),ofstream::out);

	ofstream userIDPreFileName;
	userIDPreFileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/useridPre3.txt").c_str(),ofstream::out);

	ofstream userIDInOnlyFileName;
	userIDInOnlyFileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/useridtxin.txt").c_str(),ofstream::out);

	mlili userMap;

	long int lasttxInID = 0;
//	int lastAddrID = 0;
	long int lastUserID = 0;
//	int a,b;

	///Find last txin id
//	if(txInPrevFile.is_open()){
//		while(txInFileName >> txInID >> addrID >> value && !txInPrevFile.eof()){
//		}
//		cout << "Last TXIN " << txInID << " addrID = " << addrID << " value = " << value << endl;
//	}
	///find last user id

	//Generation user id
	userMap[0] = 0;
	vli addrStack;
	long int txInID,addrID,currentUserID;
	double value;

	currentUserID = lastUserID;
	txInFileName >> txInID >> addrID >> value;
//	cout << "TXIN " << txInID << " addrID = " << addrID << " value = " << value << endl;
//	addrStack.push_back(addrID);

	lasttxInID = txInID;
//	int c = 0;

	do{
//		c++;
//		if(c == 100000)
//			break;

		if(txInFileName.eof()){
//			cout << "End of tx file." << endl;
			break;
		}
		txInFileName >> txInID >> addrID >> value;
		cout << "TXIN " << txInID << " addrID = " << addrID << " value = " << value << endl;

		if(txInID == lasttxInID){
//		 	cout << "Address in the same input tx. Addr = " << addrID << endl;
			addrStack.push_back(addrID);
		}else{
			vli uIDvec;
			unsigned int GotNoUserID,GotUserID;
			GotNoUserID= 0;
			GotUserID = 0;

			long int userID;
			tr(addrStack,a){
				if(userMap[*a] == 0){
//					cout << "Address got no user id." << endl;
					GotNoUserID++;
				}else{
//					cout << "Address got user id " << userMap[*a] << endl;
					if(find(uIDvec.begin(),uIDvec.end(),userMap[*a]) == uIDvec.end()){ // inserting unique user ids only
						uIDvec.push_back(userMap[*a]);
						userID = userMap[*a];
//						cout << "userID " << userID << " inserted into uIDvec." << endl;
					}
					GotUserID++;
				}
			}

			if(GotNoUserID == addrStack.size()){
//				cout << "No address got any user id " << endl;
				currentUserID++;
//				cout << "Set all address current user id " << currentUserID << endl;
				tr(addrStack,a){
					userMap[*a] = currentUserID;
				}
			}else if(GotUserID == 1){
				tr(addrStack,a){
					userMap[*a] = userID;
				}
			}else{	// more than one address got user id
				cout << "more than one address got user id" << endl;
				tr(uIDvec,u){ //find minimum user id
					if(*u < userID){
//						cout << "smaller user id = " << *u << endl;
						userID = *u;
					}
				}

//				cout << "Set minimum userID = " << userID << endl;
				tr(addrStack,a){
					userMap[*a] = userID;
				}

				//Give them the user id
				tr(uIDvec,u){
					if(*u != userID ){
//						cout << *u << " will receive user id "<< userID << endl;
						tr(userMap,it){
							//cout << "Before userID = " << it->second << endl;
							if(it->second == *u)
								it->second = userID;
							//cout << "After userID = " << it->first << endl;
						}
					}
				}
			}

//			cout << "Number of address in this input tx : " << addrStack.size() << endl;
//			cout << "Clearing address stack." << endl;
			addrStack.clear();
			lasttxInID = txInID;
			if(addrID != 0)
				addrStack.push_back(addrID);
			cout << "Starting new input tx. txInID = " << txInID << endl;
		}
	}while(1);

	tr(userMap,u){
		userIDInOnlyFileName << u->first << "\t" << u->second << endl;
	}

	long int txOutID;

	while(txOutFileName >> txOutID >> addrID >> value && !txOutFileName.eof()){
		cout << "TXOUT " << txOutID << " addrID = " << addrID << " value = " << value << endl;
		if(userMap[addrID] == 0){
			currentUserID++;
			userMap[addrID] = currentUserID;
		}
	}

	// respacing the user ids, removing gaps
	vli uID;

	tr(userMap,u){
		userIDPreFileName << u->first << "\t" << u->second << endl;

//		if(find(uID.begin(),uID.end(),u->second) == uID.end())  //pushing unique user ids
//			uID.push_back(u->second);
	}


//	sort(uID.begin(),uID.end()); //sorting the unique userids of the
//
//	mlili uIDB;
//	long int id = 0;
//	tr(uID,u){
//		uIDB[*u] = id++;
//	}
//
//	tr(userMap,u){
//		userIDFileName << u->first << "\t" << uIDB[u->second] << endl;
//	}

	txFileName.close();
	txInFileName.close();
	txOutFileName.close();
	addrFileName.close();
	userIDFileName.close();
	userIDPreFileName.close();
	userIDInOnlyFileName.close();
}
