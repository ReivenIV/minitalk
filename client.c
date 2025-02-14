/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:26:45 by rita              #+#    #+#             */
/*   Updated: 2025/02/13 18:26:45 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// TODO
/*
	- check a way to declare g_received_ack in .h
	- what is volatile ? 
	- ack_handler : why ? 
	- wait_sig : 	why ? 


*/

int	main(int ac, char **av)
{
	int	pid;

	if (ac !=)
		return (0);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (kill(pid, 0) == -1)
			return (0);
		if (av[2] == NULL)
			return (0);
		set_signal_action(send_msg, 3);	// TODO send_msg 
	}

}