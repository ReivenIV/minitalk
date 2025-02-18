/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwebe-ir <fwebe-ir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:58:45 by rita              #+#    #+#             */
/*   Updated: 2025/02/17 14:31:50 by fwebe-ir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_str = NULL;

void	signal_parser(int signal, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit_count = 0;

	(void)context;
	c = handle_incoming_bit(c, signal, &bit_count);
	if (bit_count == 8)
	{
		if (c == '\0')
		{
			ft_putstr(g_str);
			free(g_str);
			g_str = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			g_str = update_global_str(g_str, c);
			if (g_str == NULL)
				return ;
		}
		c = 0;
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	(void) av;
	if (ac == 1)
	{
		write(1, "Server PID my dear :: ", 22);
		ft_putnbr(getpid());
		write(1, "\n", 1);
		set_signal_action(&signal_parser, 3);
		while (1)
			pause();
		free(g_str);
	}
	exit(0);
	return (0);
}
