#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include "config.h"

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char pin[256];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    ssize_t recv_len = recv(sock, pin, sizeof(pin)-1, 0);
    if (recv_len < 0) {
        perror("Receive failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    pin[recv_len] = '\0';

    printf("Received from server: %s\n", pin);

    printf("Enter your PIN: ");
    fgets(pin, sizeof(pin), stdin);
    pin[strcspn(pin, "\n")] = '\0';

    if (send(sock, pin, strlen(pin), 0) < 0) {
        perror("Send failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    recv_len = recv(sock, pin, sizeof(pin)-1, 0);
    if (recv_len < 0) {
        perror("Receive failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    pin[recv_len] = '\0';

    printf("Server response: %s\n", pin);

    close(sock);

    return 0;
}
