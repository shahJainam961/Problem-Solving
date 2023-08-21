// C. Sereja and Brackets
// time limit per test 1 second
// memory limit per test 256 megabytes
// inputstandard input
// outputstandard output

// Sereja has a bracket sequence s1, s2, ..., sn, or, in other words, a string s of length n, consisting of characters "(" and ")".
// Sereja needs to answer m queries, each of them is described by two integers li, ri (1 ≤ li ≤ ri ≤ n). The answer to the i-th query is the length of the maximum correct bracket subsequence of sequence sli, sli + 1, ..., sri. Help Sereja answer all queries.
// You can find the definitions for a subsequence and a correct bracket sequence in the notes.

// Input
// The first line contains a sequence of characters s1, s2, ..., sn (1 ≤ n ≤ 106) without any spaces. Each character is either a "(" or a ")". The second line contains integer m (1 ≤ m ≤ 105) — the number of queries. Each of the next m lines contains a pair of integers. The i-th line contains integers li, ri (1 ≤ li ≤ ri ≤ n) — the description of the i-th query.
// Output
// Print the answer to each question on a single line. Print the answers in the order they go in the input.

// input

// ())(())(())(
// 7
// 1 1
// 2 3
// 1 2
// 1 12
// 8 12
// 5 11
// 2 10

// output

// 0
// 0
// 2
// 10
// 4
// 6
// 6

// Note
// A subsequence of length |x| of string s = s1s2... s|s| (where |s| is the length of string s) is string x = sk1sk2... sk|x| (1 ≤ k1 < k2 < ... < k|x| ≤ |s|).

// A correct bracket sequence is a bracket sequence that can be transformed into a correct aryphmetic expression by inserting characters "1" and "+" between the characters of the string. For example, bracket sequences "()()", "(())" are correct (the resulting expressions "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

// For the third query required sequence will be «()».

// For the fourth query required sequence will be «()(())(())».

#include<bits/stdc++.h>
using namespace std;

class Node{

private:
    int open;
    int close;
    int full;

public:
    Node(){
        open = 0;
        close = 0;
        full = 0;
    }

    Node(int _open, int _close, int _full){
        open = _open;
        close = _close;
        full = _full;
    }

    int getOpen(){return open;}
    int getClose(){return close;}
    int getFull(){return full;}

};

class SegTreeParanthesis{

private:
    vector<Node*> seg;

public:
    SegTreeParanthesis(int n){
        seg.resize(4*n);
    }

    Node* merge(Node* n1, Node* n2){
        int _open, _close, _full;
        int x = min(n1->getOpen(), n2->getClose());
        _full = n1->getFull() + n2->getFull() + x;
        _open = n1->getOpen() + n2->getOpen() - x;
        _close = n1->getClose() + n2->getClose() - x;

        Node* ans =new Node(_open, _close, _full);
        return ans;
    }

    void build(int ind, int low, int high, string &s){
        if(low==high){
            // cout<<ind<<endl;
            seg[ind] = new Node(s[low]=='(', s[low]==')', 0);
            return;
        }
        int mid = low + (high-low)/2;
        build(2*ind+1, low, mid, s);
        build(2*ind+2, mid+1, high, s);
        seg[ind] = merge(seg[2*ind+1], seg[2*ind+2]);
    }

    Node* rangeQuery(int ind, int low, int high, int l, int r){
        // In range
        // l low high r
        if(low>=l and high<=r) return seg[ind];

        // Out of Range
        // low high l r OR l r low high
        else if(high<l or low>r) return new Node();

        // Partial Range
        else{
            int mid = low + (high - low)/2;
            Node* left = rangeQuery(2*ind+1, low, mid, l, r);
            Node* right = rangeQuery(2*ind+2, mid+1, high, l, r);
            Node* ans = merge(left, right);
            return ans;
        }
    }
};


int main(){
    // #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif

    string s;
    cin>>s;

    int n = s.size();
    SegTreeParanthesis*  segTree = new SegTreeParanthesis(n);
    segTree->build(0, 0, n-1, s);

    int q;
    cin>>q;

    while(q--){
        int l, r;
        cin>>l>>r; l--; r--; // From 1-based indexing To 0-based indexing
        Node* ans = segTree->rangeQuery(0, 0, n-1, l, r);
        int res = 2*ans->getFull();
        cout<<res;
        if(q!=0)cout<<endl;
    }

}
