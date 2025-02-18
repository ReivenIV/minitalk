/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:26:45 by rita              #+#    #+#             */
/*   Updated: 2025/02/17 14:35:06 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_acknowledgment_status = 0;

// client : Will wait/listen the server till answer that it received the msg
void	stablish_link_with_server(int signum, siginfo_t *info, void *content)
{
	(void) content;
	(void) info;
	if (signum == SIGUSR1)
		g_acknowledgment_status = 1;
	else if (signum == SIGUSR2)
		write(1, "Thanks my dear, msg received!\n", 30);
	else
	{
		write(2, "problem with the server\n", 20);
		exit(EXIT_FAILURE);
	}
}

//client : after sending data to server we way validation receipt
void	wait_validation_from_server(void)
{
	int	retries;

	retries = 1000;
	while (!g_acknowledgment_status && retries > 0)
	{
		usleep(100);
		retries--;
	}
	if (retries == 0)
	{
		write(2, "server fail to validate", 23);
		exit(EXIT_FAILURE);
	}
	g_acknowledgment_status = 0;
}

// client: will send an *str "bit by bit" to server's pid. 
void	handle_send_signal(int pid, char *str)
{
	int	bit;
	int	i;

	while (*str)
	{
		i = 7;
		while (i >= 0)
		{
			bit = (*str >> i) & 1;
			if (bit == 1)
				kill(pid, SIGUSR1);
			if (bit == 0)
				kill(pid, SIGUSR2);
			i--;
			wait_validation_from_server();
		}
		str++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		wait_validation_from_server();
		i++;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		write(2, "Something wrong my dear\n", 24);
		return (0);
	}
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (kill(pid, 0) == -1)
		{
			write(2, "Wrong PID my dear\n", 18);
			return (0);
		}
		if (av[2] == NULL)
			return (0);
		set_signal_action(stablish_link_with_server, 3);
		handle_send_signal(pid, av[2]);
		return (0);
	}
}
