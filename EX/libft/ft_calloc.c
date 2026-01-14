/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:49:07 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/16 20:30:29 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	new = malloc (nmemb * size);
	if (!new)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}

/*int	main(void)
{
	int	*tab;
	tab = calloc(4, sizeof(tab));
	tab[0] = 1;
	tab[1] = 4;
	tab[2] = 5;
	tab[3] = 0;
	while (*tab != 0)
	{
		printf("%d\n", *tab);
		tab++;
	}
	return (0);
}*/