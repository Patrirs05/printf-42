/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 19:47:49 by marvin            #+#    #+#             */
/*   Updated: 2026/10/18 19:47:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex(unsigned long num)
{
	char	*base;
	int		size;
	int		temp;

	base = "0123456789abcdef";
	size = 0;
	if (num >= 16)
	{
		temp = ft_print_hex(num / 16);
		if (temp == -1)
			return (-1);
		size += temp;
	}
	if (write(1, &base[num % 16], 1) != 1)
		return (-1);
	return (size + 1);
}

int	ft_print_ptr(void *ptr)
{
	unsigned long	address;
	int				size;

	address = (unsigned long) ptr;
	if (!ptr)
		return (write(1, "(nil)", 5));
	if (write(1, "0x", 2) != 2)
		return (-1);
	size = ft_print_hex(address);
	if (size == -1)
		return (-1);
	return (size + 2);
}
