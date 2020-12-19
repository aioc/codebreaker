           #include<cstdio>
        #include/*gap*/<algorithm>
    #define for for(int i=1;i<=B;i++)
using namespace std;int B, N, A[100005],lo,
hi=1111111111,mid,best,placed,ans;int main(){
scanf("%d%d",&B,&N);for scanf("%d", &A[i]);lo=1,hi=N-B-2;while(lo<=hi){
mid=(lo+hi)/2;for placed+=min(A[i],mid);if(placed<N)best=(lo=mid+1)-1;
else hi=mid-1; placed=0;}for//itsatennisracketok
   placed+=min(A[i],best);while(placed!=N)
       placed+=A[ans=ans%B+1]>best;
          printf("%d\n",ans);}
