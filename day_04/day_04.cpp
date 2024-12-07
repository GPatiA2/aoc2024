#include "matrix.h"
#include "aocutils.h"
#include <iostream>
#include <fstream>
#include <stack>

// Lambda functions with captured arguments work like this:
// auto l = [next](char c) { return c == next;};
// std::vector<Coords> neighbours = m.validNeighbours(p.first, l);

struct dfs_state {
    Coords c;
    int index;
    Direction d;

    friend std::ostream &operator<<(std::ostream &os, const dfs_state &s){
        os << "State: " << s.c << " " << s.index << " " << s.d;
        return os;
    } 
};

int findMatches(const Matrix<char> & m, const Coords & c, int index, std::string pattern){
    int count = 0; 
    std::stack<dfs_state> s;

    // Vector of valid neighbours of pos c that match the next character in the pattern
    char next = pattern[index]; 
    auto l = [next](char c) { return c == next;};
    std::vector<Coords> neighbours = m.validNeighbours(c, l);
    for (size_t i = 0; i < count; i++)
    {
        std::cout << neighbours[i] << " " <<  m[neighbours[i]] << std::endl;
    }
    

    // Initialize the stack with the valid neighbours
    for (Coords n : neighbours){
        s.push({n, index + 1, Coords::fromDifference(n,c)});
    }

    while(!s.empty()){
        dfs_state p = s.top();
        s.pop();
        if (p.index >= pattern.size()){
            count++;
        }
        else{
            // Only push to the stack if the next character matches
            if (m.in_bounds(p.c+p.d) && m[(p.c + p.d)] == pattern[p.index]){
                // Push next position in the original direction
                s.push({p.c + p.d, p.index + 1, p.d});
            }
        }
    }
    return count;
}

int solve_case1(const Matrix<char> & m){
    std::cout << "Solving case 1 " << std::endl;
    int xmascount = 0;
    char first = 'X';
    auto l = [first](char c) { return c == first; }; 

    std::vector<Coords> roots = m.search(l);

    for(Coords r : roots){
        int matches_found = findMatches(m, r, 1, "XMAS");
        xmascount += matches_found;
    } 

    return xmascount;
}

bool isCross(const Matrix<char> & m, const Coords & c){
    std::array<std::array<Direction,2>,2> dirs = {Direction::UL, Direction::DR, Direction::UR, Direction::DL};
    bool inbounds = true;
    for (int i = 0; i < 2; i++){
        Coords n1 = c + Coords::fromDirection(dirs[i][0]);
        Coords m1 = c + Coords::fromDirection(dirs[i][1]);
        inbounds = inbounds && m.in_bounds(n1) && m.in_bounds(m1);
    }
    if (!inbounds) return false;
    // Check if UL DR are equal to M S or S M
    bool maindig = (m[c+dirs[0][0]] == 'M' && m[c+dirs[0][1]] == 'S') || (m[c+dirs[0][0]] == 'S' && m[c+dirs[0][1]] == 'M');
    // Check if UR DL are equal to S M or M S
    bool secdig = (m[c+dirs[1][0]] == 'M' && m[c+dirs[1][1]] == 'S') || (m[c+dirs[1][0]] == 'S' && m[c+dirs[1][1]] == 'M');
    return maindig && secdig;
}

int solve_case2(const Matrix<char> & m){
    std::cout << "Solving case 2 " << std::endl;
    int crossmascount = 0;
    char first = 'A';
    auto l = [first](char c) { return c == first; }; 

    std::vector<Coords> roots = m.search(l);

    for(Coords r : roots){
        int matches_found = isCross(m, r); 
        crossmascount += matches_found;
    } 

    return crossmascount;
}

int main(int argc, char * argv[]){

    std::string filename = argv[1];
    std::string line;
    std::ifstream f;
    f.open(filename);
    std::vector<std::string> lines;
    while (std::getline(f, line)){
        lines.push_back(line);
    }
    f.close();

    int rows = lines.size();
    int cols = lines[0].size();

    Matrix<char> m(rows, cols, ' ');
    for (int i = 0; i < lines.size(); i++){
        for (int j = 0; j < lines[i].size(); j++){
            m[{i, j}] = lines[i][j];
        }
    }

    int xmascount = solve_case1(m);
    std::cout << "Case 1 " << xmascount << std::endl;

    int crossmascount = solve_case2(m);
    std::cout << "Case 2 " << crossmascount << std::endl;

    return 0;
}