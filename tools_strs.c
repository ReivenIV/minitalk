/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_strs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:15:07 by rita              #+#    #+#             */
/*   Updated: 2025/02/13 18:15:07 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_strlen(char *s)
{
	int	ret;

	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}
void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

int	ft_atoi(char *str)
{
	int	i;
	int	power;
	int	res;

	i = 0;
	res = 0;
	power = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			power = power * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * power);
}
// Will update the global str with the newly created incoming char.
char	*update_global_str(char *str, char c)
{
	char *updated_str;
	int i;

	if (!str)
	{
		updated_str = malloc(sizeof(char) * 2);
		if (!updated_str)
			return (NULL);
		updated_str[0] = c;
		updated_str[1] = '\0';
		return(updated_str);		
	}
	updated_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!updated_str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		updated_str[i] = str[i];
		i++;
	}
	updated_str[i] = c;
	updated_str[i + 1] = '\0';
	free(str);
	return (updated_str); 
}
