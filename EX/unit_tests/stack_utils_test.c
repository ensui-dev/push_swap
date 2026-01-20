/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by ensui             #+#    #+#             */
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

/* Helper to create a stack from an array of values */
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

/* Helper to verify stack values match expected array */
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
/*                          STACK_NEW TESTS                                   */
/* ========================================================================== */

void	test_stack_new(void)
{
	t_stack	*node;

	ft_printf("\n===== STACK_NEW TESTS =====\n");

	/* Test 1: Create node with positive value */
	node = stack_new(42);
	print_test_result("Create node with value 42",
		node != NULL && node->value == 42);
	free(node);

	/* Test 2: Create node with negative value */
	node = stack_new(-100);
	print_test_result("Create node with value -100",
		node != NULL && node->value == -100);
	free(node);

	/* Test 3: Create node with zero */
	node = stack_new(0);
	print_test_result("Create node with value 0",
		node != NULL && node->value == 0);
	free(node);

	/* Test 4: Verify default field initialization */
	node = stack_new(42);
	print_test_result("Index initialized to -1", node->index == -1);
	print_test_result("Position initialized to 0", node->pos == 0);
	print_test_result("Target_pos initialized to 0", node->target_pos == 0);
	print_test_result("Cost_a initialized to 0", node->cost_a == 0);
	print_test_result("Cost_b initialized to 0", node->cost_b == 0);
	print_test_result("Next pointer is NULL", node->next == NULL);
	free(node);

	/* Test 5: INT_MAX edge case */
	node = stack_new(INT_MAX);
	print_test_result("Create node with INT_MAX",
		node != NULL && node->value == INT_MAX);
	free(node);

	/* Test 6: INT_MIN edge case */
	node = stack_new(INT_MIN);
	print_test_result("Create node with INT_MIN",
		node != NULL && node->value == INT_MIN);
	free(node);
}

/* ========================================================================== */
/*                          STACK_SIZE TESTS                                  */
/* ========================================================================== */

void	test_stack_size(void)
{
	t_stack	*stack;
	int		values[] = {1, 2, 3, 4, 5};
	int		i;

	ft_printf("\n===== STACK_SIZE TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack returns 0", stack_size(NULL) == 0);

	/* Test 2: Single element */
	stack = stack_new(42);
	print_test_result("Single element returns 1", stack_size(stack) == 1);
	free(stack);

	/* Test 3: Two elements */
	stack = create_test_stack(values, 2);
	print_test_result("Two elements returns 2", stack_size(stack) == 2);
	free_stack(&stack);

	/* Test 4: Five elements */
	stack = create_test_stack(values, 5);
	print_test_result("Five elements returns 5", stack_size(stack) == 5);
	free_stack(&stack);

	/* Test 5: Large stack (100 elements) */
	stack = NULL;
	i = 0;
	while (i < 100)
	{
		stack_add_back(&stack, stack_new(i));
		i++;
	}
	print_test_result("100 elements returns 100", stack_size(stack) == 100);
	free_stack(&stack);
}

/* ========================================================================== */
/*                          STACK_LAST TESTS                                  */
/* ========================================================================== */

void	test_stack_last(void)
{
	t_stack	*stack;
	t_stack	*last;
	int		values[] = {1, 2, 3, 4, 5};

	ft_printf("\n===== STACK_LAST TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack returns NULL", stack_last(NULL) == NULL);

	/* Test 2: Single element (last is itself) */
	stack = stack_new(42);
	last = stack_last(stack);
	print_test_result("Single element: last is itself",
		last == stack && last->value == 42);
	free(stack);

	/* Test 3: Two elements */
	stack = create_test_stack(values, 2);
	last = stack_last(stack);
	print_test_result("Two elements: last value is 2", last->value == 2);
	print_test_result("Two elements: last->next is NULL", last->next == NULL);
	free_stack(&stack);

	/* Test 4: Five elements */
	stack = create_test_stack(values, 5);
	last = stack_last(stack);
	print_test_result("Five elements: last value is 5", last->value == 5);
	free_stack(&stack);

	/* Test 5: Verify last->next is always NULL */
	stack = create_test_stack(values, 5);
	last = stack_last(stack);
	print_test_result("Last node's next is NULL", last->next == NULL);
	free_stack(&stack);
}

