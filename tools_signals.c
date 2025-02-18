/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:45:24 by rita              #+#    #+#             */
/*   Updated: 2025/02/18 10:45:24 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Will init the struct siginfo_t 
void	set_signal_action(void (*handler)(int, siginfo_t*, void*), int sigusr)
{
	struct sigaction	sig;

	sig.sa_sigaction = handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	if (sigusr == 1)
		sigaction(SIGUSR1, &sig, NULL);
	else if (sigusr == 2)
		sigaction(SIGUSR2, &sig, NULL);
	else
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
	}
}
