# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    readme.txt                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agusev <agusev@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/09 17:34:08 by agusev            #+#    #+#              #
#    Updated: 2019/03/09 17:35:10 by agusev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER: 

1. Compile the server.c using <gcc server.c -o server>
2. Run server providing the port e.g. <./server 5000>, 
    where port number = 5000;
3. If running as daemon use  <./server -D 5000>
    -> to silence warnings use -w flag
    -> to stop daemon provide in the terminal line <killall server>
    -> to see the process in background use <top>


CLIENT:

1. Compile the client.c using <gcc client.c -o client>
2. Run client providing IP & port number e.g. <./client 127.0.0.1 5000>,
    where IP = 127.0.0.1, port number = 5000
3. Enter message <ping>
4. You are supposed to get <pong pong> answer.