/* ========================================================================== */
/*                        STACK_ADD_BACK TESTS                                */
/* ========================================================================== */

void	test_stack_add_back(void)
{
	t_stack	*stack;
	t_stack	*new_node;
	t_stack	*last;
	int		expected[] = {10, 20, 30, 40, 50};

	ft_printf("\n===== STACK_ADD_BACK TESTS =====\n");

	/* Test 1: Add to NULL stack (becomes first element) */
	stack = NULL;
	new_node = stack_new(42);
	stack_add_back(&stack, new_node);
	print_test_result("Add to NULL: stack points to new node",
		stack == new_node && stack->value == 42);
	free_stack(&stack);

	/* Test 2: Add NULL node (should do nothing) */
	stack = stack_new(1);
	stack_add_back(&stack, NULL);
	print_test_result("Add NULL node: stack unchanged",
		stack_size(stack) == 1);
	free_stack(&stack);

	/* Test 3: Add to single element stack */
	stack = stack_new(1);
	stack_add_back(&stack, stack_new(2));
	last = stack_last(stack);
	print_test_result("Add to single: last is new node", last->value == 2);
	print_test_result("Add to single: size is 2", stack_size(stack) == 2);
	free_stack(&stack);

	/* Test 4: Add multiple elements */
	stack = NULL;
	stack_add_back(&stack, stack_new(1));
	stack_add_back(&stack, stack_new(2));
	stack_add_back(&stack, stack_new(3));
	print_test_result("Add multiple: first is 1", stack->value == 1);
	print_test_result("Add multiple: last is 3", stack_last(stack)->value == 3);
	print_test_result("Add multiple: size is 3", stack_size(stack) == 3);
	free_stack(&stack);

	/* Test 5: Verify order preservation */
	stack = create_test_stack(expected, 5);
	print_test_result("Order preserved", verify_stack_values(stack, expected, 5));
	free_stack(&stack);
}

/* ========================================================================== */
/*                       STACK_ADD_FRONT TESTS                                */
/* ========================================================================== */

void	test_stack_add_front(void)
{
	t_stack	*stack;
	t_stack	*new_node;
	t_stack	*old_head;
	int		expected[] = {1, 2, 3};

	ft_printf("\n===== STACK_ADD_FRONT TESTS =====\n");

	/* Test 1: Add to NULL stack */
	stack = NULL;
	new_node = stack_new(42);
	stack_add_front(&stack, new_node);
	print_test_result("Add to NULL: stack points to new node",
		stack == new_node && stack->value == 42);
	free_stack(&stack);

	/* Test 2: Add to single element stack */
	stack = stack_new(2);
	stack_add_front(&stack, stack_new(1));
	print_test_result("Add to single: first is 1", stack->value == 1);
	print_test_result("Add to single: second is 2", stack->next->value == 2);
	print_test_result("Add to single: size is 2", stack_size(stack) == 2);
	free_stack(&stack);

	/* Test 3: Add multiple to front (reverse order) */
	stack = NULL;
	stack_add_front(&stack, stack_new(3));
	stack_add_front(&stack, stack_new(2));
	stack_add_front(&stack, stack_new(1));
	print_test_result("Multiple add_front: order is 1,2,3",
		verify_stack_values(stack, expected, 3));
	free_stack(&stack);

	/* Test 4: New node's next points to old head */
	stack = stack_new(100);
	old_head = stack;
	stack_add_front(&stack, stack_new(50));
	print_test_result("New head->next points to old head",
		stack->next == old_head);
	free_stack(&stack);

	/* Test 5: Original head remains accessible */
	stack = stack_new(999);
	stack_add_front(&stack, stack_new(1));
	print_test_result("Original head accessible via next",
		stack->next->value == 999);
	free_stack(&stack);
}

/* ========================================================================== */
/*                              MAIN                                          */
/* ========================================================================== */

int	main(void)
{
	ft_printf("========================================\n");
	ft_printf("     STACK_UTILS.C UNIT TESTS\n");
	ft_printf("========================================\n");

	test_stack_new();
	test_stack_size();
	test_stack_last();
	test_stack_add_back();
	test_stack_add_front();

	print_test_summary("stack_utils.c");

	return (g_tests_failed > 0 ? 1 : 0);
}
