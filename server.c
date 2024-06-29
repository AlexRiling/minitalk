/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:15:00 by ariling           #+#    #+#             */
/*   Updated: 2024/06/29 19:04:18 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

void	handle_signal(int signum)
{
	static int	bit_index = 0;
	static char	current_char = 0;

	if (signum == SIGUSR1)
	{
		current_char = (current_char << 1) | 1;
		ft_printf("Received bit: 1\n");
	}
	else if (signum == SIGUSR2)
	{
		current_char = (current_char << 1) | 0;
		ft_printf("Received bit: 0\n");
	}
	bit_index++;
	if (bit_index == 8)
	{
		write(1, &current_char, 1);
		bit_index = 0;
		current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1)
	{
		perror("sigaction");
		exit(1);
	}
	pid = getpid();
	ft_printf("Server pid: %d\n", pid);
	while (1)
	{
		pause();
	}
	return (0);
}
