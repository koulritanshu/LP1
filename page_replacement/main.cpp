#include <bits/stdc++.h>
using namespace std;

class Page{
    int n;
    vector<int> sequence;
    int fifopagefaults = 0;
    int frameSize;
    int lrupagefaults = 0;
    int optimalpagefaults = 0;
public:
    void addPage(){
        cout << ">> Enter the frameSize: ";
        cin >> frameSize;
        cout << ">> Enter the number of pages: ";
        cin >> n;
        cout << ">> Enter the pages sequentially." << endl;
        for(int i=0;i<n;i++){
            int x;
            cin >> x;
            sequence.push_back(x);
        }
    }
    void optimal(){
        cout << "---------------------------------------------------------------\n";
        map<int,bool>mp;
        mp.clear();
        int curr_size = 0;
        map<int,int> order;
        for(int i=0;i<n;i++){
            cout << "\nCurrent frames\n";
            cout << "[";
            for(auto i:mp){
                if(i.second == true){
                    cout << i.first << ", ";        
                }
            }
            cout << "]" << endl;
            cout << ">> Looking for page: " << sequence[i] << endl; 
            if(mp[sequence[i]]==true){
                order[sequence[i]] = i;
                cout << ">> Page hit occured." << endl;
            }
            else{
                cout << ">> Page fault occured." << endl;
                order[sequence[i]] = i;
                optimalpagefaults++;
                if(curr_size < frameSize){
                    mp[sequence[i]] = true;
                    curr_size++;
                }
                else{
                    vector<int> ahead;
                    for(int j=(i+1);j<n;j++){
                        if(mp[sequence[j]]==true&&(find(ahead.begin(),ahead.end(),sequence[j])==ahead.end())){
                            ahead.push_back(sequence[j]);
                        }
                    }
                    if(ahead.size()==frameSize){
                        // replace the last element
                        mp[sequence[i]] = true;
                        mp[ahead[ahead.size()-1]] = false;
                        order[ahead[ahead.size()-1]] = INT_MAX;
                    }
                    else{
                        // find not occuring frames and then apply fifo
                        vector<int> notOccuring;
                        for(auto it:mp){
                            if((find(ahead.begin(),ahead.end(),it.first)==ahead.end())&&it.second==true){
                                notOccuring.push_back(it.first);
                            }
                        }
                        // find one having least order[i] value
                        int element = -1;
                        int value = INT_MAX;
                        for(int j=0;j<notOccuring.size();j++){
                            if(value > order[notOccuring[j]]){
                                value = order[notOccuring[j]];
                                element = notOccuring[j];
                            }
                        }
                        mp[element] =  false;
                        mp[sequence[i]] = true;
                    }
                }
            }
            cout << endl;
        }
        cout << ">> Number of optimal page faults = " << optimalpagefaults << endl;
        cout << ">> Number of optimal page hits = " << n - optimalpagefaults << endl;
        cout << "---------------------------------------------------------------\n";
    }
    void fifo(){
        cout << "---------------------------------------------------------------\n";
        queue<int> q;
        map<int,bool> mp;
        int curr_size = 0;
        for(int i=0;i<n;i++){
            cout << "\nCurrent frames\n";
            cout << "[";
            for(auto i:mp){
                if(i.second == true){
                    cout << i.first << ", ";        
                }
            }
            cout << "]" << endl;
            cout << ">> Looking for page: " << sequence[i] << endl; 
            if(mp[sequence[i]]!=true){
                cout << ">> Page Fault occured." << endl;
                fifopagefaults++;
                if(curr_size<frameSize){
                    q.push(sequence[i]);
                    mp[sequence[i]] = true;
                    curr_size++;
                }
                else{
                    int front = q.front();
                    q.pop();
                    mp[front] = false;
                    mp[sequence[i]] = true;
                    q.push(sequence[i]);
                }
            }
            else{
                cout << ">> Page Hit occured." << endl;
            }
            cout<<endl;
        }
        cout << ">> Number of page faults = " << fifopagefaults << endl;
        cout << ">> Number of page hits = " << n - fifopagefaults << endl;
        cout << "---------------------------------------------------------------\n";
    }
    void lru(){
        cout << "---------------------------------------------------------------\n";
        int curr_size = 0;
        map<int,bool> mp;
        vector<int> lookup;
        for(int i=0;i<n;i++){
            cout << "\nCurrent frames\n";
            cout << "[";
            for(auto i:mp){
                if(i.second == true){
                    cout << i.first << ", ";        
                }
            }
            cout << "]" << endl;
            cout << ">> Looking for page: " << sequence[i] << endl << endl;
            if(mp[sequence[i]]==true){
                cout << ">> Page hit occured." << endl;
                vector<int> temp;
                for(int i=0;i<lookup.size();i++){
                    if(lookup[i]!=sequence[i]){
                        temp.push_back(lookup[i]);
                    }
                }
                temp.push_back(sequence[i]);
                lookup = temp;
            }
            else{
                cout << ">> Page Fault occured." << endl;
                lrupagefaults++;
                if(curr_size<frameSize){
                    curr_size++;
                    mp[sequence[i]]=true;
                    lookup.push_back(sequence[i]);
                }
                else{
                    int to_remove = lookup[0];
                    reverse(lookup.begin(),lookup.end());
                    lookup.pop_back();
                    reverse(lookup.begin(),lookup.end());
                    mp[to_remove] = false;
                    lookup.push_back(sequence[i]);
                    mp[sequence[i]] = true;
                }
            }
            cout<<endl;
        }
        cout << ">> Number of page faults = " << lrupagefaults << endl;
        cout << ">> Number of page hits = " << n - lrupagefaults << endl;
        cout << "---------------------------------------------------------------\n";
    }
};

int main()
{
    Page p1;
    p1.addPage();
    cout << "\t\tRUNNING FIFO\n\n\n";
    p1.fifo();
    cout << "\t\tRUNNING LRU\n\n\n";
    p1.lru();
    cout << "\t\tRUNNING OPTIMAL\n\n\n";
    p1.optimal();
    return 0;
}
