/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/15 14:11:58 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	count_total_numbers(int argc, char **argv)
{
	int		i;
	int		count;
	char	**temp;
	int		j;

	i = 1;
	temp = NULL;
	count = 0;
	while (i < argc)
	{
		temp = ft_split(argv[i], ' ');
		if (!temp)
			return (-1);
		j = 0;
		while (temp[j])
		{
			count++;
			j++;
		}
		free_split(temp);
		i++;
	}
	return (count);
}

static char	**join_all_arguments(int argc, char **argv, int total)
{
	char	**result;
	int		i;
	int		j;
	int		result_index;
	char	**temp;

	result = malloc(sizeof(char *) * (total + 1));
	if (!result)
		return (NULL);
	i = 1;
	result_index = 0;
	while (i < argc)
	{
		temp = ft_split(argv[i], ' ');
		if (!temp)
			return (free_split(result), NULL);
		j = 0;
		while (temp[j])
			result[result_index++] = temp[j++];
		free(temp);
		i++;
	}
	result[result_index] = NULL;
	return (result);
}

char	**parse_arguments(int argc, char **argv)
{
	int	total;

	total = 0;
	if (argc < 2)
		return (NULL);
	total = count_total_numbers(argc, argv);
	if (total <= 0)
		return (NULL);
	return (join_all_arguments(argc, argv, total));
}
