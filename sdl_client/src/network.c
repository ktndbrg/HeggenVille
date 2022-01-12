/*
 * network.c
 * This file is part of HeggenVille
 *
 * Copyright (C) 2018 - Calvin T. Maxwell
 *
 * HeggenVille is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * HeggenVille is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HeggenVille. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>
#include <SDL/SDL.h>
#include "init.h"
#include "database.h"
#include "network.h"
#include "update.h"

int sock;
int port;
struct sockaddr_in sa;
struct hostent *hostlist;
char dotted_ip[15];

void network (void)
{
	/* Connect to server, and create a thread to monitor the socket */
	hostlist = gethostbyname ("127.0.0.1");
	inet_ntop (AF_INET, hostlist->h_addr_list[0], dotted_ip, 15);
	printf ("Dotted_ip: %s\n", dotted_ip);
	
	sock = socket (PF_INET, SOCK_STREAM, IPPROTO_IP);
	memset (&sa, 0, sizeof (struct sockaddr_in));
	sa.sin_port = htons (8920); /* Port */
	memcpy (&sa.sin_addr, hostlist->h_addr_list[0], hostlist->h_length);
	sa.sin_family = AF_INET;
	
	if (connect (sock, (struct sockaddr *)&sa, sizeof (sa)) < 0)
	{
		fprintf (stderr, "Unable to connect to Server, IP: %s on Port: %d\n", dotted_ip, port);
		exit (EXIT_FAILURE);
	}
	
	void *buffer = malloc (sizeof (unsigned int));
	unsigned int *buf = buffer;
	*buf = 1337;
	
	write (sock, buffer, sizeof (unsigned int));
	free (buffer);
	buffer = NULL;
	
	buffer = malloc (sizeof (unsigned int));
	unsigned int rev = 0;
	read (sock, buffer, sizeof (unsigned int));
	buf = buffer;
	rev = *buf;
	printf ("We sent 1337, and we received: %d\n", rev);
	free (buffer);
	
	close (sock);
	
	return;
}

void client_close (void)
{
	close (sock);
	
	exit (EXIT_SUCCESS);
}

