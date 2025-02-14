/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:49:01 by rita              #+#    #+#             */
/*   Updated: 2025/02/14 14:49:01 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_parser(int signal, sigiinfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = 0;

	(void)context;
	c = handle_incoming_bit(c, signal, &bit);
	if (bit == 8)
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
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}
