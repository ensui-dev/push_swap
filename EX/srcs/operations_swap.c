/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/20 22:46:34 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_stack **stack_a, int print)
{
	t_stack	*first_node;
	t_stack	*second_node;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	first_node = *stack_a;
	second_node = (*stack_a)->next;
	first_node->next = second_node->next;
	second_node->next = first_node;
	*stack_a = second_node;
	if (print == 1)
		ft_printf("sa\n");
	return ;
}

void	sb(t_stack **stack_b, int print)
{
	t_stack	*first_node;
	t_stack	*second_node;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	first_node = *stack_b;
	second_node = (*stack_b)->next;
	first_node->next = second_node->next;
	second_node->next = first_node;
	*stack_b = second_node;
	if (print == 1)
		ft_printf("sb\n");
	return ;
}

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	if (print == 1)
		ft_printf("ss\n");
}
