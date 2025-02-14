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

static char *str = NULL;

static void signals_parser(int sig, siginfo_t *info, void *context)
{
	
}

int	main(int ac, char **av)
{

	if (ac == 1)
	{
		ft_putstr("Server PID my dear :: ");
		ft_putnbr(getpid());
		write(1, "\n", 1);
		while(1)
			pause();
		free(str);
	}
	exit(0);
	return (0);
}