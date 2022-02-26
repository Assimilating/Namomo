#include<bits/stdc++.h>
#include<unordered_map>
#include<ext/pb_ds/priority_queue.hpp>
#define rep(i,j,k) for(register int i=j;i<=k;i++)
#define rrep(i,j,k) for(register int i=j;i>=k;i--)
#define erep(i,u) for(register int i=head[u];~i;i=nxt[i])
#define fastIO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define println(x) print(x),print('\n')
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pr = pair<ll,ll>;
const int MAXN = 1e6+11;
const int INF  = 0x3f3f3f3f;
const double EPS = 1e-7;
//a存储数组
int a[MAXN],n,l[MAXN],r[MAXN];

int main(){
    fastIO;
    while(cin>>n){
        //读入数组a的每个元素
        rep(i,1,n) 
            cin>>a[i];

        //单调栈，元素是a[]中的下标
        stack<int> stk;

        //计算每个a[i]作为区间中最左最小元素的区间的 极左边界l[i]
        //for all j in {l[i], ..., i-1}, a[j] > a[i]
        rep(i,1,n){//ALL a[j] > a[i], j<i
            //若栈非空 且 当前a[i] 小于 栈顶元素，则出栈
            while(!stk.empty() && a[stk.top()] > a[i]) 
                stk.pop();

            //若栈非空，则l[i]是栈顶元素+1；
            //若栈空，则l[i]是1（因为a[i]左侧的所有元素都大于a[i]，a[i]作为最小最左元素的区间向左可以延伸到1
            //所以a[i]的极左下标是1
            if(!stk.empty()) 
                l[i] = stk.top()+1;//第一个小于等于a[i]的极左下标+1
            else 
                l[i] = 1; 

            //当前元素a[i]下标i入栈
            stk.push(i);
        }

        //栈清空
        while(!stk.empty()) 
            stk.pop();

        //计算每个a[i]作为区间中最左最小元素的区间的 极右边界r[i]
        rrep(i,n,1){//a[i]<=a[j],i<j 
            while(!stk.empty()&&a[i]<=a[stk.top()]) 
                stk.pop();
            
            if(!stk.empty()) 
                r[i]=max(i,stk.top()-1);
            else 
                r[i]=n;
            stk.push(i);
        }
        //栈清空
        while(!stk.empty()) 
            stk.pop();
        //答案
        ll ans=0;
        //答案减去所有区间的最小值的和
        //等价于 答案减去a[i] 乘以 a[i]是区间最左最小值的区间数量
        rep(i,1,n) 
            ans -= (ll)a[i]*(i-l[i]+1)*(r[i]-i+1);

        //计算每个a[i]作为区间中最左最大元素的区间的 极左边界l[i]
        rep(i,1,n){
            while(!stk.empty()&&a[stk.top()]<a[i]) 
                stk.pop();
            if(!stk.empty()) 
                l[i]=stk.top()+1;
            else 
                l[i]=1; 
            stk.push(i);
        }

        //栈清空
        while(!stk.empty()) 
            stk.pop();
        //计算每个a[i]作为区间中最左最大元素的区间的 极右边界r[i]
        rrep(i,n,1){
            while(!stk.empty()&&a[i]>=a[stk.top()]) 
                stk.pop();
            if(!stk.empty()) 
                r[i]=max(i,stk.top()-1);
            else 
                r[i]=n;
            stk.push(i);
        }
        //栈清空
        while(!stk.empty()) 
            stk.pop();
        //答案加上所有区间的最大值的和
        //等价于 答案加上a[i] 乘以 a[i]是区间最左最大值的区间数量
        rep(i,1,n) 
            ans += (ll)a[i]*(i-l[i]+1)*(r[i]-i+1);
        //输出答案
        cout<<ans<<endl;
    }
    return 0;
}
