/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:05:11 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/16 20:24:02 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s_ptr;

	s_ptr = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		s_ptr[i] = 0;
		i++;
	}
}

/*int	main(void)
{
	char	str[4] = "test";
	ft_bzero(str, 4);
	printf("%s", str);
	return (0);
}*/
