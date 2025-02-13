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

//		-------------
//		::  tools  ::
//		-------------
int		ft_strlen(char *s);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
int		ft_atoi(const char *str);


#endif