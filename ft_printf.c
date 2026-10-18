/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:53:00 by marvin            #+#    #+#             */
/*   Updated: 2026/10/18 18:53:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert(char c, va_list args)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_print_char(va_arg(args, int));
	else if (c == 's')
		size += ft_print_str(va_arg(args, char *));
	else if (c == 'p')
		size += ft_print_ptr(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		size += ft_print_nbr(va_arg(args, int));
	else if (c == 'u')
		size += ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		size += ft_print_hex(va_arg(args, unsigned int), c);
	else if (c == '%')
		size += write(1, "%", 1);
	return (size);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		i;
	int		size;

	i = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			size = ft_convert(format[i], args);
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (size);
}
