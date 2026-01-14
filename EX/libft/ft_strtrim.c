/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:01:19 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/23 13:58:14 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#

static int	ft_isset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_ta(size_t *start, size_t *end, char const *set, char const *s1)
{
	char	*trimmed;
	size_t	trimmed_len;

	while (s1[*start] && ft_isset(s1[*start], set))
		(*start)++;
	if (*start < *end)
	{
		while (*end > *start && ft_isset(s1[(*end) - 1], set))
			(*end)--;
	}
	if (*start >= *end)
		trimmed_len = 0;
	else
		trimmed_len = *end - *start;
	trimmed = (char *) malloc(trimmed_len + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	k = ft_strlen(s1);
	trimmed = ft_ta(&i, &k, set, s1);
	while (i < k)
		trimmed[j++] = s1[i++];
	trimmed[j] = '\0';
	return (trimmed);
}
/*
int	main(void)
{
	char	*trim;
	char *totrim = "soHello, Worldows";
	char *set = "ows";

	trim = ft_strtrim(totrim, set);
	printf ("%s", trim);
	return (0);
}*/
