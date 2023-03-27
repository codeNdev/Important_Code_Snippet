#include<bits/stdc++.h>
using namespace std;
#define ll long long
// SEGMENT TREES LAZY PROPAGATION
class LazySegTree{
    vector<ll> seg,lazy;
    public:
    LazySegTree(ll n){
        seg.resize(4*n,0);
        lazy.resize(4*n,0);
    }
    // build the segment tree
    void build(ll i,ll low, ll high, vector<ll>& arr){
        if(low==high){
            seg[i]=arr[low];return;
        }
        ll mid=low+(high-low)/2;
        build(2*i+1,low,mid,arr);
        build(2*i+2,mid+1,high,arr);
        seg[i]=seg[2*i+1]+seg[2*i+2];
    }
    // Update the segment tree----- Range Update ==> Lazy Propagation
    void update(ll i, ll low, ll high, ll l, ll r, ll val){
        // UPDATE THE PREVIOUS REMAINING UPDATES AND PROPAGATE DOWNWARDS
        if(lazy[i]!=0){
            // update the value
            seg[i]+=(high - low + 1)*lazy[i];
            // Propagate the Lazy Update Downward for the remaining Nodes to get Updated
            if(low!=high){
                lazy[2*i+1]+=lazy[i];
                lazy[2*i+2]+=lazy[i];
            }
            lazy[i]=0;
        }
        // NO OVERLAP
        if(r<low or l>high){
            return;
        }else if(low>=l and high<=r){
            // Node is Completely Within Given Range
            seg[i]+=(high - low + 1)*val;
            // If Not A LEAF node Lazy Propagate
            if(low!=high){
                lazy[2*i+1]+=val;
                lazy[2*i+2]+=val;
            }
            return;
        }else{
            ll mid= low+(high-low)/2;
            update(2*i+1,low, mid, l, r, val);
            update(2*i+2,mid+1,high, l, r, val);
            seg[i]=seg[2*i+1]+seg[2*i+2];
        }
    }
    ll query(ll i,ll low, ll high, ll l, ll r){
        // Same as segment tree
        // BUT IF previous updates remaining, Do it and Propagate 
        // and return required answer
        if(lazy[i]!=0){
            // update the value
            seg[i]+=(high - low + 1)*lazy[i];
            // Propagate the Lazy Update Downward for the remaining Nodes to get Updated
            if(low!=high){
                lazy[2*i+1]+=lazy[i];
                lazy[2*i+2]+=lazy[i];
            }
            lazy[i]=0;
        }
        if(r<low or l>high){
            // NO OVERLAP
            return 0LL;
        }else if(low>=l and high<=r){
            // Node is Completely Within Given Range
            return seg[i];
        }else{
            ll mid= low+(high-low)/2;
            ll left= query(2*i+1,low, mid, l, r);
            ll right= query(2*i+2,mid+1,high, l, r);
            return (left+right);
        }
    }
};
