//
// Created by danil on 22.11.2025.
//
//arguments of cos,sin,tg,ctg and exp should be written in breackets
//for example, "cos x" and "cosx" are invalid, only "cos(x)" is right
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cmath>

int main() {
    std::string line;
    std::cout<<"enter expression to calculate: ";
    std::getline(std::cin, line);
    std::vector<std::string> result;
    std::vector<std::string> numbers;
    std::unordered_map<std::string, int> priority = {{"+",1},{"-",1},{"*",2},{"/",2}, {"^",3},{"@",3},{"~",3},{"`",3},{"$",3},{"!",3}};
    std::unordered_map<std::string, std::string> complex_functions={{"cos","@"}, {"sin","~"}, {"tg","`"}, {"ctg","$"},{"exp","!"}};
    std::string c;
    std::string num="";
    if (line[0]=='-') line[0]='#';
    while (line.find("(-")!=std::string::npos) {
        line.replace(line.find("(-"),2,"(#");
    }
    int chet=0;
    for (auto it = complex_functions.begin(); it != complex_functions.end(); it++) {
        while (line.find(it->first)!=std::string::npos) {
            auto pos = line.find(it->first);
            line.replace(pos,it->first.length(),"");
            for (int i=pos; i<line.size(); i++) {
                if (line[i]=='(') chet++;
                if (line[i]==')') {
                    chet--;
                }
                if (chet==0) {
                    line.insert(i+1,it->second);
                    break;
                }
            }
        }
    }
    std::string temp=line;
    std::replace(temp.begin(), temp.end(), '+', ' ');
    std::replace(temp.begin(), temp.end(), '-', ' ');
    std::replace(temp.begin(), temp.end(), '*', ' ');
    std::replace(temp.begin(), temp.end(), '/', ' ');
    std::replace(temp.begin(), temp.end(), '(', ' ');
    std::replace(temp.begin(), temp.end(), ')', ' ');
    std::replace(temp.begin(), temp.end(), '^', ' ');
    std::replace(temp.begin(), temp.end(), '@', ' ');
    std::replace(temp.begin(), temp.end(), '`', ' ');
    std::replace(temp.begin(), temp.end(), '~', ' ');
    std::replace(temp.begin(), temp.end(), '!', ' ');
    std::replace(temp.begin(), temp.end(), '$', ' ');
    temp.erase(temp.find_last_not_of(" \n\r\t") + 1);
    std::stringstream ss(temp);
    std::string number;
    while (!ss.eof()) {
        ss >> number;
        std::replace(number.begin(), number.end(), '#', '-');
        numbers.push_back(number);
    }

    std::stack<std::string> memory;
    int j=0;
    for (int i = 0; i < line.size(); i++) {
        c = line[i];
        if (c == "+" || c == "-" || c == "*" || c == "/" || c== "^" || c=="@" || c=="`" || c=="~" || c=="!" || c=="$") {
            if (memory.empty() || memory.top() == "(") {
                memory.push(c);
            }
            else {
                if (priority[c] <= priority[memory.top()]) {
                    while (memory.top()!="(" && !memory.empty() && priority[c] <= priority[memory.top()]) {
                        if (memory.top()=="+" || memory.top()=="-" || memory.top()=="*" || memory.top()=="/" || memory.top()=="^") {
                            result.push_back(memory.top());
                        }
                        else {
                            for (auto it = complex_functions.begin(); it != complex_functions.end(); it++) {
                                if (memory.top()==it->second) result.push_back(it->first);
                            }
                        }
                        memory.pop();
                    }
                    memory.push(c);
                }
                else {
                    memory.push(c);
                }
            }
        }
        else if (c=="(") memory.push(c);
        else if (c==")") {
            while (memory.top()!="(") {
                if (memory.top()=="+" || memory.top()=="-" || memory.top()=="*" || memory.top()=="/" || memory.top()=="^") {
                    result.push_back(memory.top());
                }
                else {
                    for (auto it = complex_functions.begin(); it != complex_functions.end(); it++) {
                        if (memory.top()==it->second) result.push_back(it->first);
                    }
                }
                memory.pop();
            }
        }
        else {
            result.push_back(numbers[j]);
            i+=numbers[j].length()-1;
            j++;
        }
    }
    while (!memory.empty()) {
        if (memory.top()=="+" || memory.top()=="-" || memory.top()=="*" || memory.top()=="/" || memory.top()=="^") {
            result.push_back(memory.top());
        }
        else {
            for (auto it = complex_functions.begin(); it != complex_functions.end(); it++) {
                if (memory.top()==it->second) result.push_back(it->first);
            }
        }
        memory.pop();
    }
    //for (auto pos:result) std::cout<<pos<<" ";std::cout<<std::endl;
    if (std::find(numbers.begin(), numbers.end(), "x") != numbers.end()) {
        std::string x;
        std::cout<<"enter value of x: "; std::cin>>x;
        std::replace(result.begin(), result.end(),std::string("x"),x);
        //for (auto pos:result) std::cout<<pos<<" ";std::cout<<std::endl;
    }
    std::string save;
    double numb;
    std::pair<std::string, std::string> pair;
    for (auto it = result.begin(); it != result.end(); it++) {
        try {
            numb=std::stod(*it);
            if (pair.first == "") pair.first = *it;
            else if (pair.second == "") pair.second = *it;
            else {pair.first = pair.second; pair.second = *it;}
        }
        catch (...) {
            if (*it=="+"|| *it=="-" || *it=="*" || *it=="/" || *it=="^") {
                save=*it;
                result.erase(it);
                result.erase(--it);
                --it;
                if (save=="+") *it = std::to_string(std::stod(pair.first)+std::stod(pair.second));
                if (save=="-") *it = std::to_string(std::stod(pair.first)-std::stod(pair.second));
                if (save=="*") *it = std::to_string(std::stod(pair.first)*std::stod(pair.second));
                if (save=="/") *it = std::to_string(std::stod(pair.first)/std::stod(pair.second));
                if (save=="^") *it = std::to_string(pow(std::stod(pair.first),std::stod(pair.second)));
                pair.first = ""; pair.second = "";
                it=result.begin();
                --it;
            }
            else {
                save=(*it);
                if (pair.second!="") numb=std::stod(pair.second);
                else numb=std::stod(pair.first);
                result.erase(it); --it;
                if (save=="cos") *it = std::to_string(cos(numb));
                if (save=="sin") *it = std::to_string(sin(numb));
                if (save=="tg") *it = std::to_string(tan(numb));
                if (save=="ctg") *it = std::to_string(1.0/tan(numb));
                if (save=="exp") *it = std::to_string(exp(numb));
                pair.first = ""; pair.second = "";
                it=result.begin();
                --it;
            }
        }
        if (result.size()<=3) break;
    }
    std::cout<<"result: ";
    if (result.size()==3) {
        if (result[2]=="+") std::cout<<std::stod(result[0])+std::stod(result[1])<<std::endl;
        else if (result[2]=="-") std::cout<<std::stod(result[0])-std::stod(result[1])<<std::endl;
        else if (result[2]=="*") std::cout<<std::stod(result[0])*std::stod(result[1])<<std::endl;
        else if (result[2]=="/") std::cout<<std::stod(result[0])/std::stod(result[1])<<std::endl;
        else if (result[2]=="^") std::cout<<pow(std::stod(result[0]),std::stod(result[1]))<<std::endl;
    }
    if (result.size()==2) {
        if (result[1]=="cos") std::cout<<cos(std::stod(result[0]))<<std::endl;
        else if (result[1]=="sin") std::cout<<sin(std::stod(result[0]))<<std::endl;
        else if (result[1]=="tg") std::cout<<tan(std::stod(result[0]))<<std::endl;
        else if (result[1]=="ctg") std::cout<<1/tan(std::stod(result[0]))<<std::endl;
        else if (result[1]=="exp") std::cout<<exp(std::stod(result[0]))<<std::endl;
    }
}