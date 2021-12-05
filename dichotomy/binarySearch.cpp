#include<vector>
#include<iostream>
using namespace std;

template<typename T>
class BiSearch{
public:
    //匹配左边界
    int matchLeft(const vector<T>& nums,T target){
        int l=0,r=nums.size();
        int mid;
        while (l<r)
        {
            mid=(l+r)/2;
            if(nums[mid]<target){
                l=mid+1;
            }else if(nums[mid]==target){
                r=mid;
            }else{
                r=mid;
            }
        }
        if(l<nums.size()&&nums[l]==target){
            return l;
        }else{
            return -1;
        }
        
    }
    int matchRight(vector<T> nums,T target){
        int l=0,r=nums.size();
        int mid;
        while (l<r)
        {
            mid=(l+r)/2;
            if(nums[mid]<target){
                l=mid+1;
            }else if(nums[mid]==target){
                l=mid+1;
            }else{
                r=mid;
            }
        }
        //这里匹配的右边界是左闭右开的，因此匹配到的是r-1
        if(r>0&&r<=nums.size()&&nums[r-1]==target){
            return r-1;
        }else{
            return -1;
        }
    } 
};

int main(){
    BiSearch<int> BiSearchInt;
    vector<int> nums{3,3,5,7};
    cout<<BiSearchInt.matchLeft(nums,1)<<endl;
    cout<<BiSearchInt.matchRight(nums,1)<<endl;

}