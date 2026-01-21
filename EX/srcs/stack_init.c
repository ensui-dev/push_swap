/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/20 22:47:24 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_stack	*append_node(t_stack **stack, char *str)
{
	long	value;
	t_stack	*node;

	if (!is_valid_number(str))
		return (NULL);
	value = ft_atol(str);
	if (!is_int_range(value))
		return (NULL);
	node = stack_new((int)value);
	if (!node)
		return (NULL);
	stack_add_back(stack, node);
	return (node);
}

static t_stack	*build_stack(char **numbers)
{
	t_stack	*stack;
	int		i;

	stack = NULL;
	i = 0;
	while (numbers[i])
	{
		if (!append_node(&stack, numbers[i]))
		{
			free_stack(&stack);
			return (NULL);
		}
		i++;
	}
	if (has_duplicates(stack))
	{
		free_stack(&stack);
		return (NULL);
	}
	return (stack);
}

t_stack	*init_stack_a(int argc, char **argv)
{
	char	**numbers;
	t_stack	*stack_a;

	stack_a = NULL;
	numbers = NULL;
	numbers = parse_arguments(argc, argv);
	if (!numbers)
		return (NULL);
	stack_a = build_stack(numbers);
	if (!stack_a)
	{
		if (argc == 2)
			free_split(numbers);
		return (NULL);
	}
	if (argc == 2)
		free_split(numbers);
	return (stack_a);
}
