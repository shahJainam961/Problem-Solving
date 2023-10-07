#include<bits/stdc++.h>
#define int long long
using namespace std;

// samDaily, kellyDaily initSam
// n*samDaily + initSam < n*kellyDaily
// n > (initSam)/(kellyDaily - samDaily)

signed main(){

	int s, k, i;
	cin>>s>>k>>i;
	
	if(s-k>=0){
		cout<<"-1";
		return 0;
	}
	
	int n = i/(k-s);
	n++;
	cout<<n;
	
    return 0;
}
