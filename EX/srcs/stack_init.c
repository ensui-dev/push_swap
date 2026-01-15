/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/15 17:08:31 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_stack	*append_node(t_stack **stack, char *str)
{
	int		value;
	t_stack	*node;

	if (!is_valid_number(str))
		return (NULL);
	value = ft_atoi(str);
	if (!is_int_range(value))
		return (NULL);
	
}

t_stack	*init_stack_a(int argc, char **argv)
{
	char	**numbers;
	t_stack	*stack_a;
	int		i;
	int		value;

	numbers = parse_arguments(argc, argv);
	if (!numbers)
		return (NULL);
	stack_a = NULL;
	i = 0;
	value = 0;
	while (numbers[i])
	{
		if (!(is_valid_number(numbers[i])))
		{
			free_stack(&stack_a);
			if (argc == 2)
				free_split(numbers);
			return (NULL);
		}
		value = ft_atoi(numbers[i]);
		if (!(is_int_range(value)))
		{
			free_stack(&stack_a);
			if (argc == 2)
				free_split(numbers);
			return (NULL);
		}
		i++;
	}
}
