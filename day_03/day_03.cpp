#include "aocutils.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int resultmult(string match_str) {
  string only_digits = match_str.substr(4, match_str.size() - 1);
  // Remove )
  only_digits = only_digits.substr(0, only_digits.size() - 1);
  vector<string> numbers = split_line(only_digits, ",");
  int n1 = stoi(numbers[0]);
  int n2 = stoi(numbers[1]);
  cout << only_digits << "=" << n1 * n2 << endl;
  return n1 * n2;
}

int solve1(string line) {
  regex mul("mul\\([0-9]+,[0-9]+\\)");
  auto beg = sregex_iterator(line.begin(), line.end(), mul);
  auto end = sregex_iterator();
  long long int sum = 0;
  bool enabled = true;
  for (sregex_iterator i = beg; i != end; ++i) {
    smatch match = *i;
    string match_str = match.str();
    sum += resultmult(match_str);
  }
  return sum;
}

int solve2(string line) {

  regex mul("mul\\([0-9]+,[0-9]+\\)");
  regex dorgx("do\\(\\)");
  regex dontrgx("don\\'t\\(\\)");
  auto mulbeg = sregex_iterator(line.begin(), line.end(), mul);
  auto mulend = sregex_iterator();
  auto dobeg = sregex_iterator(line.begin(), line.end(), dorgx);
  auto doend = sregex_iterator();
  auto dontbeg = sregex_iterator(line.begin(), line.end(), dontrgx);
  auto dontend = sregex_iterator();
  long long int sum = 0;
  bool enabled = true;
  while (mulbeg != mulend) {
    smatch mulmatch = *mulbeg;
    smatch domatch = *dobeg;
    smatch dontmatch = *dontbeg;
    cout << "Enabled = " << enabled << endl;
    cout << "Mulmatch = " << mulmatch.position() << endl;
    cout << "Domatch = " << domatch.position() << endl;
    cout << "Dontmatch = " << dontmatch.position() << endl;
    cout << "===" << endl;

    if (mulmatch.position() > domatch.position() && dobeg != doend) {
      enabled = true;
      dobeg++;
    }
    if (mulmatch.position() > dontmatch.position() && dontbeg != dontend) {
      enabled = false;
      dontbeg++;
    }
    if (enabled) {
      string match_str = mulmatch.str();
      cout << "Multiplying = " << match_str << endl;
      sum += resultmult(match_str);
      cout << "Sum = " << sum << endl;
    }

    mulbeg++;
  }
  return sum;
}

int main(int argc, char *argv[]) {
  string file = argv[1];
  ifstream f;
  string line;
  f.open(file);
  getline(f, line);
  // int sum1 = solve1(line);
  // cout << sum1 << endl;

  int sum2 = solve2(line);
  cout << sum2 << endl;
  return 0;
}
