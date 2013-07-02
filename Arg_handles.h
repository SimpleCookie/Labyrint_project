#ifndef ARGH
#define ARGH

#include <getopt.h> // includes the getopt command for input flags

class option long_options[] = {
    {"version",     no_argument, 0,  'v' },
    {"help",  no_argument,       0,  'h' },
    {"size",  required_argument, 0,  's' },
    {"columns", required_argument,       0,  'c' },
    {"rows",  required_argument, 0, 'r'},
    {"input",    required_argument, 0,  'i' },
    {"output",    required_argument, 0,  'o' },
    {"check",    no_argument, 0,  'b' },
    {"path",    no_argument, 0,  'p' },
    {0,         0,                 0,  0 }
};


#endif 
/* Arg_handles.h */
