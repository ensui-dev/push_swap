/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/19 14:01:47 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_stack **stack_a, int print)
{
	t_stack	*first_node;
	t_stack	*second_node;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	first_node = *stack_a;
	second_node = (*stack_a)->next;
	first_node->next = second_node->next;
	*stack_a = second_node;
	second_node->next = first_node;
	if (print == 1)
		ft_printf("sa\n");
	return ;
}