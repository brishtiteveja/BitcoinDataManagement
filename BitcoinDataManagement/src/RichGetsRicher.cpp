/*
 * RichGetsRicher.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: zehadyzbdullahkhan
 */
#include "CommonHeaders.h"
#include "RichGetsRicher.h"

void numberOfAddressesOverWeeks(){
	ifstream txtimef("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin_dataset/txtime.txt");
	ifstream txf("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin_dataset/tx.txt");
	ifstream txinf("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin_dataset/txin.txt");
	ifstream txoutf("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin_dataset/txout.txt");
	ifstream addrf("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin_dataset/addresses.txt");

	ofstream addr_per_weekf("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin_dataset/my_bitcoin_computed/address_every_week.txt");
	ofstream cum_addr_per_weekf("/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/bitcoin_dataset/my_bitcoin_computed/cumulative_address_every_week.txt");

	//storing txid and txtime in a vector id_time from txtime.txt file
	ii i_t;
	vii txtime;
	string id,time;
	while(txtimef >> id && txtimef >> time ){
		i_t.first = atoi(id.c_str());
		i_t.second = atoi(time.c_str());
		txtime.push_back(i_t);
	}

	//storing tx in a vector tx from txin.txt file
	ii id_blkid;
	iii id_blkid_nInput;
	iiii id_blkid_nInput_nOutput;
	viiii tx;

	string id2,blkid,nInput,nOutput;
	while(txf >> id2 && txf >> blkid && txf >> nInput && txf >> nOutput){
		id_blkid = ii(atoi(id2.c_str()),atoi(blkid.c_str()));
		id_blkid_nInput = iii(id_blkid,atoi(nInput.c_str()));
		id_blkid_nInput_nOutput = iiii(id_blkid_nInput,atoi(nOutput.c_str()));
		tx.push_back(id_blkid_nInput_nOutput);
	}

	//cout << tx[100].first.first.first << " " << tx[100].first.first.second << " " << tx[100].first.second << " " << tx[100].second << endl;

	//int initial_time = txtime[0].second;

	//int end_time = txtime[len - 1].second;


	//	//1 week = 604800 seconds
//	int i,k;
//	for(k = 0, i = initial_time; i <= end_time; i += 604800){
//		int s = i;
//		int e = i + 604800 - 1;
//
//		int addr_count = 0;
//		for(;s <= e; s++){
//
//		}
//	}

	int len = txtime.size();
	vi addr_per_week;
	vi cum_addr_per_week;

	int week = 0;
	int addr_count = 0;
	int cum_addr_count = 0;

	for(int k = 0 ; k < len ; k++){
		if(txtime[k].second  >= txtime[0].second + week * 604800){
			if(k != 0){
				addr_per_week.push_back(addr_count);
				cum_addr_per_week.push_back(cum_addr_count);
			}
			week ++;
			addr_count = 0;
		}

		int txid = txtime[k].first;
		addr_count += (tx[txid].first.second + tx[txid].second);
		cum_addr_count += (tx[txid].first.second + tx[txid].second);
	}

	for(int i = 0; i < (int)addr_per_week.size(); i++){
		cout << "week " << i + 1 << ": " << addr_per_week[i]  << endl;
		addr_per_weekf << i + 1 << "\t" << txtime[0].second + i * 604800 << "\t" << addr_per_week[i] << endl;
		cum_addr_per_weekf << i + 1 << "\t" << txtime[0].second + i * 604800 << "\t" << cum_addr_per_week[i] << endl;

	}



	txtimef.close();
	txf.close();
	txinf.close();
	txoutf.close();
	addrf.close();

	addr_per_weekf.close();
	cum_addr_per_weekf.close();
}




