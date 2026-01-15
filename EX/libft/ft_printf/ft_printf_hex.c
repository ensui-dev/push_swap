/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 10:55:20 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/12/31 11:10:18 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_puthex(unsigned long n, char format)
{
	char	*base;
	int		len;

	len = ft_hexlen(n);
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
		ft_puthex(n / 16, format);
	ft_putchar(base[n % 16]);
	return (len);
}

int	ft_putptr(unsigned long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
	{
		count += ft_putstr("(nil)");
		return (count);
	}
	count += ft_putstr("0x");
	count += ft_puthex(ptr, 'x');
	return (count);
}
