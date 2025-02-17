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

// Will init the struct siginfo_t 
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

// client : Will wait/listen the server till answer that it received the msg
void	stablish_link_with_server(int signum, siginfo_t *info, void *content)
{
	(void)	context;
	(void)	info;
	if (signum == SIGUSR1 || signum == SIGUSR2)
		g_acknowledgment_status = 1;
	else
	{
		write(2, "problem with the server\n", 20);
		exit(EXIT_FAILURE);
	}
}

void	wait_validation_from_server(void)
{
	int	retries = 1000;

	while (!g_acknowledgment_status && retries > 0)
	{
		usleep(100)
		retries--;
	}
	if (retries == 0)
	{
		write(2, "server fail to validate", 23);
        exit(EXIT_FAILURE);
	}
	g_acknowledgment_status = 0;
}