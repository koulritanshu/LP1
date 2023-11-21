#include <bits/stdc++.h>
using namespace std;

class pass1
{
public:
    void execute()
    {
        map<string, pair<string, string>> opcode;
        opcode["STOP"] = {"IS", "00"};
        opcode["ADD"] = {"IS", "01"};
        opcode["SUB"] = {"IS", "02"};
        opcode["MULT"] = {"IS", "03"};
        opcode["MOVER"] = {"IS", "04"};
        opcode["MOVEM"] = {"IS", "05"};
        opcode["COMP"] = {"IS", "06"};
        opcode["BC"] = {"IS", "07"};
        opcode["DIV"] = {"IS", "08"};
        opcode["READ"] = {"IS", "09"};
        opcode["PRINT"] = {"IS", "10"};
        opcode["START"] = {"AD", "01"};
        opcode["END"] = {"AD", "02"};
        opcode["ORIGIN"] = {"AD", "03"};
        opcode["EQU"] = {"AD", "04"};
        opcode["LTORG"] = {"AD", "05"};
        opcode["DC"] = {"DL", "01"};
        opcode["DS"] = {"DL", "02"};
        opcode["AREG"] = {"1", ""};
        opcode["BREG"] = {"2", ""};
        opcode["CREG"] = {"3", ""};
        opcode["DREG"] = {"4", ""};
        opcode["LT"] = {"1", ""};
        opcode["LE"] = {"2", ""};
        opcode["EQ"] = {"3", ""};
        opcode["GT"] = {"4", ""};
        opcode["GE"] = {"5", ""};
        opcode["ANY"] = {"6", ""};
        map<string,pair<int,string>> symtab;
        vector<pair<string,int>> littab;
        vector<string> pooltab;
        string label = "";
        string word, line;
        ifstream fin;
        fin.open("input.txt");
        ofstream fout;
        fout.open("ic.txt");
        int lc = -1;
        int litindex = 0;
        while(getline(fin, line)){
            stringstream st(line);
            st >> word;
            if(opcode.count(word) == 0){
                if(symtab.count(word) == 0){
                    symtab[word] = {lc, to_string(symtab.size() + 1)};
                }
                else{
                    symtab[word].first = lc;
                }
                label = word;
                st >> word;
            }
            string operation = word;
            if(operation == "START"){
                fout << "    ";
                fout << "(" << opcode[operation].first << ", " << opcode[operation].second << ") ";
                st >> word;
                fout << "(C, " << word << ")";
                try{
                    lc = stoi(word);
                }
                catch(exception e){
                    cout << "Exception in START\n";
                }
            }
            else if(operation == "END"){
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
                pooltab.push_back("#"+to_string(litindex+1));
                for(; litindex<littab.size();litindex++){
                    fout << lc << " ";
                    fout << "(" << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                    littab[litindex].second = lc;
                    string literal = littab[litindex].first;
                    string sublit = literal.substr(2,literal.length()-3);
                    fout << "(C, " << sublit << ") ";
                    fout << endl;
                    lc++;
                }
            }
            else if(operation == "LTORG"){
                pooltab.push_back("#" + to_string(litindex+1));
                for(; litindex < littab.size();litindex++){
                    fout << lc << " ";
                    fout << "(" << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                    littab[litindex].second = lc;
                    string literal = littab[litindex].first;
                    string sublit = literal.substr(2,literal.length()-3);
                    fout << "(C, " << sublit << ")";
                    lc++;
                    if(litindex!=littab.size()-1){
                        fout << endl;
                    }
                }
            }
            else if(operation == "EQU"){
                fout << "   ";
                fout << " No IC generated ";
                st >> word;
                int plusminusindex = 0;
                for(int i=0;i<word.size();i++){
                    if(word[i] == '-' || word[i] == '+'){
                        plusminusindex = i;
                        break;
                    }
                }
                char plusminus = '0';
                string beforesign;
                string aftersign;
                if(plusminusindex != 0){
                    plusminus = word[plusminusindex];
                    aftersign = word.substr(plusminusindex+1);
                }
                else{
                    beforesign = word.substr(0,word.length());
                }
                symtab[label].first = symtab[beforesign].first;
                if(plusminus == '+'){
                    try{
                        symtab[label].first += stoi(aftersign);
                        fout << "+" << aftersign << "\n";
                    }
                    catch(exception e){
                        cout << "Exception e\n";
                    }
                }   
                else{
                    try{
                        symtab[label].first -= stoi(aftersign);
                        fout << "-" << aftersign << "\n";
                    }
                    catch(exception e){
                        cout << "Exception e\n";
                    }
                }
            }
            else if(operation == "ORIGIN"){
                fout << "    ";
                fout << "(" << opcode[operation].first << ", " << opcode[operation].second << ") ";
                st >> word;
                int plusminusindex = 0;
                for(int i=0;i<word.size();i++){
                    if(word[i] == '-' || word[i] == '+'){
                        plusminusindex = i;
                        break;
                    }
                }
                char plusminus = '0';
                string beforesign;
                string aftersign;
                if(plusminusindex != 0){
                    plusminus = word[plusminusindex];
                    aftersign = word.substr(plusminusindex+1);
                }
                else{
                    beforesign = word.substr(0,word.length());
                }
                lc = symtab[beforesign].first;
                fout << "(S, " << symtab[beforesign].second << ")";
                if(plusminus == '+'){
                    try{
                        lc += stoi(aftersign);
                        fout << "+" << aftersign;
                    }
                    catch(exception e){
                        cout << "Exception e\n";
                    }
                }   
                else{
                    try{
                        lc -= stoi(aftersign);
                        fout << "-" << aftersign;
                    }
                    catch(exception e){
                        cout << "Exception e\n";
                    }
                }
            }
            else{
                fout << lc << "  ";
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
                while(st >> word){
                    if(operation == "DC"){
                        word = word.substr(1,word.length()-2);
                        fout << "(C, " << word << ") ";
                    }   
                    else if(operation == "DS"){ 
                        fout << "(C, " << word << ") ";
                        try{
                            lc += stoi(word) - 1;
                        }
                        catch(exception e){
                            cout << "another one\n";
                        }
                    }
                    else if(word[0] == '='){
                        littab.push_back({word,lc});
                        fout << "(L, " << littab.size() << ") ";
                    }
                    else if(opcode.count(word)>0){
                        fout << "(" << opcode[word].first << ") ";
                    }
                    else {
                        if(symtab.count(word) == 0){
                            symtab[word] = {lc,to_string(symtab.size()+1)};
                        }
                        fout << "(S, " << symtab[word].second << ") ";
                    }
                } 
                lc++;
            }
            fout << endl;
        }
    }
};

int main()
{
    pass1 obj;
    obj.execute();
}