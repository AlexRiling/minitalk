/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:15:15 by ariling           #+#    #+#             */
/*   Updated: 2024/10/29 15:14:09 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"  // Your own header for ft_printf and ft_atoi

void send_bits(char c, pid_t pid)
{
    int i;
    int bit;

    i = 7;
    while (i >= 0)
    {
        bit = (c >> i) & 1;
        if (bit == 1)
        {
            if (kill(pid, SIGUSR1) == -1)
            {
                perror("Failed to send SIGUSR1");
                exit(1);
            }
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
            {
                perror("Failed to send SIGUSR2");
                exit(1);
            }
        }
        usleep(2000);  // Increased delay to ensure the server processes each signal reliably
        i--;
    }
}

void message_sender(const char *message, pid_t pid)
{
    int i = 0;

    while (message[i] != '\0')
    {
        send_bits(message[i], pid);
        i++;
    }
    send_bits('\0', pid); // Send null character to indicate end of message
}

int main(int argc, char *argv[])
{
    int pid;
    const char *message;

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



