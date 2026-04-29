#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termcap.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

// < infile< infile2.txt < infile3 wc <infile4 -l |  wc -l  | wc -l > outfile

#endif