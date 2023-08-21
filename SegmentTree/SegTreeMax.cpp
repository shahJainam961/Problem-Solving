#include<bits/stdc++.h>
using namespace std;

class SegTreeMax{

private:
    vector<int> seg;
public:
    SegTreeMax(){}
    SegTreeMax(int n){
        seg.resize(4*n);
    }

    void build(int ind, int low, int high, vector<int> &arr){
        if(low==high){
            seg[ind] = arr[low];
            return;
        }
        
        int mid = low + (high-low)/2;
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);
        seg[ind] = max(seg[2*ind+1], seg[2*ind+2]);
    }

    int rangeQuery(int ind, int low, int high, int l, int r){
        // complete overlap
        // l low high r
        if(low>=l and high<=r) return seg[ind];

        //no overlap
        // low high l r OR l r low high
        else if(low>r or high<l) return INT_MIN;

        //partial overlap
        else{
            int mid = low + (high-low)/2;
            int left = rangeQuery(2*ind+1, low, mid, l, r);
            int right = rangeQuery(2*ind+2, mid+1, high, l, r);
            return max(left, right);
        }
    }

    void pointUpdate(int ind, int low, int high, int k, int val, vector<int> &arr){
        if(low==high){
            seg[ind] = val;
            arr[k] = val;
            return;
        }

        int mid = low + (high-low)/2;
        if(k<=mid) pointUpdate(2*ind+1, low, mid, k, val, arr);
        else pointUpdate(2*ind+2, mid+1, high, k, val, arr);
        seg[ind] = max(seg[2*ind+1], seg[2*ind+2]);
    }
};

int main(){
    // #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif

    int t;
    cin>>t;

    while(t--){
        int n, q;
        cin>>n>>q;

        vector<int> arr(n);

        for(int i=0; i<n; i++)
            cin>>arr[i];
        
        SegTreeMax* segTree = new SegTreeMax(n);
        segTree->build(0, 0, n-1, arr);

        for(int i=0; i<q; i++){
            int type;
            cin>>type;

            if(type==1){
                int l, r;
                cin>>l>>r;
                cout<<segTree->rangeQuery(0, 0, n-1, l, r)<<endl;
            }
            else{
                int k, val;
                cin>>k>>val;
                segTree->pointUpdate(0, 0, n-1, k, val, arr);
            }
        }
    }
}