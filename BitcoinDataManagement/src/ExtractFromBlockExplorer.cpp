#include "CommonHeaders.h"



string numToString(int num){
	ostringstream convert;
	convert << num;

	//hello
	string res = convert.str();
	return res;
}

int stringToInt(string s){
	return atoi(s.c_str());
}

double stringToDouble(string s){
	return atof(s.c_str());
}


//2013-12-25 08:59:39
time_t convertToEpochtime(string realTime){
	struct tm timeInfo;
	timeInfo.tm_year = atoi(realTime.substr(0,4).c_str()) - 1900;
	timeInfo.tm_mon = atoi(realTime.substr(5,2).c_str()) - 1;
	timeInfo.tm_mday = atoi(realTime.substr(8,2).c_str());
	timeInfo.tm_hour = atoi(realTime.substr(11,2).c_str());
	timeInfo.tm_min = atoi(realTime.substr(14,2).c_str());
	timeInfo.tm_sec = atoi(realTime.substr(17,2).c_str());
	//cout << timeInfo.tm_year << " " << timeInfo.tm_mon << " " << timeInfo.tm_mday << " " << timeInfo.tm_hour << " " << timeInfo.tm_min << " " << timeInfo.tm_sec << endl;
	time_t epochTime = mktime(&timeInfo);
	//cout << epochTime << endl;
	return epochTime;
}

struct tm* convertToUnixtime(time_t epochTime){
	struct tm *t = localtime(&epochTime);
	t -> tm_year += 1900;
	t -> tm_mon  += 1;
	return t;
}


