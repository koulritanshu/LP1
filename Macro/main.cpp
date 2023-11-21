#include <bits/stdc++.h>
using namespace std;

// INCR &MEM_VAL &INCR_VAL = &REG = &AREGS

string findval(vector<string>&v, int ind){
    int tot = 0;
    for(int i=0;i<v.size();i++){
        if(v[i][0] == '&'){
            tot++;
        }
        if(tot == ind){
            return v[i+2];
        }
    }
    return "";
}

int findfunc(vector<string> &v, string curr){
    int tot = 0;
    bool found = false;
    for(int i=0;i<v.size();i++){
        if(v[i]=="=") continue;
        else{
            if(v[i] == curr){
                tot++;
                found = true;
                break;
            }
            else tot++;
        }
    }
    if(!found) return -1;
    return tot;
}
// a = b c d e 
// a b c d e 

int main()
{
    vector<string> mdt;
    vector<string> mnt;
    vector<string> kptab;    
    vector<string> pntab;
    fstream obj;
    obj.open("input2.txt",ios::in);
    unordered_map<string,vector<string>> mp;
    string macro_name = "";
    vector<string> macronames;
    bool insideMacro = false;
    while(!obj.eof()){
        string s;
        getline(obj,s);
        if(s == "MACRO"){
            insideMacro = true; 
            getline(obj,s);
            vector<string> v;
            string curr = "";
            for(int i=0;i<s.size();i++){
                if(s[i]==' '){
                    v.push_back(curr);
                    curr = "";
                }
                else{
                    curr += s[i];
                }
            }
            v.push_back(curr);
            macro_name = v[0];
            macronames.push_back(macro_name);
            reverse(v.begin(),v.end());
            v.pop_back();
            reverse(v.begin(),v.end());
            mp[macro_name] = v;
        }
        else if(s == "MEND"){
            mdt.push_back("MEND");
            insideMacro = false;
        }
        else if(insideMacro){
            vector<string> v;
            string curr = "";
            for(int i=0;i<s.size();i++){
                if(s[i]==' '){
                    v.push_back(curr);
                    curr = "";
                }
                else{
                    curr += s[i];
                }
            }
            v.push_back(curr);
            vector<string> out;
            for(int i=0;i<v.size();i++){
                int x = findfunc(mp[macro_name],v[i]);
                if(x == -1){
                    out.push_back(v[i]);
                }
                else{
                    string tempo = "(P, " + to_string(x) + ")";
                    out.push_back(tempo);
                }
            }
            curr = "";
            for(int i=0;i<out.size();i++){
                curr += out[i];
                if(i!=out.size()-1){
                    curr = curr + ' ';
                }
            }
            mdt.push_back(curr);
        }
    }    
    // for(auto i:mp){
    //     cout<<i.first<<" ";
    //     for(auto j:i.second){
    //         cout<<j<<" ";
    //     }cout<<endl;
    // }
    cout << "----------------MDT----------------\n"; 
    for(auto i:mdt){
        cout<<i<<endl;
    }
    for(auto j:macronames){
        string macro_name = j;
        vector<string> parameters = mp[j];
        pntab.push_back(macro_name);
        for(auto j:parameters){
            if(j == "=" || j[0] != '&') continue;
            pntab.push_back(j);
        }
    }
    cout << "---------------PNTAB---------------\n";
    for(auto i:pntab){
        cout<<i<<endl;
    }
    cout << "---------------KPTAB---------------\n";
    vector<pair<string,string>> kp;
    for(auto i:macronames){
        vector<string> parameters = mp[i];
        for(int j=0;j<parameters.size();j++){
            if(parameters[j] == "="){
                // previous one parameter and next one value
                pair<string,string> p;
                p.first = parameters[j-1];
                p.second = parameters[j+1];
                kp.push_back(p);
            }
        }
    }
    for(auto i:kp){
        string j = "";
        j += i.first + " " + i.second;
        kptab.push_back(j);
    }
    for(auto i:kptab){
        cout<<i<<endl;
    }
    cout << "----------------MNT----------------\n";
    for(auto i:macronames){
        string curr = "";
        curr += i;
        vector<string> parameters = mp[i];
        int total_parameters = 0;
        int kp = 0;
        int pp = 0;
        for(int j=0;j<parameters.size();j++){
            if(parameters[j] == "="){
                kp++;
            }
            else if(parameters[j][0]=='&'){
                total_parameters++;
            }
        }
        pp = total_parameters-kp;
        curr = curr + ' ' + to_string(kp) + ' ' + to_string(pp);
        // find index in kptab
        int knt = 0;
        for(int i=0;i<kptab.size();i++){
            // x = y ( x , y )
            string temp = kptab[i];
            string before = "";
            string after = "";
            bool space = false;
            for(int i=0;i<temp.size();i++){
                if(temp[i] == ' ') space = true;
                else if(space){
                    after += temp[i];
                }
                else{
                    before += temp[i];
                }
            }
            bool found = false;
            for(int j=0;j<parameters.size();j++){
                if(parameters[j] == "=" && parameters[j-1]==before&&parameters[j+1]==after){
                    found = true;
                    knt = i+1;
                    break;
                }
            }
            if(found){break;}
        }
        // find index in pntab
        int pnt = 0;
        for(int j=0;j<pntab.size();j++){
            if(pntab[j] == i){
                pnt = j+1;
                break;
            }
        }
        curr = curr + ' ' + to_string(knt) + ' ' + to_string(pnt);
        mnt.push_back(curr); 
    }
    for(auto i:mnt){
        cout<<i<<endl;
    }
    obj.close();
    cout << "xxxxxxxxxxxxxxxxxxxxNOW-PASS2xxxxxxxxxxxxxxxxxxxx\n";
    vector<string> aptab;
    vector<string> macroexpansion;
    // parameters i know already
    // i only need their calls 
    // then iterate from the start
    // map[macroname][parameter] = value
    // mover movem or whatever () , () 
    fstream obj2;
    obj2.open("input2.txt",ios::in);
    bool startfound = false;
    map<string,vector<string>> mp2;
    while(!obj2.eof()){
        string s;
        getline(obj2,s);
        if(s[0]=='S'&&s[1]=='T'&&s[2]=='A'&&s[3]=='R'){
            startfound = true;
        }
        else if(startfound){
            vector<string> v;
            string curr = "";
            for(int i=0;i<s.size();i++){
                if(s[i] == ' '){
                    v.push_back(curr);curr="";
                }
                else curr+=s[i];
            }
            v.push_back(curr);
            if(find(macronames.begin(),macronames.end(),v[0])!=macronames.end()){
                // parameters followed and their values
                for(int i=1;i<v.size();i++){
                    if(v[i] == "="){
                        mp2[v[0]].pop_back();
                    }
                    else{
                        mp2[v[0]].push_back(v[i]);
                    }
                }
            }
        }
    }
    int ind = 0;
    string macro = macronames[ind];
    for(auto i:mdt){
        string curr = i;
        if(curr == "MEND"){
            macroexpansion.push_back("+MEND");
            ind++;
            if(ind<macronames.size())
            macro = macronames[ind];
        }
        else{
            vector<string> line;
            string temp = "";
            for(int j=0;j<curr.size();j++){
                if(curr[j] == ' '){
                    line.push_back(temp);temp="";
                }
                else{
                    temp+=curr[j];
                }
            }
            line.push_back(temp);
            string ans = "";
            ans += '+';
            for(int j=0;j<line.size();j++){
                if(line[j][0] != '('){
                    ans += line[j] + ' ';
                }
                else{
                    j++;
                    int ind = line[j][0] - '0';ind--;
                    if(mp2.find(macro)!=mp2.end() && mp2[macro].size()-1>=ind){
                        ans += mp2[macro][ind] + ' ';
                    }
                    else{
                        ans += findval(mp[macro],ind+1) + ' ';
                    }
                }
            }
            macroexpansion.push_back(ans);
        }
    }
    for(auto i:macroexpansion){
        cout<<i<<endl;
    }
    ind = 0;
    macro = "";
    int cal = 0;
    string ans = "";
    for(auto i:pntab){
        ans = "";
        if(i[0]!='&'){
            cal=0;
            aptab.push_back(i);
            macro = i;
        }
        else{
            ans += i + ' ';
            if(mp2.find(macro)!=mp2.end() && mp2[macro].size()-1>=cal){
                ans += mp2[macro][cal];
            }
            else{
                ans += findval(mp[macro],cal+1);
            }
            aptab.push_back(ans);
            cal++;
        }
    }
    for(auto x:aptab){
        cout<<x<<endl;
    }
}