#include <bits/stdc++.h>
using namespace std;
#define int long long int 
#define ld long double
#define F first
#define S second
#define P pair<int,int>
#define V vector
#define eb emplace_back
#define pb push_back
#define mp make_pair

int totalBlockWeight = 4*1e6;
//Global variables 
int toint(const string &s) {stringstream ss; ss << s; int x; ss >> x; return x;} 
string file_name = "mempool.csv";
vector<string> output; // output vector to store txid which will be 
int total_weight_in_block =0 , total_fee_earned=0;
map<string,int> components;
set<string>found_parents;

struct block{
 	string txid ;
 	int fee=0 , weight=0;
 	vector<string> parent_txid;

}; 

block add_block(vector<string> &trans) // Step 1 coverting CSV file to C++ readable format
{
	string id = trans[0];
	int fee = toint(trans[1]);
	int weight = toint(trans[2]);
	vector<string>pars;
	for(int i = 3;i<trans.size();i++){
		pars.emplace_back(trans[i]);
	}
	return {id,fee,weight,pars};
}


void make_map(vector<block>&initial_blocks) // Step 2 , making map to acces Trixid in O(log n) time 
{
	for(int i=0;i<initial_blocks.size();i++){
		components[initial_blocks[i].txid] = i;
	}
}

bool isValid(vector<string>&has) // checking validity 
{
	for(auto &x : has){
		if(found_parents.count(x)==0){
			return false;
		}
	}
	return true;
}


void getOutput(vector<string>& output, string filename){
    ofstream myfile(filename);
    for(auto s:output){
        myfile << s << endl;
    }
    myfile.close();
}



int32_t main(){
	string k;
	ifstream in_file(file_name);
	vector<block>selected_block;

	while(getline(in_file,k)){
        stringstream strut(k);
        vector<string>transaction;
        string intermediate; 
        while(getline(strut,intermediate,',')){
            transaction.push_back(intermediate);
        }
        selected_block.pb(add_block(transaction));
	}

	// int consider = selected_block.size();

	make_map(selected_block);
	set<pair<ld,int>,greater<pair<ld,int>>>ratio_fee_by_weight;
	for(auto &x : selected_block){
		ld ratio = (ld)(((ld)x.fee) / ((ld)x.weight));
		int ele = components[x.txid];
		ratio_fee_by_weight.insert({ratio,ele});
	}


	while(!ratio_fee_by_weight.empty())
	{
		bool found = false;
		for(auto &r : ratio_fee_by_weight)
		{
			if(isValid(selected_block[r.S].parent_txid))
			{
				if(total_weight_in_block + selected_block[r.S].weight <= totalBlockWeight)
				{
					found = true;
					total_weight_in_block += selected_block[r.S].weight;
					total_fee_earned += selected_block[r.S].fee;
					for(auto edge : selected_block[r.S].parent_txid){
						found_parents.insert(edge);
					}

					output.pb(selected_block[r.S].txid);
					ratio_fee_by_weight.erase(r);
					break;
				}
			}
		}
		if(!found){
			break;
		}
	}

	cout<<"Total weight of the Block  "<<total_weight_in_block<<endl;
	cout<<"Total fee earned by miner(objective)  "<<total_fee_earned<<endl;
	cout<<"Total transactions considered  "<<output.size()<<endl;

	getOutput(output, "block.txt");
	return 0;

}
