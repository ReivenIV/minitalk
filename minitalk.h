/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:24:29 by rita              #+#    #+#             */
/*   Updated: 2025/02/13 18:24:29 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <unistd.h>		// for write function
# include <signal.h>		// main lib of these project

//		------------------------
//		::  global variables  ::
//		------------------------
extern char	*global_str;

//		------------------
//		::  tools_strs  ::
//		------------------
int		ft_strlen(char *s);
void	ft_putstr(char *s);
int		ft_atoi(const char *str);
char	*update_global_str(char *str, char c);

//		-----------------
//		::  tools_nbs  ::
//		-----------------
void	ft_putnbr(int n);

//		------------------
//		::  tools_bits  ::
//		------------------
char	handle_incoming_bit(char c, int signal, int *bit_position);

//		---------------------
//		::  tools_signals  ::
//		---------------------
void 	set_signal_action(void(*handler)(int, siginfo_t*, void*), int sigusr);
void	signal_parser(int signal, siginfo_t *info, void *context);

#endif