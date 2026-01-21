/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/21 12:01:02 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_two(t_stack **stack_a)
{
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}

void	sort_three(t_stack **stack_a)
{
	int	max;

	if (!stack_a || !*stack_a)
		return ;
	if (stack_size(*stack_a) < 3)
		return ;
	max = find_max(*stack_a);
	if ((*stack_a)->value == max)
	{
		ra(stack_a, 1);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
	else if ((*stack_a)->next->value == max)
	{
		rra(stack_a, 1);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
	else
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
}

void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	min_idx;

	if (!stack_a || !stack_b || !*stack_a || stack_size(*stack_a) < 4)
		return ;
	min_idx = find_min_index(*stack_a);
	if (min_idx == 1)
		sa(stack_a, 1);
	else if (min_idx == 2)
	{
		rra(stack_a, 1);
		rra(stack_a, 1);
	}
	else if (min_idx == 3)
		rra(stack_a, 1);
	pb(stack_a, stack_b, 1);
	sort_three(stack_a);
	pa(stack_a, stack_b, 1);
}
