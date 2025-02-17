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

int	main(int ac, char **av)
{
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