#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Macro{
    vector<string> line;
    friend class Code;
    public:
    Macro(){
        line.clear();
    }
};

class MNT{
    string name;
    int kp,pp,mdtp,kpdtp;
    friend class Code;
    public:
    MNT(){
        name="";
        kp=pp=mdtp=kpdtp=0;
    }
    void clear(){
        name="";
        kp=pp=mdtp=kpdtp=0;
    }
};

class MDT{
    int index;
    string op1,op2,oper;
    friend class Code;
    public:
    MDT(){
        index=0;
        op1=op2=oper="";
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

class PNT{
    int index;
    string pname;
    friend class Code;
    public:
    PNT(){
        index=0;
        pname="";
    }
};

class PNTAB{
    int macrono;
    vector<PNT> tab;
    friend class Code;
    public:
    PNTAB(){
        tab.clear();
        macrono=0;
    }
};

class Code{
    vector<Macro> code;
    vector<MNT> mnt;
    vector<MDT> mdt;
    vector<KPDTAB> kpdtab;
    vector<PNTAB> pntab;
    vector<int> macroidx;
    public:
    Code(){
        code.clear();
    }
    void input(){
        fstream f;
        f.open("macro.txt",ios::in);
        string s;
        int count=1;
        int c=count;
        MNT row;
        int kp=0;
        bool mname=false;
        int pcount=0;
        int mcount=0;
        while(getline(f,s)){
            if(s=="MACRO"){
                row.mdtp=c;
                mname=true;
                continue;
            }
            Macro m;
            string str="";
            for(int i=0;i<s.length();i++){
                if(s[i]==' '){
                    m.line.push_back(str);
                    str="";
                }
                else if(s[i]=='&' || s[i]==','){
                    continue;
                }
                else if(mname==true && s[i]=='='){
                    row.kp+=1;
                    kp+=1;
                    int l=i-1,m=i+1;
                    string p="",v="";
                    while(s[l]!='&'){
                        p+=s[l];
                        l-=1;
                    }
                    reverse(p.begin(),p.end());
                    while(m<s.length() && s[m]!=','){
                        v+=s[m];
                        m+=1;
                    }
                    kpdtab.push_back(KPDTAB(kp,p,v));
                    str+=s[i];
                }
                else{
                    str+=s[i];
                }
            }
            m.line.push_back(str);
            code.push_back(m);
            if(mname==true){
                PNTAB t;
                mcount+=1;
                t.macrono=mcount;
                for(int l=1;l<code[count-1].line.size();l++){
                    PNT temp;
                    string pnt=code[count-1].line[l];
                    auto it=find(pnt.begin(),pnt.end(),'=');
                    if(it==pnt.end()){
                        pcount+=1;
                        temp.index=pcount;
                        temp.pname=pnt;
                    }
                    else{
                        pcount+=1;
                        int ind=it-pnt.begin();
                        int k=ind;
                        temp.index=pcount;
                        temp.pname=pnt.substr(0,ind);
                    }
                    t.tab.push_back(temp);
                }
                pntab.push_back(t);
                pcount=0;
            }
            if(mname==true){
                macroidx.push_back(count-1);
                row.name=code[count-1].line[0];
                int pos=code[0].line.size()-1-row.kp;
                row.pp=pos<=0?0:pos;
                row.kpdtp=row.kp==0?0:kp-row.kp+1;
                mnt.push_back(row);
                row.clear();
                mname=false;
                c-=1;
            }
            count+=1;
            c+=1;
        }
        f.close();
    }
    void display_MNT(){
        fstream f;
        f.open("mnt.txt",ios::out);
        f<<right<<setw(20)<<"MNT"<<endl;
        f<<left<<setw(8)<<"Name";
        f<<left<<setw(8)<<"PP";
        f<<left<<setw(8)<<"KP";
        f<<left<<setw(8)<<"MDTP";
        f<<left<<setw(8)<<"KPDTP"<<endl;
        for(int i=0;i<mnt.size();i++){
            f<<left<<setw(8)<<mnt[i].name;
            f<<left<<setw(8)<<mnt[i].pp;
            f<<left<<setw(8)<<mnt[i].kp;
            f<<left<<setw(8)<<mnt[i].mdtp;
            if(mnt[i].kpdtp==0){
                f<<left<<setw(8)<<"-";
            }
            else{
                f<<left<<setw(8)<<mnt[i].kpdtp;
            }
            f<<endl;
        }
        f.close();
    }
    void display_KPDTAB(){
        fstream f;
        f.open("kpdtab.txt",ios::out);
        f<<right<<setw(14)<<"KPDTAB"<<endl;
        f<<left<<setw(8)<<"Index";
        f<<left<<setw(12)<<"Parameters";
        f<<left<<setw(8)<<"Value";
        f<<endl;
        for(int i=0;i<kpdtab.size();i++){
            f<<left<<setw(8)<<kpdtab[i].index;
            f<<left<<setw(12)<<kpdtab[i].param;
            f<<left<<setw(8)<<kpdtab[i].value;
            f<<endl;
        }
        f.close();
    }
    void display_PNTAB(){
        fstream f;
        f.open("pntab.txt",ios::out);
        for(int i=0;i<pntab.size();i++){
            f<<setw(15)<<"PNTAB for MACRO "<<pntab[i].macrono<<endl;
            for(int j=0;j<pntab[i].tab.size();j++){
                f<<left<<setw(3)<<pntab[i].tab[j].index<<" ";
                f<<left<<setw(3)<<pntab[i].tab[j].pname;
                f<<endl;
            }
            f<<endl;
        }
        f.close();
    }
    void create_MDT(){
        int l=0;
        int idx=0;
        int lcount=0;
        for(int i=0;i<code.size();i++){
            if(i==macroidx[l]){
                l+=1;
                continue;
            }
            MDT m;
            bool op=false;
            lcount+=1;
            for(int j=0;j<code[i].line.size();j++){
                m.index=lcount;
                if(code[i].line[j]=="MEND"){
                    m.oper="MEND";
                    break;
                }
                if(op==false){
                    m.oper=code[i].line[j];
                    op=true;
                }
                else{
                    int idx=getidx(code[i].line[j],l-1);
                    if(m.op1==""){
                        if(idx==-1){
                            m.op1=code[i].line[j];
                        }
                        else{
                            m.op1="(P,"+to_string(idx+1)+')';
                        }
                    }
                    else{
                        if(idx==-1){
                            m.op2=code[i].line[j];
                        }
                        else{
                            m.op2="(P,"+to_string(idx+1)+')';
                        }
                    }
                }
            }
            mdt.push_back(m);
        }
    }
    int getidx(string p,int n){
        for(int i=0;i<pntab[n].tab.size();i++){
            if(pntab[n].tab[i].pname==p){
                return i;
            }
        }
        return -1;
    }
    void display_MDT(){
        fstream f;
        f.open("mdt.txt",ios::out);
        for(int i=0;i<mdt.size();i++){
            f<<mdt[i].index<<" "<<mdt[i].oper<<" "<<mdt[i].op1<<" "<<mdt[i].op2<<endl;
        }
        f.close();
    }
};

int main(){
    Code obj;
    obj.input();
    obj.display_MNT();
    obj.display_KPDTAB();
    obj.display_PNTAB();
    obj.create_MDT();
    obj.display_MDT();
    return 0;
}