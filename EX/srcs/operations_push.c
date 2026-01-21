/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/20 22:46:02 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*temp;

	if (!stack_a || !stack_b || !*stack_b)
		return ;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = NULL;
	stack_add_front(stack_a, temp);
	if (print == 1)
		ft_printf("pa\n");
	return ;
}

void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*temp;

	if (!stack_a || !stack_b || !*stack_a)
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = NULL;
	stack_add_front(stack_b, temp);
	if (print == 1)
		ft_printf("pb\n");
	return ;
}
