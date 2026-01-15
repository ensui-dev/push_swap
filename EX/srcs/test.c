/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/15 02:15:03 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	output_stack_state(t_stack *stack, const char *stack_name)
{
	if (!stack || !stack_name)
	{
		ft_printf("Invalid Input for stack output.\n");
		return (0);
	}
	else
	{
		ft_printf("Stack(%s) value: %d\n", stack_name, stack->value);
		ft_printf("Stack(%s) index: %d\n", stack_name, stack->index);
		ft_printf("Stack(%s) pos: %d\n", stack_name, stack->pos);
		ft_printf("Stack(%s) target_pos: %d\n", stack_name, stack->target_pos);
		ft_printf("Stack(%s) cost_a: %d\n", stack_name, stack->cost_a);
		ft_printf("Stack(%s) cost_b: %d\n", stack_name, stack->cost_b);
		ft_printf("Stack(%s) next: %d\n", stack_name, stack->next);
		return (1);
	}
}

int	test_stack_utils(void)
{
	t_stack *test;

	test = stack_new(42);
	if (!(output_stack_state(test, NULL)))
		return (0);
	return (1);
}

int	main(void)
{
	test_stack_utils();
	return (0);
}