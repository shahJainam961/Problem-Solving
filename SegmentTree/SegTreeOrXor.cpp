#include<bits/stdc++.h>
using namespace std;


class SegTreeOrXor{

private:
    vector<int> seg;

public:
    SegTreeOrXor(){}
    SegTreeOrXor(int n){
        int ele = pow(2, n);
        seg.resize(4*ele); 
    }

    int l(int i){
        return 2*i + 1;
    }

    int r(int i){
        return 2*i + 2;
    }

    void build(int ind, int low, int high, vector<int> &arr, bool orr){
        if(low==high){
            seg[ind] = arr[low];
            return;
        }
        int mid = low + (high-low)/2;
        build(l(ind), low, mid, arr, !orr);
        build(r(ind), mid+1, high, arr, !orr);
        if(orr) seg[ind] = seg[l(ind)] | seg[r(ind)];
        else seg[ind] = seg[l(ind)] ^ seg[r(ind)];
    }

    void pointUpdate(int ind, int low, int high, int k, int val, bool orr){
        if(low==high){
            seg[ind] = val;
            return;
        }
        int mid = low + (high-low)/2;
        if(k<=mid) pointUpdate(l(ind), low, mid, k, val, !orr);
        else pointUpdate(r(ind), mid+1, high, k, val, !orr);
        if(orr) seg[ind] = seg[l(ind)] | seg[r(ind)];
        else seg[ind] = seg[l(ind)] ^ seg[r(ind)];
    }

    int getRoot(){
        return seg[0];
    }

    void print(){
        for(int i : seg) cout<<i<<" ";
        cout<<endl;
    }

};


int main(){
    // #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif

    int n, q;
    cin>>n>>q;

    int ele = pow(2, n);
    
    vector<int> arr(ele);
    for(int i=0; i<ele; i++){
        cin>>arr[i];
    }
    
    SegTreeOrXor* segTree = new SegTreeOrXor(ele);

    bool orr = true;
    if(n%2==0) orr = false;

    segTree->build(0, 0, ele-1, arr, orr);
    while(q--){
        int ind, val;
        cin>>ind>>val;
        segTree->pointUpdate(0, 0, ele-1, ind-1, val, orr);
        cout<<segTree->getRoot()<<endl;
    }
    return 0;
}