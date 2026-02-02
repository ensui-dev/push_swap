/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/02/02 04:26:04 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_chunks_to_b(t_stack **stack_a, t_stack **stack_b, int chunks)
{
	int	size;
	int	chunk_size;
	int	chunk;
	int	min_idx;
	int	max_idx;

	chunk_size = size / chunks;
	if (chunk_size == 0)
		chunk_size = 1;
	chunk = 0;
	while (chunk < chunks - 1)
		min_idx = chunk * chunk_size;
		max_idx = (chunk + 1) * chunk_size - 1;
}
