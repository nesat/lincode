#include "sock_lib.h"

int main(int argc, char const *argv[])
{
	int sock_fd;
	struct sockaddr_in server_addr;
	char message[MAX_MSG_SIZE + 1];
	
	memset(message, 0, sizeof(message));
	strncpy(message, argv[1], MAX_MSG_SIZE);
	message[MAX_MSG_SIZE] = '\0';

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket open error\n");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(UNARY_PORT);
	if (inet_pton(AF_INET, UNARY_SERVER, &server_addr.sin_addr) <= 0) {
		perror("inet_pton error\n");
		exit(1);
	}

	if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		perror("Connect error\n");
		exit(1);
	}

	if (send(sock_fd, message, strlen(message), 0) < 0) {
		perror("Send error");
	}

	



	return 0;
}
