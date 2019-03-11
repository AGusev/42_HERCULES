/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusev <agusev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:05:37 by agusev            #+#    #+#             */
/*   Updated: 2019/03/09 17:30:37 by agusev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
    int                 sock;
    char                buf[256];
    struct sockaddr_in  addr;

    printf("\033[1;32m");
    if (ac != 3)
	{
		printf("\033[1;31mPlease, provide [IP] and [PORT]\n");
		return (0);
	}
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Could not create a socket\n");
        return (0);
    }
    printf("\032[1;32mSocket has been successfully created\n");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(av[2]));
    addr.sin_addr.s_addr = inet_addr(av[1]);
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("\033[1;31mCould not connect\n");
        return (0);
    }
    printf("\033[1;33mEstablishing connection...\n");
    printf("\033[1;35mEnter message: \033[1;37m\n");
	bzero(buf, 256);
	fgets(buf, 255, stdin);
	if (send(sock, buf, strlen(buf), 0) == -1)
    {
        printf("\033[1;31mError occured while sending the message!\n");
        return (0);
    }
    printf("\033[1;32mMessage has been sent\n");
	bzero(buf, 256);
	if (recv(sock, buf, 50, 0) <= 0)
    {
        printf("\033[1;31mError occured while recieving the message\n");
        return (0);
    }
	buf[50] = '\0';
	printf("\033[1;32mVous avez un nouveau message: %s\n", buf);
	close(sock);
	return (0);
}