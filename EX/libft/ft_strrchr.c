/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:32:58 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/15 15:33:32 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	while (1)
	{
		if (s[s_len] == (char) c)
			return ((char *) &s[s_len]);
		if (s_len == 0)
			return (NULL);
		s_len--;
	}
	return (NULL);
}
