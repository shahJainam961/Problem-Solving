#include<bits/stdc++.h>
#define int long long
using namespace std;

bool cmp(pair<string, int> &a, pair<string, int> &b){
	return a.second > b.second;
}

signed main(){

	int n;
	cin>>n;
	vector<string> books(n);
	for(string &i : books) cin>>i;
	
	vector<string> order;
	
	int timer = 0;
	unordered_map<string, int> mp;
	
	
	for(string i : books){
		auto it = mp.find(i);
		if(it!=mp.end()) mp.erase(it);
		mp[i] = ++timer;
	} 

	vector<pair<string, int>> st;
	for(auto i : mp) st.push_back({i.first, i.second});
	
	sort(st.begin(), st.end(), cmp);
	
	for(auto i : st) order.push_back(i.first);
	for(string a : order) cout<<a<<" ";
    return 0;
}
