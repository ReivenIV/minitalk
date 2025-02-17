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
