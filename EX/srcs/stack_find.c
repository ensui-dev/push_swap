/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/15 14:14:05 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_min(t_stack *stack)
{
	int	min;

	if (!stack)
		return (INT_MAX);
	min = stack->value;
	stack = stack->next;
	while (stack)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return (min);
}

int	find_max(t_stack *stack)
{
	int	max;

	if (!stack)
		return (INT_MIN);
	max = stack->value;
	stack = stack->next;
	while (stack)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	return (max);
}

int	find_min_index(t_stack *stack)
{
	int	pos;
	int	min;

	if (!stack)
		return (-1);
	min = find_min(stack);
	pos = 0;
	while (stack)
	{
		if (stack->value == min)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

int	find_max_index(t_stack *stack)
{
	int	pos;
	int	max;

	if (!stack)
		return (-1);
	max = find_max(stack);
	pos = 0;
	while (stack)
	{
		if (stack->value == max)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

int	is_sorted(t_stack *stack)
{
	if (!stack || !stack->next)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
