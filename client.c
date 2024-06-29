/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:15:15 by ariling           #+#    #+#             */
/*   Updated: 2024/06/29 19:03:35 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

void	send_bits(char c, pid_t pid)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if (bit == 1)
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(300);
		i--;
	}
}

void	message_sender(const char *message, int pid)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_bits(message[i], pid);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int			pid;
	const char	*message = argv[2];

	if (argc != 3)
	{
		ft_printf("Wrong input!!\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_printf("Received server pid: %d\n", pid);
	message_sender(message, pid);
	return (0);
}
