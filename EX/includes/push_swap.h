/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
/*   Updated: 2026/01/15 01:45:26 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ========================================================================== */
/*                                  INCLUDES                                  */
/* ========================================================================== */

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft/libft.h"

/* ========================================================================== */
/*                                  MACROS                                    */
/* ========================================================================== */

// # define TRUE 1
// # define FALSE 0
// # define ERROR -1

/* ========================================================================== */
/*                                STRUCTURES                                  */
/* ========================================================================== */

/**
 * @brief Stack node structure
 *
 * @param value Original value from input
 * @param index Normalized index (0 to N-1)
 * @param pos Current position in stack
 * @param target_pos Target position for optimization
 * @param cost_a Cost to move in stack A
 * @param cost_b Cost to move in stack B
 * @param next Pointer to next node
 */
typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

/* ========================================================================== */
/*                            FUNCTION PROTOTYPES                             */
/* ========================================================================== */

/* -------------------------- Parsing & Validation -------------------------- */
char	**parse_arguments(int argc, char **argv);
t_stack	*init_stack_a(char **numbers);
int		is_valid_number(char *str);
long	ft_atol(const char *str);
int		is_int_range(long num);
int		has_duplicates(t_stack *stack);

/* ----------------------------- Stack Utils -------------------------------- */
t_stack	*stack_new(int value);
int		stack_size(t_stack *stack);
t_stack	*stack_last(t_stack *stack);
void	stack_add_back(t_stack **stack, t_stack *new);
void	stack_add_front(t_stack **stack, t_stack *new);

/* ------------------------- Stack Utils Advanced --------------------------- */
int		find_min(t_stack *stack);
int		find_max(t_stack *stack);
int		find_min_index(t_stack *stack);
int		find_max_index(t_stack *stack);
int		is_sorted(t_stack *stack);

/* ----------------------------- Position ----------------------------------- */
void	assign_position(t_stack *stack);

/* -------------------------- Index Normalization --------------------------- */
void	assign_index(t_stack *stack_a);

/* -------------------------- Swap Operations ------------------------------- */
void	sa(t_stack **stack_a, int print);
void	sb(t_stack **stack_b, int print);
void	ss(t_stack **stack_a, t_stack **stack_b, int print);

/* -------------------------- Push Operations ------------------------------- */
void	pa(t_stack **stack_a, t_stack **stack_b, int print);
void	pb(t_stack **stack_a, t_stack **stack_b, int print);

/* ------------------------- Rotate Operations ------------------------------ */
void	ra(t_stack **stack_a, int print);
void	rb(t_stack **stack_b, int print);
void	rr(t_stack **stack_a, t_stack **stack_b, int print);

/* --------------------- Reverse Rotate Operations -------------------------- */
void	rra(t_stack **stack_a, int print);
void	rrb(t_stack **stack_b, int print);
void	rrr(t_stack **stack_a, t_stack **stack_b, int print);

/* ---------------------------- Small Sorting ------------------------------- */
void	sort_small(t_stack **stack_a, t_stack **stack_b);
void	sort_two(t_stack **stack_a);
void	sort_three(t_stack **stack_a);
void	sort_four(t_stack **stack_a, t_stack **stack_b);
void	sort_five(t_stack **stack_a, t_stack **stack_b);

/* ---------------------------- Large Sorting ------------------------------- */
void	sort_large(t_stack **stack_a, t_stack **stack_b);
void	push_chunks_to_b(t_stack **stack_a, t_stack **stack_b, int size);
void	final_rotate(t_stack **stack_a);

/* -------------------------- Cost Calculation ------------------------------ */
void	calculate_cost(t_stack *stack_a, t_stack *stack_b);
int		find_target_position(t_stack *stack_a, int index_b);
int		calculate_move_cost(t_stack *stack, int target_pos);
t_stack	*find_cheapest(t_stack *stack_b);
void	execute_cheapest_move(t_stack **a, t_stack **b, t_stack *cheapest);

/* -------------------------- Error Handling -------------------------------- */
void	print_error(void);
void	error_exit(t_stack **stack_a, t_stack **stack_b);

/* ------------------------- Memory Management ------------------------------ */
void	free_stack(t_stack **stack);
void	free_split(char **split);

#endif