//crashed once in blkID = 219826 , recompute from here
void runExtractor(){
	string outfileName;
	int blockIDFrom = 265000;
	int blockIDTo = 265002;
	msi addrMap;  //address map , key: address , value: address id
//	mii userMap;
//	mii indegree,outdegree;
//	mid addrBalanceMap;
//	mmii addrUserMap;
//	mmii userAddrMap;

		//Get last BlockID and transaction ID of Rich Gets Richer Data
//	ifstream txPrevFile("C:/Users/ananda/Downloads/Bitcoin/Bitcoin_Data/tx.txt");
//	ifstream addrPrevFile("C:/Users/ananda/Downloads/Bitcoin/Bitcoin_Data/addresses.txt");
//	ifstream degPrevFile("C:/Users/ananda/Downloads/Bitcoin/bitcoin_dataset/bitcoin_computed/degree.txt");
//	ifstream balancePrevFile("C:/Users/ananda/Downloads/Bitcoin/bitcoin_dataset/bitcoin_computed/balances.txt");
//	ifstream userPrevFile("C:/Users/ananda/Downloads/Bitcoin/Blocks/userid.txt");

	int lastTXID = 0;
	int lastBlkID = blockIDFrom;//0;
	int lastAddrID = 0;
//	int lastUserID = 0;
//	int a,b;

//	if(txPrevFile.is_open()){
//		while(txPrevFile >> lastTXID >> lastBlkID >> a >> b && !txPrevFile.eof()){
//		}
//		cout << "Last TX ID: " << lastTXID + 1 << " lastBlkID: " << lastBlkID + 1 << endl;
//	}
//
//
//	addrMap["0"] = 0; //Generation address
//	if(addrPrevFile.is_open()){
//		string tmpAddr;
//		while(addrPrevFile >> lastAddrID >> tmpAddr && !addrPrevFile.eof()){
//				addrMap[tmpAddr] = lastAddrID;
//		}
//		cout << "Last Addr ID: " << lastAddrID << endl;
//	}

//	if(degPrevFile.is_open()){
//		int indeg,outdeg,addr_id;
//		while(degPrevFile >> addr_id >> indeg >> outdeg  && !degPrevFile.eof()){
//				indegree[addr_id]  = indeg;
//				outdegree[addr_id] = outdeg;
//		}
//	}


//	if(balancePrevFile.is_open()){
//		int addr_id;
//		double tmpBalance;
//		while(balancePrevFile >> addr_id >> tmpBalance){
//				addrBalanceMap[addr_id] = tmpBalance;
//		}
//	}

//	userMap[0] = 0;  // Generation user id
//	if(userPrevFile.is_open()){
//		int addr_id;
//		while(userPrevFile >> addr_id >> lastUserID){  //creating the maps
//			userMap[addr_id] = lastUserID;
//			addrUserMap.insert(pair<int,int>(addr_id,lastUserID));   // Multimap with (addressID,userID) pair
//			userAddrMap.insert(pair<int,int>(lastUserID,addr_id));   // Multimap with (userID,addressID) pair
//		}
//	}

	int blockID = blockIDFrom = lastBlkID; //lastBlockID
	int txID = lastTXID; //lastTXID
	int addrID = lastAddrID; // lastAddrID
//	int userID = lastUserID; // last user id

//	txPrevFile.close();
//	addrPrevFile.close();
//	degPrevFile.close();
//	balancePrevFile.close();
//	userPrevFile.close();

	//database file
/////////For Macintosh
	ofstream blkInfoFileName;
	blkInfoFileName.open(string(MAC_PATH + "blockinfo.txt").c_str(),ofstream::out);
	ofstream blkHashFileName;
	blkHashFileName.open(string(MAC_PATH + "blockhash.txt").c_str(),ofstream::out);
	ofstream txFileName;
	txFileName.open(string(MAC_PATH + "tx.txt").c_str(),ofstream::out);
	ofstream txinFileName;
	txinFileName.open(string(MAC_PATH + "txin.txt").c_str(),ofstream::out);
	ofstream txoutFileName;
	txoutFileName.open(string(MAC_PATH + "txout.txt").c_str(),ofstream::out);
	ofstream txedgeFileName;
	txedgeFileName.open(string(MAC_PATH + "txedge.txt").c_str(),ofstream::out);
	ofstream txhashFileName;
	txhashFileName.open(string(MAC_PATH + "txhash.txt").c_str(),ofstream::out);
	ofstream txtimeFileName;
	txtimeFileName.open(string(MAC_PATH + "txtime.txt").c_str(),ofstream::out);
	ofstream addressFileName;
	addressFileName.open(string(MAC_PATH + "addresses.txt").c_str(),ofstream::out);

/////////For windows
//	ofstream blkInfoFileName;
//	blkInfoFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/blockinfo.txt",ofstream::out);
//	ofstream blkHashFileName;
//	blkHashFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/blockhash.txt",ofstream::out);
//	ofstream txFileName;
//	txFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/tx.txt",ofstream::out);
//	ofstream txinFileName;
//	txinFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/txin.txt",ofstream::out);
//	ofstream txoutFileName;
//	txoutFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/txout.txt",ofstream::out);
//	ofstream txedgeFileName;
//	txedgeFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/txedge.txt",ofstream::out);
//	ofstream txhashFileName;
//	txhashFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/txhash.txt",ofstream::out);
//	ofstream txtimeFileName;
//	txtimeFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/txtime.txt",ofstream::out);
//	ofstream addressFileName;
//	addressFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/addresses.txt",ofstream::out);


//	ofstream balanceFileName;
//	balanceFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/balance.txt",ofstream::app);
//	ofstream userIDFileName;
//	userIDFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinData/userid.txt",ofstream::app);
//	ofstream degreeFileName;
//	degreeFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/degree.txt",ofstream::app);

	//print generation address id
	addressFileName << 0 << "\t" << 0 << endl;

	while(blockID <= blockIDTo){
			//preparing the block file name to open
			ifstream ifs;
			//For Windows
//			string infileName("C:/Users/ananda/Downloads/Bitcoin/Blocks/Block");
			//For Mac
			string infileName(string(MAC_BLOCK_PATH + "Block").c_str());

			string tmp(numToString(blockID));

			infileName.append(tmp);
			infileName.append(".html");
//			cout << infileName << endl;
			ifs.open(infileName.c_str());
			string s("");

			if(ifs.is_open()){
				char ch;
				while(!ifs.eof() && ifs >> noskipws >> ch)
					s += ch;
			}else{
				cout << "No" << endl;
			}

			//processing the html
			if(ifs.is_open()){  //if block file is open
				string blkID;

				//scraping block id
				regex blkIDPattern(".+<h1>Block\\s([0-9]+)");
				smatch p;
				regex_search(s,p,blkIDPattern);
				blkID = p[1].str();
//				cout << "Block ID: " << blkID << endl;

				//scraping block hash
				string blkHash;
				regex hashPattern(".+<li>Hash.+?:.([^<]+?)</li>");
				regex_search(s,p,hashPattern);
				blkHash = p[1].str();
//				cout << "Block Hash: " << blkHash << endl;

				//scraping previous block hash
				string prevBlkHash;
				regex prevBlkHashPattern("<li>Previous.block.+?/block/[^>]+>([^<]+)<");
				regex_search(s,p,prevBlkHashPattern);
				prevBlkHash = p[1].str();
//				cout << "Previous Block Hash: " <<  prevBlkHash << endl;

				//scraping next block hash
				string nextBlkHash;
				regex nextBlkHashPattern("<li>Next.block.+?/block/[^>]+>([^<]+)<");
				regex_search(s,p,nextBlkHashPattern);
				nextBlkHash = p[1].str();
//				cout << "Next Block Hash: " <<  nextBlkHash << endl;

				//scaping block time
				string blkTime;
				regex timePattern(".+?<li>Time.+?:.([^<]+?)</li>");
				regex_search(s,p,timePattern);
				blkTime = p[1].str();
		//		time_t epoch = convertToEpochtime(blkTime);
		//		cout << "Block Time: " << blkTime << " " << epoch << endl;
		//		struct tm* t =  convertToUnixtime(epoch);
		//
		//		cout << t->tm_year << " " << t->tm_mon<< " " <<  t->tm_mday << endl;

				//scraping block difficulty
				string blkDifficulty;
				regex blkDifficultyPattern(".+?<li>Difficulty.+?</sup>:.([^(]+?)...Bits");
				regex_search(s,p,blkDifficultyPattern);
				blkDifficulty = p[1].str();
				//remove the spaces in blkDifficulty
				string tmp;
				for(int i=0; blkDifficulty[i]!='\0';i++){
					if(blkDifficulty[i] != ' ')
						tmp.push_back(blkDifficulty[i]);
				}
				tmp.push_back('\0');
				blkDifficulty = tmp;
//				cout << "Block Difficulty: " << blkDifficulty << endl;

				//scraping bits
				string blkBits;
				regex blkBitsPattern(".+?Bits.+?</sup>:.([^)]+).");
				regex_search(s,p,blkBitsPattern);
				blkBits = p[1].str();
//				cout << "Block bits: " << blkBits << endl;

				//scraping total block bitcoin
				string blkTotalBTC;
				regex blkTotalBTCPattern(".+?<li>Total BTC.+?</sup>:.([^(]+?)...</li>");
				regex_search(s,p,blkTotalBTCPattern);
				blkTotalBTC = p[1].str();
//				cout << "Total BTC in the block: " << blkTotalBTC << endl;

				//scraping block size
				string blkSize;
				regex blkSizePattern(".+?<li>Size.+?</sup>:.([^a-z]+).");
				regex_search(s,p,blkSizePattern);
				blkSize = p[1].str();
//				cout << "Block size in kilobytes: " << blkSize << endl;

				//scaraping Merkle root
				string blkMerkleRoot;
				regex blkMerkleRootPattern(".+?<li>Merkle.root.+?</sup>:.([^<]+?)</li>");
				regex_search(s,p,blkMerkleRootPattern);
				blkMerkleRoot = p[1].str();
//				cout << "Block Merkle Root: " << blkMerkleRoot<<endl;

				//scraping block nonce
				string blkNonce;
				regex blkNoncePattern(".+?<li>Nonce.+?</sup>:.([^<]+?)</li>");
				regex_search(s,p,blkNoncePattern);
				blkNonce = p[1].str();
//				cout << "Block Nonce: " << blkNonce << endl;

				//scraping number of transactions in the block;
				string blkTXNum;
				regex blkTXNumPattern("<li>Transactions.+?</sup>:.([^<]+?)</li>");
				regex_search(s,p,blkTXNumPattern);
				blkTXNum = p[1].str();
//				cout << "Total # transactions in the block: " << blkTXNum << endl;

				//------> write block info to the blockinfo.txt
				if(blkID == "")
						prevBlkHash = "";
				blkInfoFileName << blkID << "\t" << blkHash << "\t" << prevBlkHash
						<< "\t" << nextBlkHash << "\t" << blkTime << "\t" << blkDifficulty
						<< "\t" << blkBits << "\t" << blkTXNum << "\t" << blkTotalBTC
						<< "\t" << blkSize << "\t" << blkMerkleRoot << "\t" << blkNonce << endl;
				//------> write block hash info to the blockhash.txt
				blkHashFileName << blkID << "\t" << blkHash << "\t" << blkTime << "\t" << blkTXNum << endl;

				//match the tx table
				regex ex(".+<table class=\"txtable\">(.+)</table>.+");
				smatch m;
				//scraping transaction table
				regex_search(s,m,ex);

				//Scraping Each individual transaction
				regex e("<tr>\n<td>(.+?)</td>\n</tr>");
				smatch n;
				string ss(m[1]);
				bool gen = true;
				while(regex_search(ss,n,e)){
					//------> write to txtime.txt
					txtimeFileName << txID << "\t" << blkTime << endl;

					//n[1] holds each transaction, scrape from n[1]
					string txString = n[1].str();

					//scraping tx hash
					string txHash;
					regex txPattern("/tx/([\\S]+?)\\S>.+?</td><td>([\\S]+)</td><td>([\\S]+)</td>"
							".+?(<ul.+?</ul>).+?(<ul.+?</ul>)");
					smatch q;
					regex_search(txString,q,txPattern);
					txHash = q[1].str();

					//------> write to txhash.txt
					txhashFileName << txID << "\t" << txHash << endl;

					//scraping tx fee
					string txFee = q[2].str();

					//scraping tx Size
					string txSize = q[3].str();

			//		cout << "tx " << txID++ << " hash: " << txHash << " fee: " << txFee << " Size: " << txSize << endl;

					string txInRaw = q[4].str();
					string txOutRaw = q[5].str();
			//		cout << txInRaw;

					//scraping input addresses
//					cout << "TXIN" << endl;

					int inAddressNum = 0;
					int outAddressNum = 0;
					vi inAddressIDs;
					vi outAddressIDs;

					smatch in;
					smatch out;

					//handle generation input transaction
					if(gen){
						regex coinGenPattern("<li>Generation:\\s([\\S]+?)\\s\\S\\s([\\S]+?)\\stotal\\sfees");
						regex outAddressPattern("<li>.+?./address/([\\S]+?)\\S>.+?</a>:\\s([\\S]+?)</li>");
						regex_search(txInRaw,in,coinGenPattern);
						string coinGenBTC = in[1].str();
//						cout << "coin generation: " << coinGenBTC << endl;

						inAddressNum++;   //Generation address
						int addr_id=0;
						inAddressIDs.push_back(addr_id);

						//------> write to txin.txt
						txinFileName << txID << "\t" << addr_id << "\t" << (-1)*stringToDouble(coinGenBTC.c_str()) << endl;

						// Decrease generation balance
//						double tmpBalance;
//						tmpBalance = addrBalanceMap[0];
//						tmpBalance -= atoi(coinGenBTC.c_str());
//						addrBalanceMap[0] = tmpBalance;

						string totalBlkFee = in[2].str();
//						cout << "total fee: " << totalBlkFee << endl;
						gen = false;

						//out degree of the generation address ID
//						outdegree[0]++;

						//scraping output address in generation address
//						cout << "Generation TXOUT" << endl;
						regex_search(txOutRaw,out,outAddressPattern);
						string outAddress;

						outAddress = out[1].str();
						outAddressNum++;
//						cout << "Address: " << outAddress << endl;


						//------> write to addresses.txt
						if(addrMap.find(outAddress) == addrMap.end()){
							addrID++;
							addr_id = addrMap[outAddress] = addrID;
							addressFileName << addrID << "\t" << outAddress << endl;
						}else{
							addr_id = addrMap[outAddress];
						}

//						if(userMap.find(addr_id) == userMap.end()){
//							userID++;
//							userMap[addr_id] = userID;
//							addrUserMap.insert(pair<int,int>(addr_id,userID));
//							userAddrMap.insert(pair<int,int>(userID,addr_id));
//							//cout << "Gen Output Address ID: " << addrID  << "  User ID: " << userID << endl;
//						}

						//increase the in degree of this output address, these are the miner address
//						indegree[addr_id]++;

						string outAddressBTC;
						outAddressBTC = out[2].str();
//						cout << "outAddressBTC: " << outAddressBTC << endl;

						// increase output address balance
//						tmpBalance = addrBalanceMap[addr_id];
//						tmpBalance += atoi(outAddressBTC.c_str());
//						addrBalanceMap[addr_id] = tmpBalance;

						//------> write to txout.txt
						txoutFileName << txID << "\t" << addr_id << "\t" << outAddressBTC << endl;


						//------> write to txedges.txt
						txedgeFileName << txID << "\t" << 0 << "\t" << addr_id << endl;
					}
					else{	//not generation transaction
						regex inAddressPattern("<li>.+?./address/([\\S]+?)\\S>.+?</a>:\\s([\\S]+?)</li>");
						regex outAddressPattern("<li>.+?./address/([\\S]+?)\\S>.+?</a>:\\s([\\S]+?)</li>");

						//vector of inaddresses of the current non-generation TXX

						while(regex_search(txInRaw,in,inAddressPattern)){
							string inAddress;
							inAddressNum++;

							inAddress = in[1].str();
//							cout << "Address: " << inAddress << endl;

							//------> write to addresses.txt
							int addr_id;
							if(addrMap.find(inAddress) == addrMap.end()){
								addrID++;
								addr_id = addrMap[inAddress] = addrID;
								addressFileName << addr_id << "\t" << inAddress << endl;
							}else{
								addr_id = addrMap[inAddress];
							}
							inAddressIDs.push_back(addr_id);
							//increase the out degree of this input address
//							outdegree[addr_id]++;

							string inAddressBTC;
							inAddressBTC = in[2].str();
//							cout << "inAddressBTC: " << inAddressBTC << endl;

							// decrease input address balance
//							double tmpBalance;
//							tmpBalance = addrBalanceMap[addr_id];
//							tmpBalance -= atoi(inAddressBTC.c_str());
//							addrBalanceMap[addr_id] = tmpBalance;


							txInRaw = in.suffix().str();

							//------> write to txin.txt
							txinFileName << txID << "\t" << addr_id << "\t" << inAddressBTC << endl;
						}


				//	    cout << txOutRaw;
						//scraping output addresses
//						cout << "TXOUT" << endl;

						while(regex_search(txOutRaw,out,outAddressPattern)){
							string outAddress;
							outAddressNum++;

							outAddress = out[1].str();
//							cout << "Address: " << outAddress << endl;

							//------> write to addresses.txt
							int addr_id;
							if(addrMap.find(outAddress) == addrMap.end()){
								addrID++;
								addr_id = addrMap[outAddress] = addrID;
								addressFileName << addr_id << "\t" << outAddress << endl;
							}else{
								addr_id = addrMap[outAddress];
							}
							outAddressIDs.push_back(addr_id);
							//increase the indegree of this out address
//							indegree[addr_id]++;

							string outAddressBTC;
							outAddressBTC = out[2].str();
//							cout << "outAddressBTC: " << outAddressBTC << endl;

							// increase output address balance
//							double tmpBalance;
//							tmpBalance = addrBalanceMap[addr_id];
//							tmpBalance += atoi(outAddressBTC.c_str());
//							addrBalanceMap[addr_id] = tmpBalance;

							txOutRaw = out.suffix().str();

							//------> write to txout.txt
							txoutFileName << txID << "\t" << addr_id << "\t" << outAddressBTC << endl;
						}

						//------> write to txedges.txt
						for(unsigned int i=0 ; i < inAddressIDs.size() ; i++){
							for(unsigned int j=0; j < outAddressIDs.size(); j++){
								txedgeFileName << txID << "\t" << inAddressIDs[i] << "\t" << outAddressIDs[j] << endl;
							}
						}
/*
						int user_id,count=0;
						for(unsigned int i=0 ; i < inAddressIDs.size() ; i++){
							if(userMap.find(inAddressIDs[i]) != userMap.end()){ // if any of the input addresses already exists
								count++;
								int tmpUserID = userMap[inAddressIDs[i]];
								if(user_id > tmpUserID){ //find out the smallest user_id
									user_id = tmpUserID;
								}
							}
						}

						if(count == 0){ // if none of the input address already existed
							userID++;
							user_id = userID;
						}
						for(unsigned int i=0 ; i < inAddressIDs.size() ; i++){
								//cout << "inAddressID = " << inAddressIDs[i] << "  userID = " << user_id<<  endl;
								addrUserMap.insert(pair<int,int>(inAddressIDs[i],user_id));  //input addresses as the key of userID
								userAddrMap.insert(pair<int,int>(user_id,inAddressIDs[i]));  //userID as the key of input addresses
						}

						//identify change address from output addresses
						for(unsigned int j=0; j < outAddressIDs.size(); j++){
							if(userMap.find(outAddressIDs[j]) == userMap.end()){
								userID++;
								addrUserMap.insert(pair<int,int>(outAddressIDs[j],userID));
								userAddrMap.insert(pair<int,int>(userID,outAddressIDs[j]));
								userMap[outAddressIDs[j]] = userID;
								//cout << "Output Address ID: " << outAddressIDs[j]  << "  User ID: " << userID << endl;
							}
						}

*/
						//clear up inAddress and outAddress vector
						inAddressIDs.clear();
						outAddressIDs.clear();
					}

					//------>write to tx.txt
					txFileName << txID << "\t" << blkID << "\t" << inAddressNum << "\t" << outAddressNum << endl;

					//increase transaction number
					txID++;
					ss = n.suffix().str();
				}
			}

			blockID++; //increment blockID
			ifs.close();
	}
/*
	//determine user id
	if(userID != 0){ //Only generation user
		for(int addr = 1; addr <= addrID;addr++){ // addresses are the keys of the multimap
				typeof(addrUserMap.begin()) it = addrUserMap.equal_range(addr).first;
				int userid = (*it).second;
				//cout << "addr = " << addr << " user id before smallest = " << userid << endl;
				//find what other user ids given to this address id
				for(it = addrUserMap.equal_range(addr).first; it != addrUserMap.equal_range(addr).second; it++){
					//cout << "addr =" << it->first << "Other user ids = " << it->second << endl;
					if(it->second < userid){
						userid = it->second; // find the smallest
					}
				}
				//cout << "smallest userid = " << userid << endl;
				for(it = addrUserMap.equal_range(addr).first; it != addrUserMap.equal_range(addr).second; it++){
					int user_id = it->second;
					//cout << "addr = " << addr << "user id as the key: " << user_id << endl;
					//find out what other addresses have that user_id as the key in the userAddr multimap and set userid
					for(typeof(userAddrMap.begin()) it1 = userAddrMap.equal_range(user_id).first;
						it1 != userAddrMap.equal_range(user_id).second; it1++){
						//cout << "address to map =" << it1->second << endl;
						userMap[it1->second] = userid;
						//cout << "userMap[" << it1->second << "] = " << userid << endl;
					}
				}
		}
	}
*/

	//------>write to degree.txt
//	int addr_id2 = lastAddrID; // last addrID in the file
	//degree value for the generation address
//	if(addr_id2 == 0){
//		degreeFileName << 0 << "\t" << indegree[0] << "\t" << outdegree[0] << endl;
//		addr_id2++;
//	}
//	for(typeof(addrMap.begin()) it = addrMap.begin();it != addrMap.end(); it++){
//		degreeFileName << addr_id2 << "\t" << indegree[it->second] << "\t" << outdegree[it->second] << endl;
//		addr_id2++;
//	}

	//------>write to balances.txt and also userid.txt
//	for(long int addr = 0; addr <= addrID; addr++){
//		balanceFileName << addr << "\t" << addrBalanceMap[addr] << endl;
////		userIDFileName << addr << "\t" << userMap[addr] << endl;
//	}

	blkInfoFileName.close();
	blkHashFileName.close();
	txFileName.close();
	txinFileName.close();
	txoutFileName.close();
	txedgeFileName.close();
	txhashFileName.close();
	txtimeFileName.close();
	addressFileName.close();
//	balanceFileName.close();
//	userIDFileName.close();

//	addrUserMap.clear();
//	userAddrMap.clear();
//	indegree.clear();
//	outdegree.clear();
//	//------>write to txuniqueedge.txt
//	ifstream txedgeFileName;
//	txedgeFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinData/txedge.txt",ofstream::app);
//	ofstream txuniquedgeFileName;
//	txedgeFileName.open("C:/Users/ananda/Downloads/Bitcoin/BitcoinData/txedge.txt",ofstream::app);
//
//	userMap.clear();
	addrMap.clear();
//	addrBalanceMap.clear();

	//Weighted tx edge
	//sort(userMap.begin(),userMap.end());
//	tr(userMap,i){
//		cout << i->second << " ";
//	}


}




