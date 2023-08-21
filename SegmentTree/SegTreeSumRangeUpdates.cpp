#include<bits/stdc++.h>
using namespace std;

class SegTreeSumRangeUpdates{
private:
    vector<int> seg, lazy;
public:
    SegTreeSumRangeUpdates(int n){
        seg.resize(4*n);
        lazy.resize(4*n);
    }

    void build(int ind, int low, int high, vector<int> &arr){
        if(low==high){
            seg[ind] = arr[low];
            return;
        }
        int mid = low + (high-low)/2;
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);
        seg[ind] = seg[2*ind+1] + seg[2*ind+2];
    }	

    // from l to r increment elements by val
    void rangeUpdate(int ind, int low, int high, int l, int r, int val, vector<int> &arr){
        // Update the previous remaining update and propogate downwards
        if(lazy[ind]!=0){
            seg[ind] += ((high-low+1)*lazy[ind]);
            // propogate downwards
            if(low!=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            else{
                arr[low] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // No Overlap
        // low high l r OR l r low high
        if(high<l or low>r) return;

        // Complete Overlap
        // l low high r
        else if(low>=l and high<=r){
            seg[ind] += ((high-low+1)*val);
            if(low!=high){
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            }
            else{
                arr[low] += val;
            }
            return;
        }

        // Partial Overlap
        else{
            int mid = low + (high-low)/2;
            rangeUpdate(2*ind+1, low, mid, l, r, val, arr);
            rangeUpdate(2*ind+2, mid+1, high, l, r, val, arr);
            seg[ind] = seg[2*ind+1] + seg[2*ind+2];
            return;
        }
    }

    int rangeQuery(int ind, int low, int high, int l, int r, vector<int> &arr){
        // Update if any remaining and lazy propagte
        if(lazy[ind]!=0){
            seg[ind] += ((high-low+1)*lazy[ind]);
            // propogate downwards
            if(low!=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            else{
                arr[low] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // No Overlap
        // low high l r OR l r low high
        if(high<l or low>r) return 0;

        // Complete Overlap
        // l low high r
        else if(low>=l and high<=r) return seg[ind];

        // Partial Overlap
        else{
            int mid = low + (high-low)/2;
            int left = rangeQuery(2*ind+1, low, mid, l, r, arr);
            int right = rangeQuery(2*ind+2, mid+1, high, l, r, arr);
            return left + right;
        }

    }
};


int main(){
    // #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif

    int n;
    cin>>n;

    vector<int> arr(n);
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    SegTreeSumRangeUpdates* segTree = new SegTreeSumRangeUpdates(n);
    segTree->build(0, 0, n-1, arr);

    int q;
    cin>>q;

    while(q--){
        int type;
        cin>>type;

        if(type==1){
            int l, r;
            cin>>l>>r;
            cout<<segTree->rangeQuery(0, 0, n-1, l, r, arr)<<endl;
        }
        else{
            int l, r, val;
            cin>>l>>r>>val;
            segTree->rangeUpdate(0, 0, n-1, l, r, val, arr);
        }
    }
    for(int i : arr) cout<<i<<" ";
    return 0;
}
