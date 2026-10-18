/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 21:42:42 by marvin            #+#    #+#             */
/*   Updated: 2026/10/18 21:42:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_nbr(int n)
{
	long	num;
	int		size;
	int		temp;
	char	c;

	num = n;
	size = 0;
	if (num < 0)
	{
		if (write(1, "-", 1) != 1)
			return (-1);
		num = -num;
		size++;
	}
	if (num >= 10)
	{
		temp = ft_print_nbr(num / 10);
		if (temp == -1)
			return (-1);
		size += temp;
	}
	c = num % 10 + '0';
	if (write(1, &c, 1) != 1)
		return (-1);
	return (size + 1);
}
