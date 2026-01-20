/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate_test.c                          :+:      :+:    :+:   */
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
/*                              RA TESTS                                      */
/* ========================================================================== */

void	test_ra(void)
{
	t_stack	*stack_a;
	int		values_2[] = {1, 2};
	int		expected_2[] = {2, 1};
	int		values_3[] = {1, 2, 3};
	int		expected_3[] = {2, 3, 1};
	int		values_5[] = {1, 2, 3, 4, 5};
	int		expected_5[] = {2, 3, 4, 5, 1};

	ft_printf("\n===== RA (ROTATE A) TESTS =====\n");

	/* Test 1: NULL stack_a pointer */
	ra(NULL, 0);
	print_test_result("NULL stack_a pointer: no crash", 1);

	/* Test 2: Empty stack */
	stack_a = NULL;
	ra(&stack_a, 0);
	print_test_result("Empty stack: no crash", stack_a == NULL);

	/* Test 3: Single element (no rotation needed) */
	stack_a = stack_new(42);
	ra(&stack_a, 0);
	print_test_result("Single element: value unchanged",
		stack_a->value == 42);
	print_test_result("Single element: size unchanged",
		stack_size(stack_a) == 1);
	free_stack(&stack_a);

	/* Test 4: Two elements - basic rotate */
	stack_a = create_test_stack(values_2, 2);
	ra(&stack_a, 0);
	print_test_result("Two elements: [1,2] -> [2,1]",
		verify_stack_values(stack_a, expected_2, 2));
	free_stack(&stack_a);

	/* Test 5: Three elements */
	stack_a = create_test_stack(values_3, 3);
	ra(&stack_a, 0);
	print_test_result("Three elements: [1,2,3] -> [2,3,1]",
		verify_stack_values(stack_a, expected_3, 3));
	free_stack(&stack_a);

	/* Test 6: Five elements */
	stack_a = create_test_stack(values_5, 5);
	ra(&stack_a, 0);
	print_test_result("Five elements: [1,2,3,4,5] -> [2,3,4,5,1]",
		verify_stack_values(stack_a, expected_5, 5));
	free_stack(&stack_a);

	/* Test 7: N rotations returns to original (N = size) */
	stack_a = create_test_stack(values_5, 5);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	ra(&stack_a, 0);
	print_test_result("5x ra (size=5): returns to original",
		verify_stack_values(stack_a, values_5, 5));
	free_stack(&stack_a);

	/* Test 8: Size unchanged after rotate */
	stack_a = create_test_stack(values_5, 5);
	ra(&stack_a, 0);
	print_test_result("Size unchanged after ra", stack_size(stack_a) == 5);
	free_stack(&stack_a);

	/* Test 9: First becomes last */
	stack_a = create_test_stack(values_5, 5);
	int first_value = stack_a->value;
	ra(&stack_a, 0);
	print_test_result("First becomes last",
		stack_last(stack_a)->value == first_value);
	free_stack(&stack_a);

	/* Test 10: Print mode */
	stack_a = create_test_stack(values_2, 2);
	ft_printf("  (Print mode test - should see 'ra' below)\n  ");
	ra(&stack_a, 1);
	print_test_result("Print mode: completed", 1);
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              RB TESTS                                      */
/* ========================================================================== */

void	test_rb(void)
{
	t_stack	*stack_b;
	int		values_2[] = {10, 20};
	int		expected_2[] = {20, 10};
	int		values_3[] = {10, 20, 30};
	int		expected_3[] = {20, 30, 10};

	ft_printf("\n===== RB (ROTATE B) TESTS =====\n");

	/* Test 1: NULL stack_b pointer */
	rb(NULL, 0);
	print_test_result("NULL stack_b pointer: no crash", 1);

	/* Test 2: Empty stack */
	stack_b = NULL;
	rb(&stack_b, 0);
	print_test_result("Empty stack: no crash", stack_b == NULL);

	/* Test 3: Single element */
	stack_b = stack_new(42);
	rb(&stack_b, 0);
	print_test_result("Single element: unchanged", stack_b->value == 42);
	free_stack(&stack_b);

	/* Test 4: Two elements */
	stack_b = create_test_stack(values_2, 2);
	rb(&stack_b, 0);
	print_test_result("Two elements: [10,20] -> [20,10]",
		verify_stack_values(stack_b, expected_2, 2));
	free_stack(&stack_b);

	/* Test 5: Three elements */
	stack_b = create_test_stack(values_3, 3);
	rb(&stack_b, 0);
	print_test_result("Three elements: [10,20,30] -> [20,30,10]",
		verify_stack_values(stack_b, expected_3, 3));
	free_stack(&stack_b);

	/* Test 6: Double rb */
	stack_b = create_test_stack(values_3, 3);
	rb(&stack_b, 0);
	rb(&stack_b, 0);
	int expected_double[] = {30, 10, 20};
	print_test_result("Double rb: [10,20,30] -> [30,10,20]",
		verify_stack_values(stack_b, expected_double, 3));
	free_stack(&stack_b);

	/* Test 7: Print mode */
	stack_b = create_test_stack(values_2, 2);
	ft_printf("  (Print mode test - should see 'rb' below)\n  ");
	rb(&stack_b, 1);
	print_test_result("Print mode: completed", 1);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                              RR TESTS                                      */
/* ========================================================================== */

void	test_rr(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		a_values[] = {1, 2, 3};
	int		a_expected[] = {2, 3, 1};
	int		b_values[] = {10, 20, 30};
	int		b_expected[] = {20, 30, 10};

	ft_printf("\n===== RR (ROTATE BOTH) TESTS =====\n");

	/* Test 1: Both NULL */
	rr(NULL, NULL, 0);
	print_test_result("Both NULL: no crash", 1);

	/* Test 2: Both empty */
	stack_a = NULL;
	stack_b = NULL;
	rr(&stack_a, &stack_b, 0);
	print_test_result("Both empty: no crash",
		stack_a == NULL && stack_b == NULL);

	/* Test 3: A empty, B has elements */
	stack_a = NULL;
	stack_b = create_test_stack(b_values, 3);
	rr(&stack_a, &stack_b, 0);
	print_test_result("A empty: A unchanged", stack_a == NULL);
	print_test_result("A empty: B rotates",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_b);

	/* Test 4: A has elements, B empty */
	stack_a = create_test_stack(a_values, 3);
	stack_b = NULL;
	rr(&stack_a, &stack_b, 0);
	print_test_result("B empty: A rotates",
		verify_stack_values(stack_a, a_expected, 3));
	print_test_result("B empty: B unchanged", stack_b == NULL);
	free_stack(&stack_a);

	/* Test 5: Both have elements */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	rr(&stack_a, &stack_b, 0);
	print_test_result("Both rotate: A correct",
		verify_stack_values(stack_a, a_expected, 3));
	print_test_result("Both rotate: B correct",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 6: A single element, B multiple */
	stack_a = stack_new(1);
	stack_b = create_test_stack(b_values, 3);
	rr(&stack_a, &stack_b, 0);
	print_test_result("A single: unchanged", stack_a->value == 1);
	print_test_result("A single: B rotates",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 7: N rotations returns both to original */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	rr(&stack_a, &stack_b, 0);
	rr(&stack_a, &stack_b, 0);
	rr(&stack_a, &stack_b, 0);
	print_test_result("3x rr: A returns to original",
		verify_stack_values(stack_a, a_values, 3));
	print_test_result("3x rr: B returns to original",
		verify_stack_values(stack_b, b_values, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 8: Print mode */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	ft_printf("  (Print mode - should see only 'rr', not 'ra rb')\n  ");
	rr(&stack_a, &stack_b, 1);
	print_test_result("Print mode: shows 'rr'", 1);
	free_stack(&stack_a);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                           EDGE CASE TESTS                                  */
/* ========================================================================== */

void	test_rotate_edge_cases(void)
{
	t_stack	*stack_a;
	int		int_limits[] = {INT_MIN, INT_MAX};
	int		expected_limits[] = {INT_MAX, INT_MIN};
	int		negatives[] = {-100, -50, -200};
	int		expected_neg[] = {-50, -200, -100};

	ft_printf("\n===== ROTATE EDGE CASES =====\n");

	/* Test 1: INT_MIN and INT_MAX values */
	stack_a = create_test_stack(int_limits, 2);
	ra(&stack_a, 0);
	print_test_result("INT_MIN/INT_MAX rotate correctly",
		verify_stack_values(stack_a, expected_limits, 2));
	free_stack(&stack_a);

	/* Test 2: Negative values */
	stack_a = create_test_stack(negatives, 3);
	ra(&stack_a, 0);
	print_test_result("Negative values rotate correctly",
		verify_stack_values(stack_a, expected_neg, 3));
	free_stack(&stack_a);

	/* Test 3: Same values */
	int same_values[] = {42, 42, 42};
	stack_a = create_test_stack(same_values, 3);
	ra(&stack_a, 0);
	print_test_result("Identical values: rotate works",
		verify_stack_values(stack_a, same_values, 3));
	free_stack(&stack_a);

	/* Test 4: Large rotation count */
	int values_5[] = {1, 2, 3, 4, 5};
	stack_a = create_test_stack(values_5, 5);
	int i = 0;
	while (i < 100)
	{
		ra(&stack_a, 0);
		i++;
	}
	/* 100 % 5 = 0, so back to original */
	print_test_result("100 rotations (mod 5 = 0): back to original",
		verify_stack_values(stack_a, values_5, 5));
	free_stack(&stack_a);

	/* Test 5: Two elements - ra acts like swap */
	int two[] = {1, 2};
	int two_exp[] = {2, 1};
	stack_a = create_test_stack(two, 2);
	ra(&stack_a, 0);
	print_test_result("Two elements: ra = swap effect",
		verify_stack_values(stack_a, two_exp, 2));
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              MAIN                                          */
/* ========================================================================== */

int	main(void)
{
	ft_printf("========================================\n");
	ft_printf("  OPERATIONS_ROTATE.C UNIT TESTS\n");
	ft_printf("========================================\n");

	test_ra();
	test_rb();
	test_rr();
	test_rotate_edge_cases();

	print_test_summary("operations_rotate.c");

	return (g_tests_failed > 0 ? 1 : 0);
}
