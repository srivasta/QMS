

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <csignal>
#include <cstring>

#include <fstream>
#include <iostream>
#include <strstream>
#include <sstream>

#include <ctype.h>

#include <string>
using std::string;
using std::cout;

/* function proto */
#ifndef GET_DATA_H
#define GET_DATA_H

int get_data(char *counter, char *probe_output);
void create_column_data (char *src, char *replace);
void modify_data (string &src, const char *pattern, const char *replace);

//int cleanup_top_proc();
//int get_counter_value(char *counter, double *value);

/** Variables used to measure CPU utilization in intervals */
static long s_user = 0 ;
static long s_nice = 0 ;
static long s_system = 0 ;
static double s_timestamp = 0  ;

#define MEM_COUNTER "/proc/meminfo/Mem"
#define SWAP_COUNTER "/proc/meminfo/Swap"
#define CPU_COUNTER "/proc/stat/cpu"
#define PS_COUNTER "/proc/ps"
#define GET_RESOURECE_BUF 100
#define MAX_LINE_BUFFER 400


#endif /* end of GET_DATA_C_H */
