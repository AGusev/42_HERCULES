/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusev <agusev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:18:32 by agusev            #+#    #+#             */
/*   Updated: 2019/03/09 17:32:10 by agusev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define PORT_NUM 5050

int main(int ac, char **av)
{
    int                 sock;
    int                 bytes_read;
    int                 sock_accept;
    char                buf[256];
    struct sockaddr_in  addr;
    socklen_t           addr_size;
    int                 port;
    int                 flag;

    printf("\033[1;33m");
    if (ac == 2)
    {
        flag = 0;
        port = atoi(av[1]);
    }
    else if (ac == 3 && !strcmp(av[1], "-D"))
    {
        flag = 1;
        port = atoi(av[2]);
        printf("\033[1;31mRunning as Daemon\033[5;33m\n");
    }
    else
        printf("\033[1;31mEther port or command provided incorrectly\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("\033[1;31mCould not create a socket\n");
        return (0);
    }
    printf("\033[1;32mSocket has been successfully created\n");
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)))
    {
        printf("\033[1;31mFailed to bind\n");
        return (0);
    }
    printf("\033[1;32mSocket has been successfully bound\n");
    if (listen (sock, 5) == -1)
    {
        printf("\033[1;31mFailed to listen");
        return (0);
    }
    printf("\033[1;35mListeting...\n");
    printf("\033[1;32mServer ready to connect...\n");
    while (1)
    {
        if (flag)
            daemon(0, 0);
        addr_size = sizeof(addr);
        sock_accept = accept(sock, (struct sockaddr*)&addr, &addr_size);
        if (sock_accept < 0)
        {
            printf("\033[1;31mError to accept\n");
            return (0);
        }
        else
        {
            bytes_read = recv(sock_accept, buf, 255, 0);
            if (bytes_read <= 0)
                break ;
            buf[bytes_read] = '\0';
            if (!strncmp(buf, "ping", 4) && !flag)
                send(sock_accept, "\n\033[1;37mpong \npong\n", 20, 0);
            else if (!strncmp(buf, "ping", 4) && flag)
                send(sock_accept, "\033[1;31m\nRunning as Daemon\033[1;37m\npong\n\033[1;37mpong\n", 50, 0);
        }
        close(sock_accept);
    }
    return (0);
}