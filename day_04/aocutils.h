
#ifndef AOCUTILS_H
#define AOCUTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline std::vector<std::string> split_line(std::string s, std::string sep) {
  std::vector<std::string> ret;
  int pos = 0;
  std::string tok;
  while ((pos = s.find(sep)) != std::string::npos) {
    tok = s.substr(0, pos);
    ret.push_back(tok);
    s.erase(0, pos + sep.length());
  }
  ret.push_back(s);
  return ret;
}

template <class T> inline std::vector<T> subvect(std::vector<T> v, int start, int end) {
  std::vector<T> ret;
  for (int i = start; i < end; i++) {
    ret.push_back(v[i]);
  }
  return ret;
}

inline std::string substr(std::string s, int start, int end) {
  std::string ret = "";
  for (int i = start; i < end; i++) {
    ret += s[i];
  }
  return ret;
}

template <class T> inline std::ostream &operator<<(std::ostream &os, std::vector<T> vec) {
  for (T it : vec) {
    os << it << " ";
  }
  return os;
}

template <class T>
std::vector<T> filter_vector(const std::vector<T> &v, bool (*filter)(T)) {
  std::vector<T> ret;
  for (T elem : v) {
    if (filter(elem)) {
      ret.push_back(elem);
    }
  }
  return ret;
}

template <class T>
 std::vector<T> filter_vector(const std::vector<T> &v, bool (*filter)(T, T), const T &ef) {
  std::vector<T> v_ret;
  for (T elem : v) {
    if (filter(elem, ef)) {
      v_ret.push_back(elem);
    }
  }
  return v_ret;
}

inline long int variations(int elems, int groups) {
  long int prod = 1;
  for (int i = elems; i >= groups; i--) {
    prod *= i;
  }

  return prod;
}

inline long int count_in_substr(const std::string &str, long int start, long int end,
                                char c) {
  long int count = 0;
  for (int i = start; i < end; i++) {
    if (str[i] == c) {
      count += 1;
    }
  }
  return count;
}

#endif
