/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/20 22:45:39 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	copy_values_to_array(t_stack *stack, int *arr, int size)
{
	int	i;

	if (!arr || !stack)
		return ;
	if (size <= 0)
		return ;
	i = 0;
	while (i < size && stack)
	{
		arr[i] = stack->value;
		stack = stack->next;
		i++;
	}
	return ;
}

void	sort_int_array(int *arr, int size)
{
	int	i;
	int	j;
	int	min_idx;
	int	temp;

	if (!arr || size <= 1)
		return ;
	i = -1;
	while (++i < size - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
			j++;
		}
		if (min_idx != i)
		{
			temp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = temp;
		}
	}
}

int	get_index_position(int *arr, int size, int value)
{
	int	i;

	if (!arr || size <= 0)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (arr[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

void	assign_index(t_stack *stack)
{
	int		size;
	int		*values;
	t_stack	*current;

	if (!stack)
		return ;
	size = stack_size(stack);
	if (size == 0 || size == 1)
		return ;
	values = malloc(sizeof(int) * size);
	if (!values)
		return ;
	copy_values_to_array(stack, values, size);
	sort_int_array(values, size);
	current = stack;
	while (current)
	{
		current->index = get_index_position(values, size, current->value);
		current = current->next;
	}
	free(values);
}
