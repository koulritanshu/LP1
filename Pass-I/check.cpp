#include <bits/stdc++.h>
// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;
using namespace std;
#define MOD 1000000007
#define endl "\n"
// typedef int512_t ll;
typedef long long ll;

//========================NUMBER OF COMPOSITE DIVISORS==========================
// IF NUMBER HAS K PRIME DIVISORS, THEN 
// NUMBER OF COMPOSITE DIVISORS = (1<<K) - K - 1 
//==============================================================================

ll sum_of_digits(ll number){
    // sum of digits till only one digit remains
    ll cal = number % 9ll;
    if(cal == 0ll){
        return 9ll;
    }
    else return cal;
}

bool check(int a, int b, int c){
    // checks whether a can be made divisble to b by subtracting a multiple of c
    // from a and b
    ll cal = __gcd(b,c);
    if(a % cal == 0) return true;
    return false;
}

ll power(ll a, ll b, ll mod = MOD)
{
    // USING BINARY EXPONENTIATION
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b = b / 2;
    }
    return res;
}

template <class T>
void disp_array(ll n, T arr[])
{
    for (ll i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <class T>
void input(ll n, T arr[])
{
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
}

int power(int x, unsigned int y)
{
    // WITHOUT MODULUS
    if (y == 0)
        return 1;
    int temp = power(x, y / 2);
    if (y % 2 == 0)
        return temp * temp;
    else
        return x * temp * temp;
}

template<class T,class X>
void disp_pair(pair<T,X> p){
    cout << p.first << " " << p.second << endl;
}

template<class T>
void disp_vector(vector <T> v){
    for(auto i:v){
        cout << i << " ";
    }
    cout << endl;
}

ll binary_search(ll n, ll arr[], ll index){
    // finds first greater element than current element
    ll target = arr[index];
    ll start = 0ll;
    ll end = n-1ll;
    ll ans = -1ll;
    while(start <= end){
        ll mid = (start+end)/2;
        if(arr[mid] + target > 0 && mid > index){
            ans = mid; 
            end = mid-1;
        }
        else{
            start = mid+1;
        }
    }
    return ans;
}

//========================SUBSEQUENCES RECURSIVELY=============================
vector<vector<ll>> subseq;
void generate_subseq(ll ind, ll n, ll arr[], vector<ll> curr){
    if(ind == n){
        subseq.push_back(curr); return;
    }
    curr.push_back(arr[ind]);
    generate_subseq(ind+1,n,arr,curr);
    curr.pop_back();
    generate_subseq(ind+1,n,arr,curr);
}
//==========================O(2^N)=============================================

void solve()
{
    string s = "Manshu Khajuria weds Siddhesh Dhadse";
    stringstream st(s);
    string x;
    st >> x;
    cout << x << endl;
    // string x;
    st >> x;
    cout << x << endl;
    // string x;
    st >> x;
    cout << x << endl;
    // string x;
    st >> x;
    cout << x << endl;
    st >> x;
    cout << x << endl;
    st >> x;
    cout << x << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}