#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

#include <fstream>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <iomanip>
#include <algorithm>

#include "p1_threads.h"

using namespace std;

void get_statistics(string class_name[], int num_processes, int num_threads);
struct Answer read(string filename);
void fileOut(string filename, struct Answer data);
void fileOutAns(string filename, struct Answer data);

#endif
