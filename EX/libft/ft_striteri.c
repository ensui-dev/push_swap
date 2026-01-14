/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:57:27 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/23 17:07:46 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* static void	ft_oddcasex(unsigned int i, char *c)
{
	if (i % 2 != 0)
	{
		if (*c >= 'A' && *c <= 'Z')
			*c += 32;
		else if (*c >= 'a' && *c <= 'z')
			*c -= 32;
	}
}

int	main(void)
{
	char *s;
	s = malloc(6 * sizeof(char));
	if (!s)
		return (1);
	ft_strlcpy(s, "Hello", 6);
	ft_striteri(s, ft_oddcasex);
	printf("%s\n", s);
	free(s);
	return (0);
} */