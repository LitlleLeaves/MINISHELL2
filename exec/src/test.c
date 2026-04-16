#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// int main(void)
// {
// 	// int fd_in = open("a", O_RDONLY);
// 	// if (fd_in == -1)
// 	// {
// 	// 		printf("%s: %s\n", "a", strerror(errno));
// 	// }

// 	// if (access("NoPerm", X_OK) != 0)
// 	// 	printf("1: %s: %s\n", "NoPerm", strerror(errno));
// 	// if (access("NoFile", X_OK) != 0)
// 	// 	printf("2: %s: %s\n", "NoPerm", strerror(errno));
// 	// if (access("NoPerm", F_OK) != 0)
// 	// 	printf("3: %s: %s\n", "NoPerm", strerror(errno));
// 	// if (access("NoFile", F_OK) != 0)
// 	// 	printf("4: %s: %s\n", "NoPerm", strerror(errno));

// 	char *env = getenv("HOME");
// 	printf("%s", env);
// }
