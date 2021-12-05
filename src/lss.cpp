// AGPLv3 cafkafk © 2021

#include "lss.h"

/* C++ libs */

// OS
#include <cstdlib>

// I/O
#include <iostream>
#include <iomanip>

// Sort
#include <algorithm>

// Set
#include <set>
#include <iterator>

/* C libs */

// Files in dir
#include <dirent.h>

// Arguments
#include <getopt.h>

// Winsize
#include <sys/ioctl.h>
#include <unistd.h>

/* END HEADER */

using namespace std;

/* File scope flags, all default to 0 */

static int f_long;
static string list_separator = "\t";

/* Working dir/file argument */
static string path = ".";

static int longest_file_name = 0;

/* Window size */
static struct winsize w;

set<string> scan_dir() {
    set<string> files;
    DIR *d;
    struct dirent *dir;
    d = opendir(path.c_str());
    int len;
    if(d) {
        while((dir = readdir(d)) != NULL) {
            files.insert(dir->d_name);
            len = ((string)dir->d_name).size();
            if(len > longest_file_name){
                longest_file_name = len;
            }
        }
       closedir(d);
    }
    return files;
}

void print_set(set<string> files) {
    set<string>::iterator itr = files.begin();
    //int past = 0;
    int max = w.ws_col / (longest_file_name + list_separator.length());
    max = w.ws_col / (longest_file_name + list_separator.length() + (max*4));
    int i = 0;
    for (itr = files.begin(); itr != files.end(); itr++) {
        //int len = ((string)*itr).length() + list_separator.length();
        //int len = ((string)*itr).length() + list_separator.length() + 32;
        //cout << len << " " << past << " " << w.ws_col  << " " << longest_file_name<< endl;
        if(i < max) {
            printf("%-32s%s", ((string)*itr).c_str(), list_separator.c_str());
            i++;
        }
        else{
            cout << endl;
            printf("%-32s%s", ((string)*itr).c_str(), list_separator.c_str());
            i=1;
        }
    }
}

int main(int argc, char *argv[]) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int c;

  while (1)
  {
    int option_index = 0;
    static struct option long_options[] =
    {
      {"long",    no_argument, &f_long,     1},
      {NULL,      0,           NULL,       0}
    };

    c = getopt_long(argc, argv, "-:lh", long_options, &option_index);
    if (c == -1)
      break;

    switch (c)
    {
      case 1:
        path = optarg;
        break;

      case 'l':
          f_long=1;
          list_separator = "\n";
          break;

      case 'h':
          cout << "HELP" << endl;
          break;

      case '?':
        printf("Unknown option %c\n", optopt);
        break;
    }
  }

  set<string> files = scan_dir();

  print_set(files);

  return EXIT_SUCCESS;
}
