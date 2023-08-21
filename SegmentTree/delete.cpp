#include<bits/stdc++.h>
using namespace std;

class SegTreeMinRangeUpdates{
private:
    vector<int> seg, lazy;
public:
    SegTreeMinRangeUpdates(int n){
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
        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
    }

    // from l to r increment elements by val
    void rangeUpdate(int ind, int low, int high, int l, int r, int val){
        // Update the previous reamining update and propogate downwards
        if(lazy[ind]!=0){
            seg[ind] += lazy[ind];
            // propogate downwards
            if(low!=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // No Overlap
        // low high l r OR l r low high
        if(high<l or low>r) return;

        // Complete Overlap
        // l low high r
        else if(low>=l and high<=r){
            seg[ind] += val
            if(low!=high){
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            }
            return;
        }

        // Partial Overlap
        else{
            int mid = low + (high-low)/2;
            rangeUpdate(2*ind+1, low, mid, l, r, val);
            rangeUpdate(2*ind+2, mid+1, high, l, r, val);
            seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
            return;
        }
    }

    int rangeQuery(int ind, int low, int high, int l, int r){
        // Update if any remaining and lazy propagte
        if(lazy[ind]!=0){
            seg[ind] += lazy[ind];
            // propogate downwards
            if(low!=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
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
            int left = rangeQuery(2*ind+1, low, mid, l, r);
            int right = rangeQuery(2*ind+2, mid+1, high, l, r);
            return min(left, right);
        }

    }
};

class Solution {

    int f(SegTreeMinRangeUpdates &segTree, int l, int r, int n){
        
        if(l==r) return segTree.rangeQuery(0, 0, n-1, l, r);

        int mini = segTree.rangeQuery(0, 0, n-1, l, r);
        int res = 0;
        int ind = l;

        while(ind<=r){

            while(ind<=r and )

        }



    }

public:
    int minNumberOperations(vector<int>& arr) {
        int res = 0;
        int n = arr.size();
        SegTreeMinRangeUpdates segTree(n);
        segTree.build(0, 0, n-1, arr);
        return f(segTree, 0, n-1, n);
    }
};