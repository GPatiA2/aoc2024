#include "aocutils.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct input_case
{
  long long int target;
  std::vector<long long int> numbers;
  long long int act;
  std::vector<char> placed;

  input_case(){}

  input_case(const input_case & c2){
    target = c2.target;
    numbers= std::vector<long long int>(c2.numbers);
    act = c2.act;
    placed = std::vector<char>(c2.placed);
  }

  input_case(long long int t, const std::vector<long long int> & n, long long int a, const std::vector<char> & p){
    target = t;
    numbers = std::vector<long long int>(n);
    act = a;
    placed = std::vector<char>(p);
  }

  friend std::ostream& operator<<(std::ostream& out, const input_case & ic){
    out << std::to_string(ic.target) << ": ";
    for(int i = 0; i < ic.numbers.size(); i++){
      out << std::to_string(ic.numbers[i]) << " ";
    }
    return out;
  }

  std::string show() const{
    std::string r;
    r += std::to_string(target) + ": 0 ";
    for(int i = 0; i < placed.size(); i++){
      r += std::string(1, placed[i]) + " " + std::to_string(numbers[i+1]) + " ";
    } 
    return r;
  }
};

std::pair<input_case, bool> ispossible(const input_case & c, const std::vector<char> & symbols, int position){


  if(position > c.numbers.size() - 2){
    if(c.target == c.act){
      std::cout << c.show() << std::endl;
    }
    return {input_case(c), c.target == c.act};
  }

  // Recursive case
  input_case sol(c);
  bool p = false;

  for(int i = 0; i < symbols.size(); i++){
    char s = symbols[i];
    if(s == '+' && !p){
      sol.act += c.numbers[position+1];
      sol.placed.push_back('+');

      auto s = ispossible(sol, symbols, position+1);

      p |= s.second;

      sol.act -= c.numbers[position+1];
      sol.placed.pop_back(); 
    }
    else if(s == '*' && position != 0 & !p){
      sol.act *= c.numbers[position+1];
      sol.placed.push_back('*');

      auto s = ispossible(sol, symbols, position+1);

      p |= s.second;

      sol.act /= c.numbers[position+1];
      sol.placed.pop_back();
    }
    else if(s == '|' && position != 0 && !p){
      sol.act *= (10 * std::to_string(c.numbers[position+1]).size());
      sol.act += c.numbers[position+1];
      sol.placed.push_back('|');

      auto s = ispossible(sol, symbols, position+1);

      p |= s.second;

      sol.act -= c.numbers[position+1];
      sol.act /= (10 * std::to_string(c.numbers[position+1]).size());
      sol.placed.pop_back();
    }
  } 
  return {sol, p};
}


bool possible(const input_case & c, const std::vector<char> & symbols){
  auto sol = ispossible(c, symbols, 0);
  // if (sol.second) std::cout << "Found valid with " << sol.first.show() << std::endl;
  return sol.second;
}

long int case1(const std::vector<input_case> & ic){
  long int result = 0;
  int valid = 0;
  std::vector<char> symbols = {'+', '*'};
  for(input_case c : ic){
    bool pos = possible(c, symbols);
    // if(pos) std::cout << "Case " << c << " valid" << std::endl;
    if(pos) valid++;
    if(pos) result+= c.target;
  }
  // std::cout << "Valid : " << valid << " out of " << ic.size() << std::endl;
  return result;
}

long long int case2(const std::vector<input_case> & ic){
  long long int result = 0;
  int valid = 0;
  std::vector<char> symbols = {'+', '*', '|'};
  for(input_case c : ic){
    bool pos = possible(c, symbols);
    // if(pos) std::cout << "Case " << c << " valid" << std::endl;
    if(pos) valid++;
    if(pos) result+= c.target;
  }
  // std::cout << "Valid : " << valid << " out of " << ic.size() << std::endl;
  return result;
}


int main(int argc, char * argv[])
{
  std::string filename = argv[1];
  std::ifstream file;

  file.open(filename);
  std::string line;
  std::vector<std::string> file_lines;
  while (getline(file, line)) {
    file_lines.push_back(line);
  }

  std::vector<input_case> cases;
  for(std::string s : file_lines){
    std::vector<std::string> strcase = split_line(s, ":");
    std::vector<std::string> strnumbers = split_line(strcase[1], " ");

    std::transform(strnumbers.begin(), strnumbers.end(), strnumbers.begin(), [](std::string s1){return strip(s1);});

    input_case ic;
    long long int t = std::stoll(strip(strcase[0]));
    ic.target = t;
    std::vector<long long int> num;
    num.push_back(0);
    for(int i = 0; i < strnumbers.size(); i++){ 
      long long int n2 = std::stoll(strnumbers[i]);
      num.push_back(n2); 
    }
    ic.numbers = num;
    ic.act = 0;
    std::cout << ic << std::endl;

    cases.push_back(ic);
  } 

  std::cout << "===" << std::endl;

  // long int res = case1(cases);
  // std::cout << "Case 1: " << res << std::endl;

  long long int res2 = case2(cases);
  std::cout << "Case 2: " << res2 << std::endl;


}
