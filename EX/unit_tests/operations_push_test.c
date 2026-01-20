/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push_test.c                            :+:      :+:    :+:   */
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
/*                              PA TESTS                                      */
/* ========================================================================== */

void	test_pa(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		a_values[] = {1, 2, 3};
	int		b_values[] = {10, 20, 30};
	int		expected_a[] = {10, 1, 2, 3};
	int		expected_b[] = {20, 30};

	ft_printf("\n===== PA (PUSH A) TESTS =====\n");

	/* Test 1: NULL stack_a pointer */
	stack_b = stack_new(1);
	pa(NULL, &stack_b, 0);
	print_test_result("NULL stack_a: no crash", 1);
	free_stack(&stack_b);

	/* Test 2: NULL stack_b pointer */
	stack_a = stack_new(1);
	pa(&stack_a, NULL, 0);
	print_test_result("NULL stack_b: no crash", 1);
	free_stack(&stack_a);

	/* Test 3: Both NULL */
	pa(NULL, NULL, 0);
	print_test_result("Both NULL: no crash", 1);

	/* Test 4: Empty B (nothing to push) */
	stack_a = create_test_stack(a_values, 3);
	stack_b = NULL;
	pa(&stack_a, &stack_b, 0);
	print_test_result("Empty B: A unchanged",
		verify_stack_values(stack_a, a_values, 3));
	print_test_result("Empty B: B still NULL", stack_b == NULL);
	free_stack(&stack_a);

	/* Test 5: Basic push - B has elements, A has elements */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Basic pa: A receives element",
		verify_stack_values(stack_a, expected_a, 4));
	print_test_result("Basic pa: B loses element",
		verify_stack_values(stack_b, expected_b, 2));
	print_test_result("Basic pa: A size is 4", stack_size(stack_a) == 4);
	print_test_result("Basic pa: B size is 2", stack_size(stack_b) == 2);
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 6: Push to empty A */
	stack_a = NULL;
	stack_b = create_test_stack(b_values, 3);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Push to empty A: A has element",
		stack_a != NULL && stack_a->value == 10);
	print_test_result("Push to empty A: A size is 1", stack_size(stack_a) == 1);
	print_test_result("Push to empty A: B size is 2", stack_size(stack_b) == 2);
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 7: Push all from B to A */
	stack_a = NULL;
	stack_b = create_test_stack(b_values, 3);
	pa(&stack_a, &stack_b, 0);
	pa(&stack_a, &stack_b, 0);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Push all: B is empty", stack_b == NULL);
	print_test_result("Push all: A size is 3", stack_size(stack_a) == 3);
	/* Order is reversed: [30, 20, 10] */
	print_test_result("Push all: first is 30", stack_a->value == 30);
	print_test_result("Push all: last is 10", stack_last(stack_a)->value == 10);
	free_stack(&stack_a);

	/* Test 8: Single element in B */
	stack_a = create_test_stack(a_values, 3);
	stack_b = stack_new(99);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Single B: A first is 99", stack_a->value == 99);
	print_test_result("Single B: B is NULL", stack_b == NULL);
	free_stack(&stack_a);

	/* Test 9: Print mode */
	stack_a = NULL;
	stack_b = stack_new(42);
	ft_printf("  (Print mode test - should see 'pa' below)\n  ");
	pa(&stack_a, &stack_b, 1);
	print_test_result("Print mode: completed", 1);
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              PB TESTS                                      */
/* ========================================================================== */

