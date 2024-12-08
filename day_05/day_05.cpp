#include "aocutils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>


template <typename T> inline std::ostream & operator<<(std::ostream &os, const std::pair<T, T> &p){
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}


struct sorter{

    std::unordered_map<int, std::set<int>> bm;

    sorter(const std::unordered_map<int, std::set<int>> & bm){
        this->bm = bm;
    }

    bool reachable(int a, int b){
        return bm[a].count(b) > 0;
    }

    bool operator()(int a, int b){
        return reachable(a,b);
    }
};

int solveCase1(const std::vector<std::pair<int, int>> & rules, const std::vector<std::vector<int>> & printings){
    int count = 0;
    int sorted = 0;

    // Printing rules are a total order
    std::unordered_map<int, std::set<int>> bm;
    for(std::pair<int, int> p : rules){
        if(bm.find(p.first) == bm.end()){
            bm[p.first] = std::set<int>();
        }
        bm[p.first].insert(p.second);

        if(bm.find(p.second) == bm.end()){
            bm[p.second] = std::set<int>();
        }
    }

    sorter s(bm);

    for(std::vector<int> p : printings){
        if(std::is_sorted(p.begin(), p.end(), s)){
            count+= p[p.size() / 2];
            sorted++;
        }
        else{
        }
    }
    std::cout << "Sorted: " << sorted << " out of " << printings.size() << std::endl;

    return count;
}


int solveCase2(const std::vector<std::pair<int, int>> & rules, const std::vector<std::vector<int>> & printings){
    int count = 0;

    std::unordered_map<int, std::set<int>> bm;
    for(std::pair<int, int> p : rules){
        if(bm.find(p.first) == bm.end()){
            bm[p.first] = std::set<int>();
        }
        bm[p.first].insert(p.second);

        if(bm.find(p.second) == bm.end()){
            bm[p.second] = std::set<int>();
        }
    }

    sorter s(bm);

    for(std::vector<int> p : printings){
        if(!std::is_sorted(p.begin(), p.end(), s)){
            std::sort(p.begin(), p.end(), s); 
            count+= p[p.size() / 2];
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    std::string line; 
    std::vector<std::string> lines; 
    while (std::getline(file, line)) {
        lines.push_back(line);
    }


    std::vector<std::string> l1;
    int i = 0;
    std::string aux = lines[i];
    while(aux != "==="){
        l1.push_back(aux);
        i++;
        aux = lines[i];
    }

    std::vector<std::string> l2;
    i++;
    while(i < lines.size()){
        aux = lines[i];
        l2.push_back(aux);
        i++;
    }

    std::vector<std::pair<int, int>> rules;
    for(std::string s : l1){
        std::vector<std::string> aux = split_line(s, "|");
        rules.push_back(std::make_pair(std::stoi(aux[0]), std::stoi(aux[1])));
    }

    std::vector<std::vector<int>> printings;
    for(std::string s : l2){
        std::vector<std::string> aux = split_line(s, ",");
        std::vector<int> aux2;
        for(std::string s2 : aux){
            aux2.push_back(std::stoi(s2));
        }
        printings.push_back(aux2);
    }

    // Trick: printing rules are a total ordering of pages
    // Checking if a sequence fulfills the rules is checking if it is sorted

    int c1 = solveCase1(rules, printings);
    std::cout << "Case 1: " << c1 << std::endl;

    int c2 = solveCase2(rules, printings);
    std::cout << "Case 2: " << c2 << std::endl;

    return 0;
}