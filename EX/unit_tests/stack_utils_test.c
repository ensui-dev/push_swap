/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/15 12:48:01 by mju-ferr         ###   ########.fr       */
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
		if(!stack->next)
			ft_printf("Stack(%s) next value: NULL\n", stack_name);
		else
			ft_printf("Stack(%s) next value: %d\n", stack_name, stack->next->value);
		return (1);
	}
}

int	test_stack_utils(void)
{
	t_stack *new;
	t_stack *back;
	t_stack	*front;
	t_stack	*last;
	int		test_size;

	ft_printf("\n===== TEST \"stack_new\" =====\n");
	new = stack_new(42);
	if (!(output_stack_state(new, "New")))
	{
		ft_printf("Invalid Output.\n");
		return (0);
	}
	ft_printf("\n===== TEST \"stack_add_back\" =====\n");
	back = stack_new(84);
	stack_add_back(&new, back);
	if (!(output_stack_state(new, "Back")))
	{
		ft_printf("Invalid Output.\n");
		return (0);
	}
	ft_printf("\n===== TEST \"stack_add_front\" =====\n");
	front = stack_new(21);
	stack_add_front(&new, front);
	if (!(output_stack_state(new, "Front")))
	{
		ft_printf("Invalid Output.\n");
		return (0);
	}
	ft_printf("\n===== TEST \"stack_last\" =====\n");
	last = stack_last(new);
	if (!(output_stack_state(new, "Last")))
	{
		ft_printf("Invalid Output.\n");
		return (0);
	}
	ft_printf("\n===== TEST \"stack_size\" =====\n");
	test_size = stack_size(new);
	if (test_size == 0)
	{
		ft_printf("Size not found.\n");
		return (0);
	}
	else
		ft_printf("Stack size: %d\n", test_size);
	return (1);
}

int	main(void)
{
	test_stack_utils();
	return (0);
}