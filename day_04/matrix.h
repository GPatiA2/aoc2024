#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>
#include <array>


enum Direction {
  UL, UP, UR , LE, CE, RI , DL, DO, DR
};

struct Coords {
  int x;
  int y;

  
  Coords() {}
  Coords(int cx, int cy) {
    x = cx;
    y = cy;
  }

  friend std::ostream &operator<<(std::ostream &out, const Coords & c) {
    out << "{" << c.x << " , " << c.y << "}";
    return out;
  }

  friend Coords operator-(const Coords &c1, const Coords &c2) {
    int d1 = c1.x - c2.x;
    int d2 = c1.y - c2.y;
    return {d1, d2};
  }

  friend Coords operator+(const Coords &c1, const Direction d){
    Coords c2 = fromDirection(d);
    return Coords(c1.x + c2.x, c1.y + c2.y);
  }

  friend Coords operator+(const Coords &c1, const Coords &c2){
    return Coords(c1.x + c2.x, c1.y + c2.y);
  }

  static Direction fromDifference(const Coords &c1, const Coords &c2) {
    Coords diff = c1 - c2;
    std::array<std::array<Direction, 3>,3> dir = { UL, UP, UR , LE, CE, RI , DL, DO, DR  }; 
    return dir[diff.x+1][diff.y+1];
  }

  static Coords fromDirection(const Direction d) {
    std::array<Coords,9> ind = { Coords(-1, -1), Coords(-1, 0), Coords(-1, 1), Coords(0, -1), Coords(0, 0), Coords(0, 1), Coords(1, -1), Coords(1, 0), Coords(1, 1) }; 
    return ind[d];
  }

}; 


template <class T> class Matrix {

private:
  T **matrix;
  int rows;
  int cols;
  T init;

public:

  Matrix() {
  }

  Matrix(int r, int c, T init) {
    rows = r;
    cols = c;
    matrix = new T *[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = new T[cols];
      for (int j = 0; j < cols; j++) {
        matrix[i][j] = init;
      }
    }
    this->init = init;
  }

  int get_rows() const { return rows; }
  int get_cols() const { return cols; }

  T *operator[](int row) { return matrix[row]; }

  T *const &operator[](int row) const { return matrix[row]; }

  T &operator[](Coords c) { return matrix[c.x][c.y]; }

  T const &operator[](Coords c) const { return matrix[c.x][c.y]; }

  bool in_bounds(int x, int y) const {
    bool x_ok = x >= 0 && x < rows;
    bool y_ok = y >= 0 && y < cols;
    return x_ok && y_ok;
  }

  void clear() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        matrix[i][j] = 0;
      }
    }
  }
  bool in_bounds(const Coords &c) const { return in_bounds(c.x, c.y); }

  long int to_arr_pos(int x, int y) const { return x * cols + y; }

  long int to_arr_pos(const Coords &c) const { return to_arr_pos(c.x, c.y); }

  Coords from_arr_pos(long int i) const {
    Coords c;
    c.x = i / rows;
    c.y = i % cols;
    return c;
  }

  std::vector<Coords> validNeighbours(const Coords & c, std::function<bool(char)> filter)const {
    std::vector<Coords> ret;
    for(int d = Direction::UL; d <= Direction::DR; d++){
      if(d == Direction::CE) continue;
      Coords n = c + Coords::fromDirection(static_cast<Direction>(d));
      if (in_bounds(n) && filter(matrix[n.x][n.y])){
        ret.push_back(n);
      }
    }
    return ret;
  }

  std::vector<Coords> search(std::function<bool(T)> filter) const {

    bool isf = filter(matrix[0][1]);
    std::vector<Coords> ret;
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
          bool isf = filter(matrix[i][j]);
          if (isf){
            ret.push_back(Coords(i, j));
          } 
      }
    }
    return ret;
  }

  ~Matrix() {
    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

};
 

template <class T>
inline std::ostream &operator<<(std::ostream &out, const Matrix<T> &mat) {
  for (int i = 0; i < mat.get_rows(); i++) {
    for (int j = 0; j < mat.get_cols(); j++) {
      out << mat[i][j] << " ";
    }
    out << '\n';
  }
  return out;
}

std::string dirToString(Direction d){
  std::array<std::string,9> dir = {"UP", "UR", "RI", "DR", "DO", "DL", "LE", "UL", "CE"};
  return dir[d];
}

#endif
