#include <bits/stdc++.h>
using namespace std;

class Process{
    vector<int> process_id;
    vector<int> arrivalTime;
    vector<int> completionTime;
    vector<int> burstTime;
    vector<int> tat;
    vector<int> wt;
    vector<int> priority;
    double avgtatfcfs;
    double avgwtfcfs;
    double avgtatsjf;
    double avgwtsjf;
    double avgwtrr;
    double avgtatrr;
    double avgtatpr;
    double avgwtpr;
    int n;
public:
    static bool cmp(pair<int,int> &a, pair<int,int> &b){
        if(a.first == b.first){
            return a.second < b.second;
        }
        return a.first < b.first;
    }
    void accept(){
        cout << ">> Enter the number of processes: ";
        cin >> n;
        for(int i=0;i<n;i++){
            int pid,at,bt,pt;
            cout << ">> Enter the process id: ";
            cin >> pid;
            cout << ">> Enter the arrival time: ";
            cin >> at;
            cout << ">> Enter the burst time: ";
            cin >> bt;
            cout << ">> Enter the priority: ";
            cin >> pt;
            priority.push_back(pt);
            process_id.push_back(pid);
            arrivalTime.push_back(at);
            burstTime.push_back(bt);
        }
        completionTime = vector<int>(n);
        tat = vector<int>(n);
        wt = vector<int>(n);
    }
    void fcfs(){
        vector<string> v;
        vector<pair<int,int>> arrId;
        for(int i=0;i<n;i++){
            arrId.push_back({arrivalTime[i],process_id[i]});
        }
        sort(arrId.begin(),arrId.end(),cmp);
        int time = 0;
        for(int i=0;i<arrId.size();i++){
            if(arrId[i].first > time){
                time += (arrId[i].first - time);
                string curr = " | Idle " + to_string(time) + " | ";
                v.push_back(curr);
            }
            int currId = arrId[i].second;
            int currAt = arrId[i].first;
            int indi;
            for(int j=0;j<n;j++){
                if(currId == process_id[j] && currAt == arrivalTime[j]){
                    indi = j;
                    break;
                }
            }
            time += burstTime[indi];
            completionTime[indi] = time;
            tat[indi] = completionTime[indi] - arrivalTime[indi];
            wt[indi] = tat[indi] - burstTime[indi];
            string curr = " | ";
            curr += 'P';
            curr += to_string(currId);
            curr += " " + to_string(time) + " | ";
            v.push_back(curr);
        }
        cout << "ProcessID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
        for(int i=0;i<n;i++){
            cout << process_id[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << completionTime[i] << "\t\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
        }
        double avgtat = 0.0;
        double avgwt = 0.0;
        for(int i=0;i<n;i++){
            avgtat += tat[i];
            avgwt += wt[i];
        }
        avgtat /= n;
        avgwt /= n;
        cout << ">> Average TAT: " << avgtat << endl;
        cout << ">> Average WT: " << avgwt << endl;
        avgtatfcfs = avgtat;
        avgwtfcfs = avgwt;
        cout << "\nGantt Chart\n";
        for(int i=0;i<v.size();i++){
            cout<<v[i];
        }
        cout<<endl;
    }
    void sjf(){
        int t = 0;
        completionTime = vector<int>(n,0);
        wt = vector<int>(n,0);
        tat = vector<int>(n,0);
        int process_ = 0;
        vector<int> v;
        vector<int> burst(n);
        for(int i=0;i<n;i++){
            burst[i] = burstTime[i];
        }
        while(process_ != n){
            int mini = INT_MAX;
            int indi = -1;
            for(int i=0;i<n;i++){
                if(arrivalTime[i] <= t){
                    if(mini > burst[i] && burst[i] > 0){
                        mini = burst[i];
                        indi = i;
                    }
                }
            }
            if(mini == INT_MAX){
                v.push_back(-1);
                t++;
                continue;
            }
            v.push_back(indi);
            t++;
            burst[indi] -= 1;
            if(burst[indi] == 0){
                process_++;
                completionTime[indi] = t;
            } 
        }
        for(int i=0;i<n;i++){
            tat[i] = completionTime[i] - arrivalTime[i];
            wt[i] = tat[i] - burstTime[i];
        }
        cout << "ProcessID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
        for(int i=0;i<n;i++){
            cout << process_id[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << completionTime[i] << "\t\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
        }
        double avgtat = 0.0;
        double avgwt = 0.0;
        for(int i=0;i<n;i++){
            avgtat += tat[i];
            avgwt += wt[i];
        }
        avgtat /= n;
        avgwt /= n;
        cout << ">> Average TAT: " << avgtat << endl;
        cout << ">> Average WT: " << avgwt << endl;
        avgtatsjf = avgtat;
        avgwtsjf = avgwt;
        vector<string> gantt;
        int curr = 0;
        for(int i=0;i<v.size();i++){
            int j=i;
            for(j=i;j<v.size();j++){
                if(v[j]==v[i]){
                    curr++;
                }
                else{
                    if(v[i]==-1){
                        string current = " | Idle " + to_string(curr) + " | ";
                        gantt.push_back(current);
                    }
                    else{
                        string current = " | P" + to_string(process_id[v[i]]) + " " + to_string(curr) + " | ";
                        gantt.push_back(current);
                    }
                    i = j-1;
                    break;
                }
            }
            if(j==v.size()){
                if(v[i]==-1){
                    string current = " | Idle " + to_string(curr) + " | ";
                    gantt.push_back(current);
                }
                else{
                    string current = " | P" + to_string(process_id[v[i]]) + " " + to_string(curr) + " | ";
                    gantt.push_back(current);
                }
                break;
            }
        }
        cout << "\nGantt Chart\n";
        for(int i=0;i<gantt.size();i++){
            cout<<gantt[i];
        }
        cout<<endl;
    }
    void roundRobin(){
        completionTime = vector<int>(n,0);
        wt = vector<int>(n,0);
        tat = vector<int>(n,0);
        vector<int> burst(n);
        for(int i=0;i<n;i++){
            burst[i] = burstTime[i];
        }
        int quantum;
        cout << ">> Enter the quantum for round robin: ";
        cin >> quantum;
        queue<int> q;
        int time = 0;
        int front;
        int process_ = 0;
        for(int i=0;i<n;i++){
            if(arrivalTime[i]<=time){
                q.push(i);
            }
        }
        while(process_ != n){
            front = q.front();
            q.pop();
            int cntr = 0;
            while(cntr != quantum && burst[front]!=cntr){
                time++;
                cntr++;
                for(int i=0;i<n;i++){
                    if(burst[i] > 0 && arrivalTime[i] == time){
                        q.push(i);
                    }
                }
            }
            burst[front] -= cntr;
            if(burst[front] == 0){
                completionTime[front] = time;
                process_++;
            }
            else{
                q.push(front);
            }
        }
        for(int i=0;i<n;i++){
            tat[i] = completionTime[i] - arrivalTime[i];
            wt[i] = tat[i] - burstTime[i];
        }
        cout << "ProcessID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
        for(int i=0;i<n;i++){
            cout << process_id[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << completionTime[i] << "\t\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
        }
        double avgtat = 0.0;
        double avgwt = 0.0;
        for(int i=0;i<n;i++){
            avgtat += tat[i];
            avgwt += wt[i];
        }
        avgtat /= n;
        avgwt /= n;
        cout << ">> Average TAT: " << avgtat << endl;
        cout << ">> Average WT: " << avgwt << endl;
        avgtatrr = avgtat;
        avgwtrr = avgwt;
    }
    void pr(){
        vector<int> burst(n);
        for(int i=0;i<n;i++){
            burst[i] = burstTime[i];
        }
        int time = 0;
        int process_ = 0;
        while(process_ != n){
            int current_max_priority = INT_MAX;
            int index = -1;
            for(int i=0;i<n;i++){
                if(time >= arrivalTime[i] && current_max_priority > priority[i] && burst[i] > 0) {
                    current_max_priority = priority[i];
                    index = i;
                }
            }
            if (index == -1) {
                time++;
            }
            else{
                time += burst[index];
                burst[index] = 0;
                completionTime[index] = time;
                process_++;
            }
        }
        for(int i=0;i<n;i++){
            tat[i] = completionTime[i] - arrivalTime[i];
            wt[i] = tat[i] - burstTime[i];
        }
        cout << "ProcessID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
        for(int i=0;i<n;i++){
            cout << process_id[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << completionTime[i] << "\t\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
        }
        double avgtat = 0.0;
        double avgwt = 0.0;
        for(int i=0;i<n;i++){
            avgtat += tat[i];
            avgwt += wt[i];
        }
        avgtat /= n;
        avgwt /= n;
        cout << ">> Average TAT: " << avgtat << endl;
        cout << ">> Average WT: " << avgwt << endl;
        avgtatpr = avgtat;
        avgwtpr = avgwt;
    }
};

int main()
{
    Process obj;
    cout << "---------------------INPUT---------------------\n";
    obj.accept();
    cout << "---------------------FCFS----------------------\n";
    obj.fcfs();
    cout << "----------------------SJF----------------------\n";
    obj.sjf();
    cout << "----------------------RR-----------------------\n";
    obj.roundRobin();
    cout << "----------------------PR-----------------------\n";
    obj.pr();
    return 0;
}