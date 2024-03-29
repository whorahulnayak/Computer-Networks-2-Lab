// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>

#define PORT 8080
#define MAXLINE 1024

int palindrome(int n)
{
	int reversed = 0, remainder, original;
	original = n;

	// reversed integer is stored in reversed variable
	while (n != 0)
	{
		remainder = n % 10;
		reversed = reversed * 10 + remainder;
		n /= 10;
	}

	// palindrome if orignal and reversed are equal
	if (original == reversed)
		return 1;
	else
		return 0;
}
// Driver code
int main()
{
	int sockfd;
	char *buffer;
	int n;
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	int len;

	len = sizeof(cliaddr); // len is value/result

	n = recvfrom(sockfd, &n, sizeof(n), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
	// printf("Client : %s\n", buffer);

	// int flag = palindrome(n);
	// printf("%d", flag);
	// if (flag)
	// {
	// 	buffer = "palindrome";
	// }
	// else
	// 	buffer = "not palindrome";
	buffer = "heyyo";
	sendto(sockfd, (char *)buffer, sizeof(buffer), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
	printf("Hello message sent.\n");

	return 0;
}
