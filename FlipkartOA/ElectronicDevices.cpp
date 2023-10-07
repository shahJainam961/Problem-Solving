#include<bits/stdc++.h>
#define int long long
using namespace std;

bool isVowel(char ch){
	return ch=='a' or ch=='A' or ch=='e' or ch=='E' or ch=='i' or ch=='I'
			 or ch=='o' or ch=='O' or ch=='u' or ch=='U';
}

signed main(){
	
	string items;
	cin>>items;
	int k;
	cin>>k;
	
	int i=0;
	int j=0;
	int n = items.size();
	int ans = 0;
	int cnt = 0;
	
	while(j<n){
		cnt +=	isVowel(items[j]);
		if(j-i+1<k){
			j++;
			continue;
		}
		else if(j-i+1==k){
			ans = max(ans, cnt);
			cnt -= isVowel(items[i]);
			i++;
			j++;
		}
	}
	cout<<ans;
    return 0;
}
