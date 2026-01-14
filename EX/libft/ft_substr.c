/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:27:59 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/23 14:15:31 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (start >= j)
	{
		new_s = malloc(1);
		if (!new_s)
			return (NULL);
		new_s[0] = '\0';
		return (new_s);
	}
	if (start + len > j)
		len = j - start;
	new_s = malloc(len + 1);
	if (!new_s)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		new_s[i] = s[start + i];
	new_s[i] = '\0';
	return (new_s);
}

/*int	main(void)
{
	char *str = "Hello, World!";
	unsigned int	start = 7;
	size_t	len = 3;
	
	printf("%s", ft_substr(str, start, len));
	return (0);
}*/