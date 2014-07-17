#include <string.h>
#include <stdio.h>

#include "sock_lib.h"

#define MAX_SIZE 1024


void make_xor(char *msg_1, char *msg_2, char *result, size_t n) {
	int i;
	for (i = 0; i < n; i++) {
		result[i] = msg_1[i] ^ msg_2[i];
	}
}

int main(int argc, char const *argv[]) {
	char msg_1[MAX_SIZE];
	char msg_2[MAX_SIZE];
	char result[MAX_SIZE];
	char result_org[MAX_SIZE];

	strncpy(msg_1, argv[1], MAX_SIZE);
	strncpy(msg_2, argv[2], MAX_SIZE);

	make_xor(msg_1, msg_2, result, MAX_SIZE);
	make_xor(result, msg_2, result_org, MAX_SIZE);

 	printf("MSG1: %s\n", msg_1);
 	printf("MSG2: %s\n", msg_2);
 	printf("RESL: %s\n", result);
 	printf("RESO: %s\n", result_org);
	return 0;
}
