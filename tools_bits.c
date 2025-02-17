/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:44:24 by rita              #+#    #+#             */
/*   Updated: 2025/02/14 13:44:24 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//		----------------
//		::  server.c  ::
//		----------------
/*
we define the value of SIGUSR1 & SIGUSR2 and we added to 'c' 
in the bit realm: we move one position to the left inside 'c' byte(8bits)
to the left.
*/
char	handle_incoming_bit(char c, int signal, int *bit_count)
{
	int bit_value;

	// We define values
	if (signal == SIGUSR1)
		bit_value = 1;
	if (signal == SIGUSR2)
		bit_value = 0;

	c = c << 1 | bit_value;		// We move 1 bit to the left then we update the current value with "bit_value".
	(*bit_count)++;				// we update the bit count.
	return (c);
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
			if (bit = 1)
				kill(pid, SIGUSR1);
			if (bit = 0)
				kill(pid, SIGUSR2);
			i--;
			check_res_server();
		}
		str++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		check_res_server();
		i++;
	}
}