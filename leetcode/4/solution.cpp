#include <vector>
using std::vector;

class Solution
{
    public:
        double findMedianSortedArrays(vector<int> & nums1,vector<int> & nums2)
            //We will use recursive method. Divide and conque.
        {
            int n1=nums1.size(),n2=nums2.size();
            return findMedian(nums1,0,n1-1,nums2,0,n2-1);
        }

        double findMedian(vector<int> & nums1, int lo1, int hi1, vector<int> & nums2, int lo2, int hi2)
        {
            int n1=hi1-lo1+1;
            int n2=hi2-lo2+1;
            if(n1>n2)
                return findMedian(nums2,lo2,hi2,nums1,lo1,hi1); // n1 is always <=n2
            if(n1==0)
            {
                if(n2%2==0)
                    return (nums2[(n2>>1)-1]+nums2[n2>>1])/2.0;
                else
                    return nums2[n2>>1];
            }

            if(n1<=10 && n2<=10)
                return trival_solution(nums1, lo1, hi1, nums2, lo2, hi2);

            if(n1*2<n2)   
                //if n1 is much less than n2. This was the key point of this problem.
                //assuming n2-x=((n1+n2)>>1)+1
                //Then the x elements in the head and back of the nums2 can be safety deleted.
                //x=n2-((n1+n2)>>1)-1 > 2*n1-((n1+2*n1)>>1)-1=n1-(n1>>1)-1 
            {
                int x=n2-((n1+n2)>>1)-1;
                return findMedian(nums1,lo1,hi1,nums2,lo2+x,hi2-x);
            }

            if(n1<=10)    // trivial solution
                return trival_solution(nums1,lo1,hi1,nums2,lo2,hi2);

            int mid1=(lo1+hi1)>>1;
            int mid2=(lo2+hi2)>>1;
            if(nums1[mid1]<=nums2[mid2])
                //assuming we delete x elements in the head of nums1, we should have
                //n1-x+hi2-mid2+1=((n1+n2)>>1)+1
                //So we have x=n1+hi2-mid2-((n1+n2)>>1)
            {
                int x=n1+hi2-mid2-((n1+n2)>>1);
                x=std::min(x,mid1-lo1-1);
                return findMedian(nums1,lo1+x,hi1,nums2,lo2,hi2-x);
            }

            else if(nums1[mid1]>nums2[mid2])
                //assuming we delete x elements in the end of the nums1, we should have
                //n1-x+mid2-lo2+1=((n1+n2)>>1)+1
                //So we have x=n1+mid2-lo2-((n1+n2)>>1)
            {
                int x=n1+mid2-lo2-((n1+n2)>>1);
                x=std::min(x,hi1-mid1-1);
                return findMedian(nums1,lo1,hi1-x,nums2,lo2+x,hi2);
            }
            return 0;
        }

        double trival_solution(vector<int> & nums1, int lo1, int hi1, vector<int> & nums2, int lo2, int hi2)
        {
            vector<int> merge_num;
            int i=lo1,j=lo2;
            while(i<=hi1 && j<=hi2)
            {
                if(nums1[i]<=nums2[j]) merge_num.push_back(nums1[i++]);
                else merge_num.push_back(nums2[j++]);
            }
            if(i<=hi1) merge_num.insert(merge_num.end(),nums1.begin()+i,nums1.begin()+hi1+1);
            else merge_num.insert(merge_num.end(),nums2.begin()+j,nums2.begin()+hi2+1);
            int n=merge_num.size();
            if(n%2==0)
                return (merge_num[(n>>1)-1]+merge_num[(n>>1)])/2.0;
            else
                return merge_num[n>>1];
        }

};
