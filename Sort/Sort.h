//
// Created by fidel on 3/11/18.
//

#ifndef VECTORSORT_SORT_H
#define VECTORSORT_SORT_H
#include <iostream>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec){
  for(T item : vec){
    out << item << " ";
  }
  return out;
}

template <typename T>
void swap(std::vector<T> &vec, typename std::vector<T>::iterator &pos1, typename std::vector<T>::iterator &pos2){
  T temp = *pos1;
  *pos1 = *pos2;
  *pos2 = temp;
}

template <typename T>
void sort(std::vector<T> &vec){
  for(auto i = vec.begin(); i != vec.end(); i++){
    for(auto j = i; j != vec.end(); j++){
      if(*i > *j) swap(vec, i, j);
    }
  }
}

#endif //VECTORSORT_SORT_H
