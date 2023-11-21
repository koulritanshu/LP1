#include <bits/stdc++.h>
using namespace std;

class Ring{
    int total;
    vector<bool> arr;
public:
    Ring(int n){
        total = n;
        arr = vector<bool>(n,true);
    }
    void up(int n){
        arr[n-1] = true;
    }
    void down(int n){
        arr[n-1] = false;
    }
    void election(int n){
        if(arr[n-1] == false){
            cout << "Node " << n+1 << " cannot start election.\n";return;
        }
        cout << "Election started by node " << n+1 << endl;
        int start = n-1;
        int ptr = (start + 1) % total;
        int last_true = start;
        vector<int>process_id_array;
        while (start != ptr){
            if(arr[ptr] == true){
                cout << "Node " << last_true + 1 << " sent message to node " << ptr + 1 << endl;
                process_id_array.push_back(last_true+1);
                cout << "Process ID Array is: ";
                for(auto i:process_id_array) cout << i << " ";
                cout << endl;
                last_true = ptr;
            }
            ptr = (ptr + 1)%total;
        }
        cout << "Node " << last_true + 1 << " sent message to node " << ptr + 1 << endl;
        process_id_array.push_back(last_true+1);
        cout << "Process ID Array is: ";
        for(auto i:process_id_array) cout << i << " ";
        cout << endl;
        int maxi = INT_MIN;
        for(int i=arr.size()-1;i>=0;i--){
            if(arr[i] == true){
                maxi = i;
                break;
            }
        }
        cout << "Election won by " << maxi + 1 << endl;
        cout << "Node " << maxi + 1 << " tells other nodes that it has won the election." << endl;
    }
};

class Bully{
    int total;
    vector<bool> arr;
public:
    Bully(int n){
        total = n;
        arr = vector<bool>(n,true);
    }
    void up(int n){
        arr[n-1] = true;
    }
    void down(int n){
        arr[n-1] = false;
    }
    void election(int n){
        if(n > total){
            return;
        }
        if(arr[n-1] == false){
            cout << "Node " << n + 1 << " cannot start an election.\n";return;
        }
        for(int i=n;i<total;i++){
            cout<<"Election message sent by " << n << " to " << i + 1 << endl;
        }
        for(int i=n;i<total;i++){
            if(arr[i] == true){
                cout<<"OK message sent by " << i+1 << " to " << n << endl;
            }
        }
        for(int i=n;i<total;i++){
            if(arr[i] == true){
                election(i+1);
                return;
            }
        }
        int maxi = INT_MIN;
        for(int i=arr.size()-1;i>=0;i--){
            if(arr[i]==true){
                maxi=i+1;break;
            }
        }
        cout << "No ok message received by " << maxi << endl;
        cout << "Election won by " << maxi << endl;
    }
};

int main()
{
    Ring obj(10);
    obj.down(10);
    obj.down(6);
    obj.election(4);
    Bully obj2(6);
    obj2.down(6);
    // obj2.down(5);
    obj2.election(2);
    return 0;
}