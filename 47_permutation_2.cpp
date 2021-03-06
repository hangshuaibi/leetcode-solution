#include <algorithm>
#include <vector>

using namespace std;

//不好意思，stl就是这么炫，next_permutation搞定了三道题--

//std差不多8ms
//下面的版本12ms
//记得要先做一个排序，next_permutation事实上是找到下一个递增数
//若该数不是当前组合后的最大值
//那么必然存在两个相邻数nums[i]<nums[i+1]
//我们从右往左找到第一个这样的两个数
//容易推得nums[i+1:]是非递增的
//这时候只要找出最右边第一个大于nums[i]的数与nums[i]进行swap
//这时候[i+1:]仍然是有序的
//并且该数大于原数
//把[i+1:]reverse一下，得到的数也即是大于原数的最小数

//另：这个枚举是可以处理重复数的
namespace sch001{
    template<class BIt>
    bool next_permutation(BIt first, BIt last){
        if(first == last)return false;//size == 0
        BIt i = last;
        if(--i==first)return false;//size == 1
        while ((true))
        {
            BIt i1 = i;
            if(*--i<*i1){
                BIt i2 = last;
                while(!(*i<*--i2));
                swap(*i, *i2);
                std::reverse(i1, last);
                return true;
            }
            if(i==first){
                std::reverse(first, last);//回归原位
                return false;
            }
        }

    }
};

class _Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ret;
        std::sort(nums.begin(), nums.end());
        do{
            ret.push_back(nums);
        }while(sch001::next_permutation(nums.begin(), nums.end()));

        return ret;
    }
};

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ret;
        // std::sort(nums.begin(), nums.end());
        // do{
        //     ret.push_back(nums);
        // }while(sch001::next_permutation(nums.begin(), nums.end()));
        generate(ret, nums,0);

        return ret;
    }

    void generate(vector<vector<int>>& res, vector<int>& nums, int cur){
        if(cur==nums.size()){
            res.push_back(nums);
            return;
        }

        for(int i=cur;i<nums.size();i++){
            // if(i!=cur&&(nums[i]==nums[i-1]||nums[i]==nums[cur]))continue;
            //去重的关键
            //一开始以为只要排序后，比较是否和前面的数相同来continue
            //最后一个case就死了==
            bool flag = true;
            for(int j=cur;j<i;j++){
                if(nums[j]==nums[i]){
                    flag = false;
                    break;
                }
            }
            if(!flag)continue;
            //
            swap(nums[i],nums[cur]);
            generate(res,nums,cur+1);
            swap(nums[i],nums[cur]);
        }
    }
};