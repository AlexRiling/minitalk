/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:15:15 by ariling           #+#    #+#             */
/*   Updated: 2024/11/08 12:11:20 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(pid_t pid, int signal, const char *error_msg)
{
	if (kill(pid, signal) == -1)
	{
		perror(error_msg);
		exit(1);
	}
}

void	send_bits(char c, pid_t pid)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if (bit == 1)
			send_signal(pid, SIGUSR1, "Failed to send SIGUSR1");
		else
			send_signal(pid, SIGUSR2, "Failed to send SIGUSR2");
		usleep(300);
		i--;
	}
}

void	message_sender(const char *message, pid_t pid)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_bits(message[i], pid);
		i++;
	}
	send_bits('\0', pid);
}

int	main(int argc, char *argv[])
{
	int			pid;
	const char	*message;

	if (argc != 3)
	{
		ft_printf("Wrong input! Usage: ./client <PID> <message>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Invalid PID provided.\n");
		return (1);
	}
	message = argv[2];
	ft_printf("Received server PID: %d\n", pid);
	message_sender(message, pid);
	return (0);
}
