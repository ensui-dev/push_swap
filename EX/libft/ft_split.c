/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:07:46 by mju-ferr          #+#    #+#             */
/*   Updated: 2025/10/23 13:59:51 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *str, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*ft_copyword(char *str, int len)
{
	char	*word;
	int		i;

	word = (char *) malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_fillres(char **result, char const *str, char c)
{
	size_t	j;
	size_t	len;

	j = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		len = 0;
		while (str[len] && str[len] != c)
			len++;
		if (len > 0)
		{
			result[j] = ft_copyword((char *)str, len);
			if (!result[j])
				return (NULL);
			str += len;
			j++;
		}
	}
	result [j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	**temp;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	result = (char **) ft_calloc((ft_countwords(s, c) + 1), sizeof (char *));
	if (!result)
		return (NULL);
	temp = ft_fillres(result, s, c);
	if (!temp)
	{
		while (result[i])
			free(result[i++]);
		free(result);
		return (NULL);
	}
	return (result);
}
