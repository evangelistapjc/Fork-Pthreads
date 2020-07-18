#ifndef __P1_THREADS
#define __P1_THREADS

#include "p1_ans.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <math.h>
#include <pthread.h>
#include "p1_process.h"

bool mySort(const Student& student1, const Student& student2);

void* findAvg(void* input);
void* findMed(void* input);
void* findStd(void* input);

float average(struct Answer* data);
void median(float& median, std::vector<Student> students);
float std_dev(struct Answer* data);

#endif
