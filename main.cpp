//
//  main.cpp
//  MicroProject
//
//  Created by Mariam Elsaqa on 5/19/21.
//  Copyright © 2021 None. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class transistor {
public:
    string drain;
    string gate;
    string src;
    string body;
    string type;

    transistor();
    transistor(char d, string g, string s, string b, int t);
    vector<transistor> PUN(vector<string> in, vector<char> LogicGate, int w, char output);
    vector<transistor> PDN(vector<string> in, vector<char> LogicGate, int w, char output);

};

transistor::transistor()
{
}

transistor::transistor(char d, string g, string s, string b, int t) {
    gate = g;
    drain = d;
    src = s;
    body = b;
    type = t;
}

vector<transistor>transistor::PUN(vector<string> in, vector<char> LogicGate, int w, char output) {
    vector<transistor>outPUN;
    int s = 0, e = 0;

    for (int i = 0; i < LogicGate.size(); i++)
    {
       
        if (LogicGate[i] == '&') {
            e++;
        }
        
        else {
            
            for (int j = s; j <= e; j++) {
                gate = in[j];
                type = "PMOS";
                if (j == s) {
                    src = "Vdd";
                    body = "Vdd";
                }
                else {
                    src = to_string(w);
                    body = to_string(w);
                }
                if (i == e) {
                    drain = output;
                  
                }
                else {
                    w++;
                    drain =to_string( w);
                    
                }

                outPUN.push_back(*this);
            }
            e++;
            s = e;
            
        }
        
    }
    for (int k = s; k <= e; k++) {
        gate = in[k];
        type = "PMOS";
        if (k == s) {
            src = "Vdd";
            body = "Vdd";
        }
        else {
            src = to_string(w);
            body = to_string(w);
        }
        if (k == e) {
            drain = output;
        }
        else {
            w++;
            drain = to_string(w);
        }
        outPUN.push_back(*this);
    }

    return outPUN;
}

vector<transistor>transistor::PDN(vector<string> in, vector<char> LogicGate, int w, char output) {
    vector<transistor>outPDN;
    int s = 0, e = 0, srcW = 0, Dw = w+1;
  
    for (int i = 0; i < LogicGate.size(); i++) {
        if (LogicGate[i] == '&') {
            e++;
        }
        else {
            for (int j = s; j <= e; j++) {
                type = "NMOS";
                drain =to_string(Dw);
                gate = in[j];
                src = to_string(srcW);
                body = to_string(srcW);
            

                outPDN.push_back(*this);
            }
            w++;
            srcW = Dw;
            Dw++;
            e++;
            s = e;
        }
    }
    drain = output;
    for (int k = s; k <= e; k++) {
        type = "NMOS";
        gate = in[k];
        src = to_string(srcW);
        body = to_string(srcW);

        outPDN.push_back(*this);
    }

    return outPDN;
}

void print(vector<transistor> pu, vector <transistor> pd, int index)
{
    for (int i = 0; i < pu.size(); i++)
    {
        cout << "M" << i + 1 + index << " " << pu[i].drain << " " << pu[i].gate << " " << pu[i].src << " " << pu[i].src << " " << pu[i].type << endl;
    }
    for (int j = 0; j < pd.size(); j++)
    {
        cout << "M" << pu.size() + j+1 + index<< " " << pd[j].drain << " " << pd[j].gate << " " << pd[j].src << " " << pd[j].src << " " << pd[j].type << endl;
    }
}

int main()
{
    cout << "Enter boolean equation:";
    string line;
    cin >> line;
    int lwire = 0;
    int no_of_transisters = 0;
    char output = line[0];
    vector<string>inputs;
    vector<char>operators;
    for (int i = 2; i < line.size(); i = i + 2)
    {
        string t;
        t.push_back(line[i]);
        if (t[0] == output)
        {
            cout << "Error, output cannot be part of expression";
            exit(1);
        }
        if (i == line.size() - 1 || line[i + 1] != '\'')
        {
            t.push_back('\'');
        }
        else
            ++i;
        inputs.push_back(t);

        if (i != line.size() - 1)
        operators.push_back(line[i + 1]);


    }
    for (int i = 0; i < operators.size(); i++)
    {

        if (operators[i] != '|' && operators[i] != '&' && operators[i] != '\'')
        {
            cout << "Error, Operators entered are invalid";
            exit(1);
        }
    }
    transistor t;
    vector<transistor> pu = t.PUN(inputs, operators, lwire, output);
    vector<transistor> pd = t.PDN(inputs, operators, lwire, output);
    for (int i = 0; i < inputs.size(); i++)
    {
        if (inputs[i].size() > 1)
        {
            no_of_transisters++;
            cout << "M" << no_of_transisters << " " << inputs[i] << " " << inputs[i][0] << " vdd vdd PMOS" << endl;
            no_of_transisters++;
            cout << "M" << no_of_transisters << " " << inputs[i] << " " << inputs[i][0] << " 0 0 NMOS" << endl;
        }
    }
    print(pu, pd,no_of_transisters);

    return 0;
}
