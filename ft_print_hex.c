/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 20:21:21 by marvin            #+#    #+#             */
/*   Updated: 2026/10/18 20:21:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int num, char format)
{
	char	*base;
	int		size;
	int		temp;

	size = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (num >= 16)
	{
		temp = ft_print_hex(num / 16, format);
		if (temp == -1)
			return (-1);
		size += temp;
	}
	if (write(1, &base[num % 16], 1) != 1)
		return (-1);
	return (size + 1);
}
