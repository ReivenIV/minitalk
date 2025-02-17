/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:58:45 by rita              #+#    #+#             */
/*   Updated: 2025/02/13 17:58:45 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char *global_str = NULL;

// Server : 
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
			ft_putstr(global_str);
			free(global_str);
			global_str = NULL;
		}
		else
		{
			global_str = update_global_str(global_str, c);
			if (global_str == NULL)
				return ;
		}
		c = 0;
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}


int	main(int ac, char **av)
{
	(void)	av;
	if (ac == 1)
	{
		write(1, "Server PID my dear :: ", 22);
		ft_putnbr(getpid());
		write(1, "\n", 1);
		set_signal_action(&signal_parser, 3);
		while(1)
			pause();
		free(global_str);
	}
	exit(0);
	return (0);
}