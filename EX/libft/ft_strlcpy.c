/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:08:41 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/15 00:21:30 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/*#include <stdio.h>
int	main(void)
{
	char	test_src[] = "This is a test.";
	char	test_dest[16];
	int	num = 3;

	printf("The src '%s'\n", test_src);
	printf("Returned Len of '%zu'\n", ft_strlcpy(test_dest, test_src, num));
	printf("Dest value is now '%s'\n", test_dest);
}*/