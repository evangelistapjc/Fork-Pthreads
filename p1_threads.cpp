#include "p1_threads.h"
#include "p1_process.h"

using namespace std;

bool mySort(const Student& student1, const Student& student2) {
  return student1.grade > student2.grade;
}

void* findAvg(void* x) {
  struct Answer* d = (struct Answer*) x;
  d->avg = average(d);
}

void* findMed(void* x) {
  struct Answer* d = (struct Answer*) x;
  median(d->median, d->students);
}

void* findStd(void* x) {
  struct Answer* d = (struct Answer*) x;
  d->std_dev = std_dev(d);
}

float average(struct Answer* d) {
  if (d->students.size() == 0) {
    return 0;
  } else {
    vector<Student>::iterator iterate;
    float total = 0;
    for (iterate = d->students.begin(); iterate != d->students.end(); iterate++)
      total += iterate->grade;
    total /= d->students.size();
    return total;
  }
}

void median(float& median, vector<Student> students) {
  int size = students.size();
  if (size%2 == 0)
    median = (students[size/2].grade + students[size/2 - 1].grade)/2;
  else
    median = students[size/2].grade;
}

float std_dev(struct Answer* d) {
  float avg = average(d);
  float temp = 0;
  for (int i = 0; i < d->students.size(); i++)
    temp += pow((d->students[i].grade - avg), 2);
  temp = sqrt(temp / d->students.size());
  return temp;
}
