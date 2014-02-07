/*
 * IdentifyBitcoinUserNew.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: zehadyzbdullahkhan
 */

#include "IdentifyBitcoinUserNew.h"

int level = 0;

long int IdentifyBitcoinUserNew::mergeUserID(long int u){
	if(sameUMap[u].size() == 0){
		cout << "Reached final." << endl;
		return u;
	}else{
		cout << "level " << level++ << " userid = " << u <<  endl;
		return mergeUserID(*sameUMap[u].begin());
	}

}

void IdentifyBitcoinUserNew::IdentifyBTCUser(){
	ifstream txFileName;
	txFileName.open(string(BITCOINPROCESSEDPATH + "tx.txt").c_str(),ifstream::in);
	ifstream txInFileName;
	txInFileName.open(string(BITCOINPROCESSEDPATH + "txin.txt").c_str(),ifstream::in);
	ifstream txOutFileName;
	txOutFileName.open(string(BITCOINPROCESSEDPATH + "txoutn.txt").c_str(),ifstream::in);
	ifstream addrFileName;
	addrFileName.open(string(BITCOINPROCESSEDPATH + "addresses.txt").c_str(),ifstream::in);
	ifstream degreeFileName;
	degreeFileName.open(string(MAC_PATH + "computed/degree.txt").c_str(),ifstream::in);


	//ofstream userIDInOnlyFileName;
	//userIDInOnlyFileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/new/useridtxin.txt").c_str(),ofstream::out);

	ofstream userIDH1FileName;
	userIDH1FileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/useridh1.txt").c_str(),ofstream::out);

	ofstream userIDH2FileName;
	userIDH2FileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/useridh2.txt").c_str(),ofstream::out);




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

/*
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
 	 	 	if(addrID != 0)
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

			if(addrStack.size() != 0 && GotNoUserID == addrStack.size()){
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
			}else if(GotUserID > 1){	// more than one address got user id
				cout << "more than one address in the input transaction got user id" << endl;
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

//				tr(uIDvec,u){
//					if(*u != userID ){
////						cout << *u << " will receive user id "<< userID << endl;
//						tr(userMap,it){
//							//cout << "Before userID = " << it->second << endl;
//							if(it->second == *u)
//								it->second = userID;
//							//cout << "After userID = " << it->first << endl;
//						}
//					}
//				}

				//push those users in the same user list
				tr(uIDvec,u){
					if(*u != userID){
						sameUMap[userID].push_back(*u);
						//sorting the list
						sameUMap[userID].sort();
						sameUMap[userID].unique();
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
	cout << sameUMap.size() << endl;

	 // Creation of same user map and initial txin user map
	ofstream sameUMapFileName;
	sameUMapFileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/new/sameusermap.txt").c_str(),ofstream::out);
	tr(sameUMap,u){
		sameUMapFileName << u->first << endl;
		tr(u->second,it){
			sameUMapFileName << "\t" << *it;
		}
		sameUMapFileName << endl;
	}

	ofstream uTmpFileName;
	uTmpFileName.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/new/usermapTxIntmp.txt").c_str(),ofstream::out);

	tr(userMap,u){
		uTmpFileName << u->first << "\t" << u->second << endl;
	}
*/

	long int ai,ui;
	ifstream inf(string(BITCOINPROCESSEDPATH+"computed/user contraction/usermapTxIntmp.txt").c_str());

	while(inf >> ai >> ui){
		//cout << ai << "\t" << ui << endl;
		userMap[ai] = ui;
	}
	cout << "Got user map." << endl;

	ifstream sameUMapInFile;
	sameUMapInFile.open(string(BITCOINPROCESSEDPATH+"computed/user contraction/sameusermap.txt").c_str(),ifstream::in);

	string s;

	mlili u2u;
	while(getline(sameUMapInFile,s)){
		istringstream is(s);

		is >> ui;
		long int uid = ui;

		u2u[ui] = uid;

		getline(sameUMapInFile,s);
		istringstream iss(s);
		while(iss >> ui){
			sameUMap[uid].push_back(ui);

			if(u2u[ui] == 0 || u2u[ui] > uid ){
				u2u[ui] = uid;
			}
		}
	}

	cout << "Got same user map." << endl;

	cout << "Start updating user map using same user map." << endl;

	// renewing user map using the sameusermap

	list<long int> users;
	tr(userMap,u){
		users.push_back(u->second);

		if(u2u[u->second] == 0){
//			cout << "For address = " << u->first << " no update." << endl;
		}
		else if(u->second != 0 && u2u[u->second] != 0){
			if(u2u[u->second] != u->second){
//				cout << "For address = " << u->first << " update user id from " << u->second << " to " << u2u[u->second]<<  endl;
				//update user map
				u->second = u2u[u->second];
			}
		}
//		userIDInOnlyFileName << u->first << "\t" << u->second << endl;
	}

	// making user ids consecutive
	users.unique();
	users.sort();

	mlili consecUserMap;
	int idx = 0;
	tr(users,u){
		if(consecUserMap[*u] == 0)
			consecUserMap[*u] = idx++;
	}
	int umax = idx - 1;

	tr(userMap,u){
		u->second = consecUserMap[u->second];
	}

	cout << "Start txout user mapping" << endl;

	long int txOutID;

	int cn = 0;
	currentUserID = umax;
	while(txOutFileName >> txOutID >> addrID >> value && !txOutFileName.eof()){
		//cout << "TXOUT " << txOutID << " addrID = " << addrID << " value = " << value << endl;
		if(userMap[addrID] == 0){
			cn++;
			currentUserID++;
			userMap[addrID] = currentUserID;
		}else{
			//cout << "Already Got" << endl;
		}
	}
	cout << "Total txout address added  = " << cn << endl;
	cout << "Total number of unique users = " << currentUserID << endl;

	tr(userMap,u){
		userIDH1FileName << u->first << "\t" << u->second << endl;
	}

	cout << "Final userMap. (Without Heuristic 2)" << endl;

	txInFileName.close();
	txOutFileName.close();
	txInFileName.open(string(BITCOINPROCESSEDPATH + "txin.txt").c_str(),ifstream::in);
	txOutFileName.open(string(BITCOINPROCESSEDPATH + "txoutn.txt").c_str(),ifstream::in);
/***********************************************************************/
	//Heuristic 2
	// if in a non-coin generation transaction in all txout addresses there is only one out address with indegree 1 but outdegree 0 and
	// there is no self-change address, then that out address is also owned by the same user
	mlili inDegMap;
	mlili outDegMap;

	long int indeg, outdeg;
	while(degreeFileName >> addrID >> indeg >> outdeg){
		inDegMap[addrID] = indeg;
		outDegMap[addrID] = outdeg;
	}


	long int txID;
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

		bool is_generationTX = false;
		long int inUserID;

		int cnt = 0;

		vli inAddrStack;
		if(txInFileName.is_open()){
			while(n_inputs != 0 && !txInFileName.eof()){
				if(MovePastFlagIn == false){
					txInFileName >> txInID >> addrID >> value;
					inAddrStack.push_back(addrID);
				}else{
					MovePastFlagIn = false;
				}

				if(addrID == 0)
					is_generationTX = true;

				if(txInID == txID){
//					cout <<"txIn = " << txInID << " " << addrID << " " << value << endl;
					cnt++;
				}
				if(cnt == n_inputs){
					//Getting the input transaction user
					inUserID = userMap[addrID];
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
		bool exist_self_change = false;
		vli outAddrStack;
		if(txOutFileName.is_open()){
			while(n_outputs != 0  && !txOutFileName.eof()){
				if(MovePastFlagOut == false){
					txOutFileName >> txOutID >> addrID >> value;
					outAddrStack.push_back(addrID);
					if(find(inAddrStack.begin(),inAddrStack.end(),addrID) != inAddrStack.end()){
						exist_self_change = true;
					}
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

		//identify change address
		if(is_generationTX == false && exist_self_change == false){
			int c = 0;
			int id;
			tr(outAddrStack,it){
				if(inDegMap[*it] == 1){
					c++;
					id = it - outAddrStack.begin();
				}
				if(c > 1){ // Can't identify as the change address
					break;
				}
			}

			if(c == 1){  // So then
				cout << "Change Address found" << endl;
				userMap[outAddrStack[id]] = inUserID;
			}
		}


		inAddrStack.clear(); //clearing the input address list
		outAddrStack.clear();
//		stopper++;
//		if(stopper == 10000)
//			break;
	}

	users.clear();
	tr(userMap,u){
		users.push_back(u->second);
	}

	// making user ids consecutive
	users.unique();
	users.sort();

	mlili consecUserMap2;
	idx = 0;
	tr(users,u){
		if(consecUserMap2[*u] == 0)
			consecUserMap2[*u] = idx++;
	}
	umax = idx - 1;

	tr(userMap,u){
		u->second = consecUserMap2[u->second];
		userIDH2FileName << u->first << "\t" << u->second << endl;
	}

	cout << "Total number of unique users = " << umax << endl;
	cout << "Final userMap. (With Heuristic 2)" << endl;


	txFileName.close();
	txInFileName.close();
	txOutFileName.close();
	addrFileName.close();
	degreeFileName.close();
	userIDH1FileName.close();
	userIDH2FileName.close();
	//	userIDInOnlyFileName.close();
}

