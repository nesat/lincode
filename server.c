#include "sock_lib.h"

int main(int argc, char const *argv[]) {
	int listen_fd, expected_connection, connection;
	int conn_fd_arr[MAX_CONNECTION];
	struct sockaddr_in server_addr;
	char buffer[MAX_MSG_SIZE];

	int i, nfds, fd, read_numb;
	fd_set read_fds;
	struct timeval time_out;
	int ready;

	expected_connection = 0;

	if (argc > 2) {
		perror("Wrong number of arguments.\n");
		exit(1);
	}

	expected_connection = strtol(argv[1], NULL, 10);
	printf("Expected connection: %d\n", expected_connection);

	char messages[expected_connection][MAX_MSG_SIZE];

	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket open error\n");
		exit(1);
	}  

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(UNARY_PORT);

	time_out.tv_sec = 0;
	time_out.tv_usec = 10000;

	if (bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		perror("Socket bind error\n");
		exit(1);
	}

	if (listen(listen_fd, MAX_CONNECTION) < 0) {
		perror("Socket listen error\n");
		exit(1);
	}

	while (connection < expected_connection) {
		conn_fd_arr[connection++] = accept(listen_fd, (struct sockaddr *) NULL, NULL);
		printf("So far %d connection\n", connection);
	}

	// START READING FROM ARRAY OF SOCKETS
	nfds = 1;
	FD_ZERO(&read_fds);
	for (i = 0; i < expected_connection; i++) {
		fd = conn_fd_arr[i];
		if (fd >= nfds) {
			nfds = fd + 1;
		}
		FD_SET(fd, &read_fds);
	}

	ready = select(nfds, &read_fds, NULL, NULL, &time_out);
	for (i = 0; i < nfds; i++) {
		int current_fd = conn_fd_arr[i];
		if (FD_ISSET(i, &read_fds)) {
			printf("Ready: %d\n", i);
			read_numb = read(i, buffer, MAX_MSG_SIZE);
			buffer[MAX_MSG_SIZE - 1] = '\0';
			printf("Message %d: %s\n", i, buffer);
			strncpy(messages[current_fd], buffer, MAX_MSG_SIZE + 1);
		}
	}

	close(listen_fd);
	return 0;
}
