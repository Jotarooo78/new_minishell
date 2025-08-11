/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:07:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/11 11:07:21 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	is_digit(char *str)
{
	int	i;
    int sign;

	i = 0;
    sign = 0;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] == '-' || str[i] == '+')
			{
				sign++;
				if (sign > 1)
				{
					
					return (2);
				}
			}
			else
				return (2);
		}
		i++;
	}
	return (0);
}

long	ft_atol(char *str)
{
	long	i;
	long	res;
	int		neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * -1;
        i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}
