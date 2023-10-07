#include<bits/stdc++.h>
#define int long long
using namespace std;

int minMoves(vector<int>& nums, int k) {
        long long n = nums.size();
        long long ans = INT_MAX;
        vector<long long> oneInd;
        for(long long i=0; i<n; i++) if(nums[i]==1) oneInd.push_back(i);
        long long ones = oneInd.size();
        vector<long long> prefix(ones, 0);
        prefix[0] = oneInd[0];
        for(long long i=1; i<ones; i++) prefix[i] += prefix[i-1] + oneInd[i];
        n = oneInd.size();
        for(int i=0; i<=n-k; i++){
            long long start = i;
            long long end = i+k-1;
            long long mid = start + (end-start)/2;
            long long temp;
            long long rightSum = prefix[end] - (mid>=0?prefix[mid]:0);
            long long leftSum = (mid-1>=0?prefix[mid-1]:0) - (start-1>=0?prefix[start-1]:0);
            long long compensate;
            temp = rightSum - leftSum;
            if(k%2==0){
                temp -= oneInd[mid];
                long long radius1 = (k-1)/2;
                long long radius2 = radius1 + 1;
                compensate = (radius1*(radius1+1)/2) + (radius2*(radius2+1)/2);
            }
            else{
                long long radius = (k-1)/2;
                compensate = radius * (radius+1);
            }
            temp -= compensate;
            ans = min(ans, temp);
        }
        return ans;
    }

signed main(){

    return 0;
}
