/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_lld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:23:03 by sjolliet          #+#    #+#             */
/*   Updated: 2026/07/31 14:24:28 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_str_to_lld(const char *nptr)
{
	long long	res;
	long long	sign;
	long long	i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		if (!ft_isdigit(nptr[i]))
			return (0);
		if (res > (LLONG_MAX - (nptr[i] - '0')) / 10)
			return (0);
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
