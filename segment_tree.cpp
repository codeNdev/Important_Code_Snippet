class segTree{
    vector<int> st;
    public:
    segTree(int n){
        st.resize(4*n+5,0);
    }
    void build(int i,int low,int high,vector<int>&arr){
        if(low==high){
            st[i]=arr[low];return;
        }
        int mid=low+(high-low)/2;
        build(2*i+1,low,mid,arr);
        build(2*i+2,mid+1,high,arr);
        st[i]=min(st[2*i+1],st[2*i+2]);
    }
    int query(int i,int low,int high,int l,int r){
        // NO OVERLAPPING
        if(high<l or low>r){
            return INT_MAX;
        }else if(low>=l and high<=r){
            // Complete Overlapping
            return st[i];
        }else{
            // Partially Overlapping
            int mid=low+(high-low)/2;
            int left=query(2*i+1,low,mid,l,r);
            int right=query(2*i+2,mid+1,high,l,r);
            return min(left,right);
        }
    }
    void update(int i,int low, int high,int idx,int val,vector<int>&arr){
        // Base case
        // on the leaf of segment tree
        if(low==high){
            arr[idx]=val;
            st[i]=val;
            return;
        }
        int mid=low+(high-low)/2;
        if(idx<=mid){
            update(2*i+1,low,mid,idx,val,arr);
        }else{
            update(2*i+2,mid+1,high,idx,val,arr);
        }
        st[i]=min(st[2*i+1],st[2*i+2]);
    }
};
