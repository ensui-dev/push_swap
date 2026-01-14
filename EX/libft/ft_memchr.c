/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:24:48 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/15 15:33:22 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s_ptr;

	s_ptr = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (s_ptr[i] == (unsigned char) c)
			return ((void *) &s_ptr[i]);
		i++;
	}
	return (NULL);
}
