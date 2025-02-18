/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:45:11 by rita              #+#    #+#             */
/*   Updated: 2025/02/18 10:45:11 by rita             ###   ########.fr       */
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
	int	bit_value;

	if (signal == SIGUSR1)
		bit_value = 1;
	if (signal == SIGUSR2)
		bit_value = 0;
	c = c << 1 | bit_value;
	(*bit_count)++;
	return (c);
}
