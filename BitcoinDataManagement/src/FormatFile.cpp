/*
 * FormatFile.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: zehadyzbdullahkhan
 */

#include "FormatFile.h"


void FormatFile::formatAddressFile(){
	ifstream addrFile;

	addrFile.open(string(MAC_PATH + "addresses.txt").c_str(),ifstream::in);

	ofstream addrOutFile;
	addrOutFile.open(string(MAC_PATH + "addressesn.txt").c_str(),ofstream::out);
	if(addrFile.is_open()){
		string line;

		while(getline(addrFile,line)){
			istringstream iss(line);
			long int addrID;
			string addr;

			while(iss >> addrID){
				iss >> addr;

				if(addr != "" && addr != "-X-X-X-"){
					addrOutFile << addrID << "\t" << addr << endl;
				}else{
					cout << addrID << "\t" << "unknown" << endl;
					addrOutFile << addrID << "\t" << "unknown" << endl;
				}
				addr = "-X-X-X-";
			}
		}
	}


}

void FormatFile::formatTxOutFile(){
	ifstream txOutFile;

	txOutFile.open(string(MAC_PATH + "txout.txt").c_str(),ifstream::in);

	ofstream txOutOutFile;
	txOutOutFile.open(string(MAC_PATH + "txoutn.txt").c_str(),ofstream::out);

	if(txOutFile.is_open()){
			string line;
			while(getline(txOutFile,line)){

				istringstream iss(line);
				string txOutID, addrID, value;

				while(iss >> txOutID >> addrID){
					iss >> value;

					if(value != "" && value != "-X-X-X-"){
						cout << txOutID << "\t" << addrID << "\t" << value << endl;
						txOutOutFile << txOutID << "\t" << addrID << "\t" << value << endl;
					}else{
						cout << txOutID << "\t" << addrID << "\t" << -1 << endl;
						txOutOutFile << txOutID << "\t" << addrID << "\t" << -1 << endl;
					}
					value = "-X-X-X-";
				}
			}
		}
}
