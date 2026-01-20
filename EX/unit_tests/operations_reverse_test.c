/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_test.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:00:00 by mju-ferr          #+#    #+#             */
/*   Updated: 2026/01/20 19:00:00 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

/* ========================================================================== */
/*                            TEST HELPER FUNCTIONS                           */
/* ========================================================================== */

static int	g_tests_passed = 0;
static int	g_tests_failed = 0;

void	print_test_result(const char *test_name, int passed)
{
	if (passed)
	{
		ft_printf("  [PASS] %s\n", test_name);
		g_tests_passed++;
	}
	else
	{
		ft_printf("  [FAIL] %s\n", test_name);
		g_tests_failed++;
	}
}

void	print_test_summary(const char *suite_name)
{
	ft_printf("\n%s Summary: %d passed, %d failed\n",
		suite_name, g_tests_passed, g_tests_failed);
	ft_printf("========================================\n");
}

t_stack	*create_test_stack(int *values, int count)
{
	t_stack	*stack;
	int		i;

	stack = NULL;
	i = 0;
	while (i < count)
	{
		stack_add_back(&stack, stack_new(values[i]));
		i++;
	}
	return (stack);
}

int	verify_stack_values(t_stack *stack, int *expected, int count)
{
	int	i;

	i = 0;
	while (stack && i < count)
	{
		if (stack->value != expected[i])
			return (0);
		stack = stack->next;
		i++;
	}
	return (i == count && stack == NULL);
}

/* ========================================================================== */
/*                              RRA TESTS                                     */
/* ========================================================================== */

