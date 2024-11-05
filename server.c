/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:15:00 by ariling           #+#    #+#             */
/*   Updated: 2024/11/05 22:48:47 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signum)
{
	static int	bit_index = 0;
	static char	current_char = 0;

	if (signum == SIGUSR1)
		current_char = (current_char << 1) | 1;
	else if (signum == SIGUSR2)
		current_char = (current_char << 1) | 0;
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
			write(1, "\n", 1);
		else
		{
			if (write(1, &current_char, 1) == -1)
			{
				perror("Failed to write character");
				exit(1);
			}
		}
		bit_index = 0;
		current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_handler = handle_signal;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror("Failed to initialize signal set");
		exit(1);
	}
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("Failed to set up sigaction");
		exit(1);
	}
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
