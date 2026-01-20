/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap_test.c                            :+:      :+:    :+:   */
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
/*                              SA TESTS                                      */
/* ========================================================================== */

void	test_sa(void)
{
	t_stack	*stack_a;
	int		values_2[] = {1, 2};
	int		expected_2[] = {2, 1};
	int		values_3[] = {1, 2, 3};
	int		expected_3[] = {2, 1, 3};
	int		values_5[] = {5, 4, 3, 2, 1};
	int		expected_5[] = {4, 5, 3, 2, 1};

	ft_printf("\n===== SA (SWAP A) TESTS =====\n");

	/* Test 1: NULL stack_a pointer */
	sa(NULL, 0);
	print_test_result("NULL stack_a pointer: no crash", 1);

	/* Test 2: Empty stack (*stack_a is NULL) */
	stack_a = NULL;
	sa(&stack_a, 0);
	print_test_result("Empty stack: no crash", stack_a == NULL);

	/* Test 3: Single element stack (should not swap) */
	stack_a = stack_new(42);
	sa(&stack_a, 0);
	print_test_result("Single element: value unchanged",
		stack_a->value == 42);
	print_test_result("Single element: size unchanged",
		stack_size(stack_a) == 1);
	free_stack(&stack_a);

	/* Test 4: Two elements - basic swap */
	stack_a = create_test_stack(values_2, 2);
	sa(&stack_a, 0);
	print_test_result("Two elements: [1,2] -> [2,1]",
		verify_stack_values(stack_a, expected_2, 2));
	free_stack(&stack_a);

	/* Test 5: Three elements - only first two swap */
	stack_a = create_test_stack(values_3, 3);
	sa(&stack_a, 0);
	print_test_result("Three elements: [1,2,3] -> [2,1,3]",
		verify_stack_values(stack_a, expected_3, 3));
	free_stack(&stack_a);

	/* Test 6: Five elements - only first two swap */
	stack_a = create_test_stack(values_5, 5);
	sa(&stack_a, 0);
	print_test_result("Five elements: [5,4,3,2,1] -> [4,5,3,2,1]",
		verify_stack_values(stack_a, expected_5, 5));
	free_stack(&stack_a);

	/* Test 7: Double swap returns to original */
	stack_a = create_test_stack(values_3, 3);
	sa(&stack_a, 0);
	sa(&stack_a, 0);
	print_test_result("Double sa: returns to original",
		verify_stack_values(stack_a, values_3, 3));
	free_stack(&stack_a);

	/* Test 8: Size unchanged after swap */
	stack_a = create_test_stack(values_5, 5);
	sa(&stack_a, 0);
	print_test_result("Size unchanged after sa", stack_size(stack_a) == 5);
	free_stack(&stack_a);

	/* Test 9: Silent mode (print=0) - no output verification needed */
	stack_a = create_test_stack(values_2, 2);
	ft_printf("  (Silent mode test - should see no 'sa' output)\n");
	sa(&stack_a, 0);
	print_test_result("Silent mode: operation completed", 1);
	free_stack(&stack_a);

	/* Test 10: Print mode (print=1) */
	stack_a = create_test_stack(values_2, 2);
	ft_printf("  (Print mode test - should see 'sa' below)\n  ");
	sa(&stack_a, 1);
	print_test_result("Print mode: operation completed", 1);
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              SB TESTS                                      */
/* ========================================================================== */

void	test_sb(void)
{
	t_stack	*stack_b;
	int		values_2[] = {1, 2};
	int		expected_2[] = {2, 1};
	int		values_3[] = {10, 20, 30};
	int		expected_3[] = {20, 10, 30};

	ft_printf("\n===== SB (SWAP B) TESTS =====\n");

	/* Test 1: NULL stack_b pointer */
	sb(NULL, 0);
	print_test_result("NULL stack_b pointer: no crash", 1);

	/* Test 2: Empty stack */
	stack_b = NULL;
	sb(&stack_b, 0);
	print_test_result("Empty stack: no crash", stack_b == NULL);

	/* Test 3: Single element stack */
	stack_b = stack_new(42);
	sb(&stack_b, 0);
	print_test_result("Single element: value unchanged",
		stack_b->value == 42);
	free_stack(&stack_b);

	/* Test 4: Two elements - basic swap */
	stack_b = create_test_stack(values_2, 2);
	sb(&stack_b, 0);
	print_test_result("Two elements: [1,2] -> [2,1]",
		verify_stack_values(stack_b, expected_2, 2));
	free_stack(&stack_b);

	/* Test 5: Three elements */
	stack_b = create_test_stack(values_3, 3);
	sb(&stack_b, 0);
	print_test_result("Three elements: [10,20,30] -> [20,10,30]",
		verify_stack_values(stack_b, expected_3, 3));
	free_stack(&stack_b);

	/* Test 6: Double swap returns to original */
	stack_b = create_test_stack(values_3, 3);
	sb(&stack_b, 0);
	sb(&stack_b, 0);
	print_test_result("Double sb: returns to original",
		verify_stack_values(stack_b, values_3, 3));
	free_stack(&stack_b);

	/* Test 7: Print mode */
	stack_b = create_test_stack(values_2, 2);
	ft_printf("  (Print mode test - should see 'sb' below)\n  ");
	sb(&stack_b, 1);
	print_test_result("Print mode: operation completed", 1);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                              SS TESTS                                      */
/* ========================================================================== */

void	test_ss(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		a_values[] = {1, 2, 3};
	int		a_expected[] = {2, 1, 3};
	int		b_values[] = {10, 20, 30};
	int		b_expected[] = {20, 10, 30};

	ft_printf("\n===== SS (SWAP BOTH) TESTS =====\n");

	/* Test 1: Both NULL */
	ss(NULL, NULL, 0);
	print_test_result("Both NULL: no crash", 1);

	/* Test 2: Both empty */
	stack_a = NULL;
	stack_b = NULL;
	ss(&stack_a, &stack_b, 0);
	print_test_result("Both empty: no crash",
		stack_a == NULL && stack_b == NULL);

	/* Test 3: A empty, B has elements */
	stack_a = NULL;
	stack_b = create_test_stack(b_values, 3);
	ss(&stack_a, &stack_b, 0);
	print_test_result("A empty, B swaps: A unchanged", stack_a == NULL);
	print_test_result("A empty, B swaps: B swapped",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_b);

	/* Test 4: A has elements, B empty */
	stack_a = create_test_stack(a_values, 3);
	stack_b = NULL;
	ss(&stack_a, &stack_b, 0);
	print_test_result("A swaps, B empty: A swapped",
		verify_stack_values(stack_a, a_expected, 3));
	print_test_result("A swaps, B empty: B unchanged", stack_b == NULL);
	free_stack(&stack_a);

	/* Test 5: Both have elements */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	ss(&stack_a, &stack_b, 0);
	print_test_result("Both swap: A correct",
		verify_stack_values(stack_a, a_expected, 3));
	print_test_result("Both swap: B correct",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 6: A single element, B multiple */
	stack_a = stack_new(1);
	stack_b = create_test_stack(b_values, 3);
	ss(&stack_a, &stack_b, 0);
	print_test_result("A single (no swap): value unchanged",
		stack_a->value == 1);
	print_test_result("A single, B swaps: B swapped",
		verify_stack_values(stack_b, b_expected, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 7: Double ss returns to original */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	ss(&stack_a, &stack_b, 0);
	ss(&stack_a, &stack_b, 0);
	print_test_result("Double ss: A returns to original",
		verify_stack_values(stack_a, a_values, 3));
	print_test_result("Double ss: B returns to original",
		verify_stack_values(stack_b, b_values, 3));
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 8: Print mode */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	ft_printf("  (Print mode test - should see only 'ss', not 'sa sb')\n  ");
	ss(&stack_a, &stack_b, 1);
	print_test_result("Print mode: shows 'ss' (verify above)", 1);
	free_stack(&stack_a);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                           EDGE CASE TESTS                                  */
/* ========================================================================== */

void	test_swap_edge_cases(void)
{
	t_stack	*stack_a;
	int		int_limits[] = {INT_MIN, INT_MAX};
	int		expected_limits[] = {INT_MAX, INT_MIN};
	int		negatives[] = {-100, -50, -200};
	int		expected_neg[] = {-50, -100, -200};

	ft_printf("\n===== SWAP EDGE CASES =====\n");

	/* Test 1: INT_MIN and INT_MAX values */
	stack_a = create_test_stack(int_limits, 2);
	sa(&stack_a, 0);
	print_test_result("INT_MIN/INT_MAX swap correctly",
		verify_stack_values(stack_a, expected_limits, 2));
	free_stack(&stack_a);

	/* Test 2: Negative values */
	stack_a = create_test_stack(negatives, 3);
	sa(&stack_a, 0);
	print_test_result("Negative values swap correctly",
		verify_stack_values(stack_a, expected_neg, 3));
	free_stack(&stack_a);

	/* Test 3: Same values (swap identical elements) */
	int same_values[] = {42, 42, 42};
	stack_a = create_test_stack(same_values, 3);
	sa(&stack_a, 0);
	print_test_result("Identical values: swap works",
		verify_stack_values(stack_a, same_values, 3));
	free_stack(&stack_a);

	/* Test 4: Zero values */
	int zeros[] = {0, 0, 1};
	int expected_zeros[] = {0, 0, 1};
	stack_a = create_test_stack(zeros, 3);
	sa(&stack_a, 0);
	print_test_result("Zero values: swap works",
		verify_stack_values(stack_a, expected_zeros, 3));
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              MAIN                                          */
/* ========================================================================== */

int	main(void)
{
	ft_printf("========================================\n");
	ft_printf("   OPERATIONS_SWAP.C UNIT TESTS\n");
	ft_printf("========================================\n");

	test_sa();
	test_sb();
	test_ss();
	test_swap_edge_cases();

	print_test_summary("operations_swap.c");

	return (g_tests_failed > 0 ? 1 : 0);
}
