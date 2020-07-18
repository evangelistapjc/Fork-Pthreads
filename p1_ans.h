#ifndef P1_ANS_H
#define P1_ANS_H

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct Student {
  string id;
  float grade;
};

struct Answer {
  vector<Student> students;
  string code;
  float avg;
  float median;
  float std_dev;
};

#endif
