#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class MDT{
    int index;
    string oper,op1,op2;
    friend class Code;
    public:
    MDT(){
        index=0;
        oper=op1=op2="";
    }
};

class KPDTAB{
    int index;
    string param,value;
    friend class Code;
    public:
    KPDTAB(){
        index=0;
        param=value="";
    }
    KPDTAB(int i,string p,string v){
        index=i;
        param=p;
        value=v;
    }
};

class MNT{
    string name;
    int kp,pp,mdtp,kpdtp;
    friend class Code;
    public:
    MNT(){
        name="";
        kp=pp=mdtp=kpdtp=-1;
    }
    void clear(){
        name="";
        kp=pp=mdtp=kpdtp=-1;
    }
};

class Pass2{
    string sign,oper,op1,op2;
    friend class Code;
    public:
    Pass2(){
        sign="+";
        oper=op1=op2="";
    }
};

class Call{
    vector<string> line;
    friend class Code;
    public:
    Call(){
        line.clear();
    }
};

class Code{
    vector<Pass2> ans;
    vector<Call> call;
    vector<MDT> mdt;
    vector<MNT> mnt;
    vector<KPDTAB> kpdtab;
    public:
    Code(){
        call.clear();
        mdt.clear();
        mnt.clear();
    }
    void input(){
        fstream f;
        f.open("macrocall.txt",ios::in);
        string s;
        while(getline(f,s)){
            string str="";
            Call pt;
            for(int i=0;i<s.length();i++){
                if(s[i]==' '){
                    pt.line.push_back(str);
                    str="";
                }
                else if(s[i]==',' || s[i]=='&'){
                    continue;
                }
                else{
                    str+=s[i];
                }
            }
            pt.line.push_back(str);
            call.push_back(pt);
        }
        f.close();
    }
    void createmdt(){
        fstream f;
        f.open("mdt.txt",ios::in);
        string s;
        while(getline(f,s)){
            string str="";
            MDT m;
            for(int i=0;i<s.length();i++){
                if(s[i]==' '){
                    if(m.index==0){
                        m.index=stoi(str);
                    }
                    else if(m.oper.length()==0){
                        m.oper=str;
                    }
                    else{
                        m.op1=str;
                    }
                    str="";
                }
                else{
                    str+=s[i];
                }
            }
            if(m.oper.length()==0){
                m.oper=str;
            }
            else{
                m.op2=str;
            }
            mdt.push_back(m);
        }
        f.close();
    }
    void createmnt(){
        fstream f;
        f.open("mnt.txt",ios::in);
        string s;
        getline(f,s);
        while(getline(f,s)){
            string str="";
            MNT m;
            for(int i=0;i<s.length();i++){
                if(s[i]==' '){
                   if(m.name.length()==0){
                        m.name=str;
                   }
                   else if(m.pp==-1){
                        m.pp=stoi(str);
                   }
                   else if(m.kp==-1){
                        m.kp=stoi(str);
                   }
                   else{
                        m.mdtp=stoi(str);
                   }
                   str="";
                   while(s[i]==' ' && i<s.length()){
                       i++;
                   }
                }
                str+=s[i];
            }
            if(str=="-"){
                m.kpdtp=0;
            }
            else{
                m.kpdtp=stoi(str);
            }
            mnt.push_back(m);
        }
        f.close();
    }
    void createkpdtab(){
        fstream f;
        f.open("kpdtab.txt",ios::in);
        string s;
        getline(f,s);
        while(getline(f,s)){
            string str="";
            KPDTAB m;
            for(int i=0;i<s.length();i++){
                if(s[i]==' '){
                   if(m.index==0){
                        m.index=stoi(str);
                   }
                   else{
                        m.param=str;
                   }
                   str="";
                   while(s[i]==' ' && i<s.length()){
                       i++;
                   }
                }
                str+=s[i];
            }
            if(m.param.length()==0){
                m.param=str;
            }
            else{
                m.value=str;
            }
            kpdtab.push_back(m);
        }
        f.close();
    }
    void macroprocess(int i,vector<string>& aptab){
        while(mdt[i].oper!="MEND"){
            Pass2 p;
            p.oper=mdt[i].oper;
            if(mdt[i].op1[0]=='('){
                string str=mdt[i].op1;
                str=str.substr(3,str.length()-4);
                p.op1=aptab[stoi(str) - 1];
            }
            else{
                p.op1=mdt[i].op1;
            }
            if(mdt[i].op2[0]=='('){
                string str=mdt[i].op2;
                str=str.substr(3,str.length()-4);
                p.op2=aptab[stoi(str)-1];
            }
            else{
                p.op2=mdt[i].op2;
            }
            ans.push_back(p);
            i+=1;
            //displayMacroProcess();
        }
    }
    void createmachinecode(){
        for(int i=0;i<call.size();i++){
            int idx=searchmnt(call[i].line[0]);
            vector<string> aptab(mnt[idx].pp+mnt[idx].kp,"");
            int kpidx=mnt[i].kpdtp;
            int ppidx=1;
            for(int j=1;j<=mnt[i].pp;j++){
                if(find(call[i].line[ppidx].begin(),call[i].line[ppidx].end(),'=')!=call[i].line[ppidx].end()){
                    break;
                }
                aptab[j-1]=call[i].line[ppidx];
                ppidx+=1;
            }
            for(int j=mnt[i].pp+1;j<=aptab.size();j++){
                if(aptab[j-1].length()==0){
                    aptab[j-1]=kpdtab[kpidx-1].value;
                }
                if(ppidx<call[i].line.size()){
                    string str=call[i].line[ppidx];
                    auto it=find(str.begin(),str.end(),'=');
                    string a=str.substr(0,it-str.begin());
                    string b=str.substr(it-str.begin()+1);
                    int q=searchkpdtab(a,mnt[idx].kpdtp);
                    //cout<<a<<" "<<b<<endl;
                    //cout<<mnt[idx].pp<<" "<<q<<" "<<mnt[idx].kpdtp<<endl;
                    aptab[mnt[idx].pp+q-mnt[idx].kpdtp]=b;
                    ppidx+=1;
                }
                kpidx+=1;
            }
            cout<<endl;
            displayMachineCode(aptab);
            macroprocess(mnt[idx].mdtp-1,aptab);
        }
        
    }
    void display(){
        for(int i=0;i<call.size();i++){
            for(int j=0;j<call[i].line.size();j++){
                cout<<call[i].line[j]<<" ";
            }
            cout<<endl;
        }
    }
    void displayMachineCode(vector<string> v){
        for(int i=0;i<v.size();i++){
            cout<<i+1<<" "<<v[i]<<endl;
        }
    }
    void display_MDT(){
        for(int i=0;i<mdt.size();i++){
            cout<<mdt[i].index<<" "<<mdt[i].oper<<" "<<mdt[i].op1<<" "<<mdt[i].op2<<endl;
        }
    }
    void display_KPDTAB(){
        for(int i=0;i<kpdtab.size();i++){
            cout<<kpdtab[i].index<<" "<<kpdtab[i].param<<" "<<kpdtab[i].value<<endl;
        }
    }
    void display_MNT(){
        for(int i=0;i<mnt.size();i++){
            cout<<mnt[i].name<<" "<<mnt[i].pp<<" "<<mnt[i].kp<<" "<<mnt[i].mdtp<<" "<<mnt[i].kpdtp<<endl;
        }
    }
    int searchmnt(string mname){
        for(int i=0;i<mnt.size();i++){
            if(mnt[i].name==mname){
                return i;
            }
        }
        return -1;
    }
    int searchkpdtab(string pname,int idx){
        for(int i=idx-1;i<kpdtab.size();i++){
            if(kpdtab[i].param==pname){
                return kpdtab[i].index;
            }
        }
        return -1;
    }
    void displayMacroProcess(){
        for(int i=0;i<ans.size();i++){
            cout<<ans[i].sign<<" "<<ans[i].oper<<" "<<ans[i].op1<<" "<<ans[i].op2<<endl;
        }
    }
};

int main(){
    Code obj;
    obj.input();
    cout<<endl;
    obj.display();

    cout<<endl;
    obj.createmdt();
    obj.display_MDT();

    cout<<endl;
    obj.createmnt();
    obj.display_MNT();

    cout<<endl;
    obj.createkpdtab();
    obj.display_KPDTAB();

    cout<<endl;
    obj.createmachinecode();
    cout<<endl;
    obj.displayMacroProcess();
    return 0;
}