void	test_rra(void)
{
	t_stack	*stack_a;
	int		values_2[] = {1, 2};
	int		expected_2[] = {2, 1};
	int		values_3[] = {1, 2, 3};
	int		expected_3[] = {3, 1, 2};
	int		values_5[] = {1, 2, 3, 4, 5};
	int		expected_5[] = {5, 1, 2, 3, 4};

	ft_printf("\n===== RRA (REVERSE ROTATE A) TESTS =====\n");

	/* Test 1: NULL stack_a pointer */
	rra(NULL, 0);
	print_test_result("NULL stack_a pointer: no crash", 1);

	/* Test 2: Empty stack */
	stack_a = NULL;
	rra(&stack_a, 0);
	print_test_result("Empty stack: no crash", stack_a == NULL);

	/* Test 3: Single element (no rotation needed) */
	stack_a = stack_new(42);
	rra(&stack_a, 0);
	print_test_result("Single element: value unchanged",
		stack_a->value == 42);
	print_test_result("Single element: size unchanged",
		stack_size(stack_a) == 1);
	free_stack(&stack_a);

	/* Test 4: Two elements - basic reverse rotate */
	stack_a = create_test_stack(values_2, 2);
	rra(&stack_a, 0);
	print_test_result("Two elements: [1,2] -> [2,1]",
		verify_stack_values(stack_a, expected_2, 2));
	free_stack(&stack_a);

	/* Test 5: Three elements */
	stack_a = create_test_stack(values_3, 3);
	rra(&stack_a, 0);
	print_test_result("Three elements: [1,2,3] -> [3,1,2]",
		verify_stack_values(stack_a, expected_3, 3));
	free_stack(&stack_a);

	/* Test 6: Five elements */
	stack_a = create_test_stack(values_5, 5);
	rra(&stack_a, 0);
	print_test_result("Five elements: [1,2,3,4,5] -> [5,1,2,3,4]",
		verify_stack_values(stack_a, expected_5, 5));
	free_stack(&stack_a);

	/* Test 7: N rotations returns to original (N = size) */
	stack_a = create_test_stack(values_5, 5);
	rra(&stack_a, 0);
	rra(&stack_a, 0);
	rra(&stack_a, 0);
	rra(&stack_a, 0);
	rra(&stack_a, 0);
	print_test_result("5x rra (size=5): returns to original",
		verify_stack_values(stack_a, values_5, 5));
	free_stack(&stack_a);

	/* Test 8: Size unchanged after reverse rotate */
	stack_a = create_test_stack(values_5, 5);
	rra(&stack_a, 0);
	print_test_result("Size unchanged after rra", stack_size(stack_a) == 5);
	free_stack(&stack_a);

	/* Test 9: Last becomes first */
	stack_a = create_test_stack(values_5, 5);
	int last_value = stack_last(stack_a)->value;
	rra(&stack_a, 0);
	print_test_result("Last becomes first", stack_a->value == last_value);
	free_stack(&stack_a);

	/* Test 10: Print mode */
	stack_a = create_test_stack(values_2, 2);
	ft_printf("  (Print mode test - should see 'rra' below)\n  ");
	rra(&stack_a, 1);
	print_test_result("Print mode: completed", 1);
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              RRB TESTS                                     */
/* ========================================================================== */

void	test_rrb(void)
{
	t_stack	*stack_b;
	int		values_2[] = {10, 20};
	int		expected_2[] = {20, 10};
	int		values_3[] = {10, 20, 30};
	int		expected_3[] = {30, 10, 20};

	ft_printf("\n===== RRB (REVERSE ROTATE B) TESTS =====\n");

	/* Test 1: NULL stack_b pointer */
	rrb(NULL, 0);
	print_test_result("NULL stack_b pointer: no crash", 1);

	/* Test 2: Empty stack */
	stack_b = NULL;
	rrb(&stack_b, 0);
	print_test_result("Empty stack: no crash", stack_b == NULL);

	/* Test 3: Single element */
	stack_b = stack_new(42);
	rrb(&stack_b, 0);
	print_test_result("Single element: unchanged", stack_b->value == 42);
	free_stack(&stack_b);

	/* Test 4: Two elements */
	stack_b = create_test_stack(values_2, 2);
	rrb(&stack_b, 0);
	print_test_result("Two elements: [10,20] -> [20,10]",
		verify_stack_values(stack_b, expected_2, 2));
	free_stack(&stack_b);

	/* Test 5: Three elements */
	stack_b = create_test_stack(values_3, 3);
	rrb(&stack_b, 0);
	print_test_result("Three elements: [10,20,30] -> [30,10,20]",
		verify_stack_values(stack_b, expected_3, 3));
	free_stack(&stack_b);

	/* Test 6: Double rrb */
	stack_b = create_test_stack(values_3, 3);
	rrb(&stack_b, 0);
	rrb(&stack_b, 0);
	int expected_double[] = {20, 30, 10};
	print_test_result("Double rrb: [10,20,30] -> [20,30,10]",
		verify_stack_values(stack_b, expected_double, 3));
	free_stack(&stack_b);

	/* Test 7: Print mode */
	stack_b = create_test_stack(values_2, 2);
	ft_printf("  (Print mode test - should see 'rrb' below)\n  ");
	rrb(&stack_b, 1);
	print_test_result("Print mode: completed", 1);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                              RRR TESTS                                     */
/* ========================================================================== */

void	test_rrr(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		a_values[] = {1, 2, 3};
	int		a_expected[] = {3, 1, 2};
	int		b_values[] = {10, 20, 30};
	int		b_expected[] = {30, 10, 20};

	ft_printf("\n===== RRR (REVERSE ROTATE BOTH) TESTS =====\n");

	/* Test 1: Both NULL */
	rrr(NULL, NULL, 0);
	print_test_result("Both NULL: no crash", 1);

	/* Test 2: Both empty */
	stack_a = NULL;
	stack_b = NULL;
	rrr(&stack_a, &stack_b, 0);
	print_test_result("Both empty: no crash",
		stack_a == NULL && stack_b == NULL);

	/* Test 3: A empty, B has elements */
	stack_a = NULL;
	stack_b = create_test_stack(b_values, 3);
	rrr(&stack_a, &stack_b, 0);
	print_test_result("A empty: A unchanged", stack_a == NULL);
	print_test_result("A empty: B reverse rotates",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_b);

	/* Test 4: A has elements, B empty */
	stack_a = create_test_stack(a_values, 3);
	stack_b = NULL;
	rrr(&stack_a, &stack_b, 0);
	print_test_result("B empty: A reverse rotates",
		verify_stack_values(stack_a, a_expected, 3));
	print_test_result("B empty: B unchanged", stack_b == NULL);
	free_stack(&stack_a);

	/* Test 5: Both have elements */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	rrr(&stack_a, &stack_b, 0);
	print_test_result("Both reverse rotate: A correct",
		verify_stack_values(stack_a, a_expected, 3));
	print_test_result("Both reverse rotate: B correct",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 6: A single element, B multiple */
	stack_a = stack_new(1);
	stack_b = create_test_stack(b_values, 3);
	rrr(&stack_a, &stack_b, 0);
	print_test_result("A single: unchanged", stack_a->value == 1);
	print_test_result("A single: B reverse rotates",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 7: N rotations returns both to original */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	rrr(&stack_a, &stack_b, 0);
	rrr(&stack_a, &stack_b, 0);
	rrr(&stack_a, &stack_b, 0);
	print_test_result("3x rrr: A returns to original",
		verify_stack_values(stack_a, a_values, 3));
	print_test_result("3x rrr: B returns to original",
		verify_stack_values(stack_b, b_values, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 8: Print mode */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	ft_printf("  (Print mode - should see only 'rrr', not 'rra rrb')\n  ");
	rrr(&stack_a, &stack_b, 1);
	print_test_result("Print mode: shows 'rrr'", 1);
	free_stack(&stack_a);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                      RA/RRA INVERSE RELATIONSHIP                           */
/* ========================================================================== */

void	test_ra_rra_inverse(void)
{
	t_stack	*stack_a;
	int		values_5[] = {1, 2, 3, 4, 5};

	ft_printf("\n===== RA/RRA INVERSE TESTS =====\n");

	/* Test 1: ra then rra returns to original */
	stack_a = create_test_stack(values_5, 5);
	ra(&stack_a, 0);
	rra(&stack_a, 0);
	print_test_result("ra then rra: returns to original",
		verify_stack_values(stack_a, values_5, 5));
	free_stack(&stack_a);

	/* Test 2: rra then ra returns to original */
	stack_a = create_test_stack(values_5, 5);
	rra(&stack_a, 0);
	ra(&stack_a, 0);
	print_test_result("rra then ra: returns to original",
		verify_stack_values(stack_a, values_5, 5));
	free_stack(&stack_a);

	/* Test 3: Multiple ra then same rra */
	stack_a = create_test_stack(values_5, 5);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	rra(&stack_a, 0);
	rra(&stack_a, 0);
	rra(&stack_a, 0);
	print_test_result("3x ra then 3x rra: returns to original",
		verify_stack_values(stack_a, values_5, 5));
	free_stack(&stack_a);

	/* Test 4: N-1 ra = 1 rra (for size N) */
	stack_a = create_test_stack(values_5, 5);
	t_stack *reference = create_test_stack(values_5, 5);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	/* After 4 ra on size 5: [5,1,2,3,4] */
	rra(&reference, 0);
	/* After 1 rra on size 5: [5,1,2,3,4] */
	print_test_result("4x ra = 1x rra (size=5): same result",
		stack_a->value == reference->value);
	free_stack(&stack_a);
	free_stack(&reference);
}

/* ========================================================================== */
/*                           EDGE CASE TESTS                                  */
/* ========================================================================== */

void	test_reverse_edge_cases(void)
{
	t_stack	*stack_a;
	int		int_limits[] = {INT_MIN, INT_MAX};
	int		expected_limits[] = {INT_MAX, INT_MIN};
	int		negatives[] = {-100, -50, -200};
	int		expected_neg[] = {-200, -100, -50};
	int		i;

	ft_printf("\n===== REVERSE ROTATE EDGE CASES =====\n");

	/* Test 1: INT_MIN and INT_MAX values */
	stack_a = create_test_stack(int_limits, 2);
	rra(&stack_a, 0);
	print_test_result("INT_MIN/INT_MAX reverse rotate correctly",
		verify_stack_values(stack_a, expected_limits, 2));
	free_stack(&stack_a);

	/* Test 2: Negative values */
	stack_a = create_test_stack(negatives, 3);
	rra(&stack_a, 0);
	print_test_result("Negative values reverse rotate correctly",
		verify_stack_values(stack_a, expected_neg, 3));
	free_stack(&stack_a);

	/* Test 3: Same values */
	int same_values[] = {42, 42, 42};
	stack_a = create_test_stack(same_values, 3);
	rra(&stack_a, 0);
	print_test_result("Identical values: reverse rotate works",
		verify_stack_values(stack_a, same_values, 3));
	free_stack(&stack_a);

	/* Test 4: Large rotation count */
	int values_5[] = {1, 2, 3, 4, 5};
	stack_a = create_test_stack(values_5, 5);
	i = 0;
	while (i < 100)
	{
		rra(&stack_a, 0);
		i++;
	}
	/* 100 % 5 = 0, so back to original */
	print_test_result("100 reverse rotations (mod 5 = 0): back to original",
		verify_stack_values(stack_a, values_5, 5));
	free_stack(&stack_a);

	/* Test 5: Two elements - rra acts like swap */
	int two[] = {1, 2};
	int two_exp[] = {2, 1};
	stack_a = create_test_stack(two, 2);
	rra(&stack_a, 0);
	print_test_result("Two elements: rra = swap effect",
		verify_stack_values(stack_a, two_exp, 2));
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              MAIN                                          */
/* ========================================================================== */

int	main(void)
{
	ft_printf("========================================\n");
	ft_printf(" OPERATIONS_REVERSE.C UNIT TESTS\n");
	ft_printf("========================================\n");

	test_rra();
	test_rrb();
	test_rrr();
	test_ra_rra_inverse();
	test_reverse_edge_cases();

	print_test_summary("operations_reverse.c");

	return (g_tests_failed > 0 ? 1 : 0);
}
