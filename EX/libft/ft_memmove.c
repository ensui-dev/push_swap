/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:36:45 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/14 23:51:07 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;
	size_t				i;

	dest_ptr = (unsigned char *) dest;
	src_ptr = (const unsigned char *) src;
	if (dest_ptr > src_ptr)
	{
		i = n;
		while (i-- > 0)
			dest_ptr[i] = src_ptr[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char str[100] = "Learningisfun";
    char *first, *second;
    first = str;
    second = str;

	char *st2r = ft_memmove(first, "second", 4);
	printf("%s", st2r);
	char *st2r = memmove(first, "second", 4);
	printf("%s", st2r);
	return (0);
}*/