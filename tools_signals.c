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

void set_signal_action(void(*handler)(int, siginfo_t*, void*), int sigusr)
{
    struct	sigaction	sig; 														// Declare a sigaction structure

    sig.sa_sigaction = handler;														// Set the handler function for the signal
    sigemptyset(&sig.sa_mask); 														// Initialize the signal mask to empty
    sig.sa_flags = SA_SIGINFO;				 										// Set flags to get detailed signal info and restart interrupted system calls

    if (sigusr == 1)
        sigaction(SIGUSR1, &sig, NULL); 											// Set the action for SIGUSR1
    else if (sigusr == 2)
        sigaction(SIGUSR2, &sig, NULL); 											// Set the action for SIGUSR2
    else
    {
        sigaction(SIGUSR1, &sig, NULL); 											// Set the action for SIGUSR1
        sigaction(SIGUSR2, &sig, NULL); 											// Set the action for SIGUSR2
    }
}

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
