#include "p1_process.h"
#include "p1_threads.h"
#include "p1_ans.h"
#include <algorithm>

using namespace std;

void get_statistics(string class_name[], int num_processes, int num_threads) {
  int num = num_threads / num_processes, mod = num_threads % num_processes;
  int size = 0, inc = 0, status = 0;
  pid_t pid, wpid;
  vector<string> file;
  
  for (int i = 0; i < num_processes; i++) {
    if (mod > 0)
      size = num+1;
    else
      size = num;
    
    if (mod > 0)
      mod -= 1;

    for (int q = 0; q < size; q++)
      file.push_back(class_name[inc++]);
    
    pid = fork();
    if (pid == 0)
      break;

    file.clear();
  }

  if (pid == 0) {
    printf("Child process is created. (pid: %d)\n", getpid());
    // for (int i = 0; i < file.size();i++)
    //   cout << file[i] << endl;
    
    for (int i = 0; i < file.size(); i++) {
      string input = "./input/" + file[i] + ".csv";
      struct Answer ans = read(input);
      pthread_t thread[3];

      pthread_create(&thread[0], NULL, findAvg, &ans);
      pthread_create(&thread[1], NULL, findMed, &ans);
      pthread_create(&thread[2], NULL, findStd, &ans);

      for (int q = 0; q < 3; q++) {
        if (pthread_join(thread[q], NULL))
          fprintf(stderr, "Error combining threads together\n");  
      }

      string output1 = "./output/" + file[i] + "_stats.csv";
      string output2 = "./output/" + file[i] + "_sorted.csv";
      fileOutAns(output1, ans);
      fileOut(output2, ans);
    }
    printf("Child process is terminated. (pid: %d)\n", getpid()); 
    exit(0);
  }

  while ( ( wpid = wait(&status) ) > 0 );
  printf("Parent process is terminated. (pid: %d)\n", getpid());
}

struct Answer read(string file) {
  struct Answer ans;
  string line;
  ifstream ifs;
  ifs.open(file.c_str());
  if(!ifs.is_open()) {
    fprintf(stderr, "[ERROR] Can't open file.\n");
    exit(-1);
  }
  getline(ifs, line);
  ans.code = line;

  while (getline(ifs, line)) {
    struct Student student;
    string name;
    float score;
    student.id = line.substr(0,10);
    name = line.substr(11);
    istringstream stream(name);
    stream >> score;
    student.grade = score;
    ans.students.push_back(student);
  }
  sort(ans.students.begin(), ans.students.end(), mySort);
  ifs.close();
  return ans;
}

void fileOut(string file, Answer ans) {
  ofstream ofs;
  ofs.open(file.c_str());

  if ( !ofs.is_open() ) {
    fprintf(stderr, "[ERROR] Can't create file.\n");
    exit(-1);
  }

  ofs << "Rank," + ans.code << endl;
  for (int i = 0; i < 1000000; i++)
    ofs << i + 1 << "," << ans.students[i].id << "," << ans.students[i].grade << endl;
  ofs.close();
}

void fileOutAns(string file, Answer ans) {
  ofstream ofs;
  ofs.open(file.c_str());
  if ( !ofs.is_open() ) {
    fprintf(stderr, "[ERROR] Can't create file.\n");
    exit(-1);
  }

  ofs << "Average,Median,Std. Dev" << endl;
  ofs << ans.avg << "," << ans.median << "," << ans.std_dev << endl;
  ofs.close();
}
