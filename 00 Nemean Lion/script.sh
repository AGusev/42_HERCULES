# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agusev <agusev@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 22:48:26 by agusev            #+#    #+#              #
#    Updated: 2019/03/01 23:08:56 by agusev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

if [[ $EUID > 0 ]]; then
	echo "Run, pozhaluista, as root/sudo"
	exit 1
else
	#Install OpenSSH server repository
	apt-get install openssh-server -y
	#Making copy of the original repository
	cp /etc/ssh/sshd_config /etc/ssh/sshd_config_copy
	#Replacing port by default, which is Port 22, with the new one
	sed -i 's/^.*Port 22/Port 6969/g' /etc/ssh/sshd_config
	#Restart the SSH service with the new port number
	/etc/init.d/ssh restart
fi
# run sh script.sh
# *run tty
# run "ssh <username>@<ip-address>"
# else run "ssh <username>@<ip-address> -p <port-number>"