void	test_pb(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		a_values[] = {1, 2, 3};
	int		b_values[] = {10, 20, 30};
	int		expected_a[] = {2, 3};
	int		expected_b[] = {1, 10, 20, 30};

	ft_printf("\n===== PB (PUSH B) TESTS =====\n");

	/* Test 1: NULL stack_a pointer */
	stack_b = stack_new(1);
	pb(NULL, &stack_b, 0);
	print_test_result("NULL stack_a: no crash", 1);
	free_stack(&stack_b);

	/* Test 2: NULL stack_b pointer */
	stack_a = stack_new(1);
	pb(&stack_a, NULL, 0);
	print_test_result("NULL stack_b: no crash", 1);
	free_stack(&stack_a);

	/* Test 3: Both NULL */
	pb(NULL, NULL, 0);
	print_test_result("Both NULL: no crash", 1);

	/* Test 4: Empty A (nothing to push) */
	stack_a = NULL;
	stack_b = create_test_stack(b_values, 3);
	pb(&stack_a, &stack_b, 0);
	print_test_result("Empty A: B unchanged",
		verify_stack_values(stack_b, b_values, 3));
	print_test_result("Empty A: A still NULL", stack_a == NULL);
	free_stack(&stack_b);

	/* Test 5: Basic push - A has elements, B has elements */
	stack_a = create_test_stack(a_values, 3);
	stack_b = create_test_stack(b_values, 3);
	pb(&stack_a, &stack_b, 0);
	print_test_result("Basic pb: A loses element",
		verify_stack_values(stack_a, expected_a, 2));
	print_test_result("Basic pb: B receives element",
		verify_stack_values(stack_b, expected_b, 4));
	print_test_result("Basic pb: A size is 2", stack_size(stack_a) == 2);
	print_test_result("Basic pb: B size is 4", stack_size(stack_b) == 4);
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 6: Push to empty B */
	stack_a = create_test_stack(a_values, 3);
	stack_b = NULL;
	pb(&stack_a, &stack_b, 0);
	print_test_result("Push to empty B: B has element",
		stack_b != NULL && stack_b->value == 1);
	print_test_result("Push to empty B: B size is 1", stack_size(stack_b) == 1);
	print_test_result("Push to empty B: A size is 2", stack_size(stack_a) == 2);
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 7: Push all from A to B */
	stack_a = create_test_stack(a_values, 3);
	stack_b = NULL;
	pb(&stack_a, &stack_b, 0);
	pb(&stack_a, &stack_b, 0);
	pb(&stack_a, &stack_b, 0);
	print_test_result("Push all: A is empty", stack_a == NULL);
	print_test_result("Push all: B size is 3", stack_size(stack_b) == 3);
	/* Order is reversed: [3, 2, 1] */
	print_test_result("Push all: first is 3", stack_b->value == 3);
	print_test_result("Push all: last is 1", stack_last(stack_b)->value == 1);
	free_stack(&stack_b);

	/* Test 8: Single element in A */
	stack_a = stack_new(99);
	stack_b = create_test_stack(b_values, 3);
	pb(&stack_a, &stack_b, 0);
	print_test_result("Single A: B first is 99", stack_b->value == 99);
	print_test_result("Single A: A is NULL", stack_a == NULL);
	free_stack(&stack_b);

	/* Test 9: Print mode */
	stack_a = stack_new(42);
	stack_b = NULL;
	ft_printf("  (Print mode test - should see 'pb' below)\n  ");
	pb(&stack_a, &stack_b, 1);
	print_test_result("Print mode: completed", 1);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                         PA + PB COMBINED TESTS                             */
/* ========================================================================== */

void	test_pa_pb_combined(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		a_values[] = {1, 2, 3, 4, 5};

	ft_printf("\n===== PA + PB COMBINED TESTS =====\n");

	/* Test 1: pb then pa returns element */
	stack_a = create_test_stack(a_values, 5);
	stack_b = NULL;
	pb(&stack_a, &stack_b, 0);
	pa(&stack_a, &stack_b, 0);
	print_test_result("pb then pa: A back to original",
		verify_stack_values(stack_a, a_values, 5));
	print_test_result("pb then pa: B is empty", stack_b == NULL);
	free_stack(&stack_a);

	/* Test 2: Multiple pb then pa */
	stack_a = create_test_stack(a_values, 5);
	stack_b = NULL;
	pb(&stack_a, &stack_b, 0);
	pb(&stack_a, &stack_b, 0);
	pb(&stack_a, &stack_b, 0);
	/* A: [4, 5], B: [3, 2, 1] */
	pa(&stack_a, &stack_b, 0);
	pa(&stack_a, &stack_b, 0);
	pa(&stack_a, &stack_b, 0);
	/* A: [1, 2, 3, 4, 5], B: [] */
	print_test_result("3xpb then 3xpa: A back to original",
		verify_stack_values(stack_a, a_values, 5));
	print_test_result("3xpb then 3xpa: B is empty", stack_b == NULL);
	free_stack(&stack_a);

	/* Test 3: Interleaved pb and pa */
	stack_a = create_test_stack(a_values, 5);
	stack_b = NULL;
	pb(&stack_a, &stack_b, 0);
	/* A: [2,3,4,5], B: [1] */
	pb(&stack_a, &stack_b, 0);
	/* A: [3,4,5], B: [2,1] */
	pa(&stack_a, &stack_b, 0);
	/* A: [2,3,4,5], B: [1] */
	print_test_result("Interleaved: A first is 2", stack_a->value == 2);
	print_test_result("Interleaved: A size is 4", stack_size(stack_a) == 4);
	print_test_result("Interleaved: B first is 1", stack_b->value == 1);
	print_test_result("Interleaved: B size is 1", stack_size(stack_b) == 1);
	free_stack(&stack_a);
	free_stack(&stack_b);
}

/* ========================================================================== */
/*                           EDGE CASE TESTS                                  */
/* ========================================================================== */

void	test_push_edge_cases(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		int_limits[] = {INT_MIN, INT_MAX};

	ft_printf("\n===== PUSH EDGE CASES =====\n");

	/* Test 1: Push INT_MIN value */
	stack_a = NULL;
	stack_b = stack_new(INT_MIN);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Push INT_MIN: A has INT_MIN",
		stack_a->value == INT_MIN);
	free_stack(&stack_a);

	/* Test 2: Push INT_MAX value */
	stack_a = NULL;
	stack_b = stack_new(INT_MAX);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Push INT_MAX: A has INT_MAX",
		stack_a->value == INT_MAX);
	free_stack(&stack_a);

	/* Test 3: Push between INT_MIN and INT_MAX */
	stack_a = create_test_stack(int_limits, 2);
	stack_b = NULL;
	pb(&stack_a, &stack_b, 0);
	print_test_result("Push INT_MIN from A: B has INT_MIN",
		stack_b->value == INT_MIN);
	print_test_result("Push INT_MIN from A: A has INT_MAX",
		stack_a->value == INT_MAX);
	free_stack(&stack_a);
	free_stack(&stack_b);

	/* Test 4: Push zero value */
	stack_a = NULL;
	stack_b = stack_new(0);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Push zero: A has 0", stack_a->value == 0);
	free_stack(&stack_a);

	/* Test 5: Push negative value */
	stack_a = NULL;
	stack_b = stack_new(-42);
	pa(&stack_a, &stack_b, 0);
	print_test_result("Push negative: A has -42", stack_a->value == -42);
	free_stack(&stack_a);
}

/* ========================================================================== */
/*                              MAIN                                          */
/* ========================================================================== */

int	main(void)
{
	ft_printf("========================================\n");
	ft_printf("   OPERATIONS_PUSH.C UNIT TESTS\n");
	ft_printf("========================================\n");

	test_pa();
	test_pb();
	test_pa_pb_combined();
	test_push_edge_cases();

	print_test_summary("operations_push.c");

	return (g_tests_failed > 0 ? 1 : 0);
}
