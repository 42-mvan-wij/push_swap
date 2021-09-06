/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bucket_sort.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 15:37:27 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/06 18:07:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"
#include "solve.h"

#include "TMP.h"

void	bucket_sort_b(t_list **stack_a, t_list **stack_b, int len_a, int len_b);

int	find_mid(t_list *stack, int len)
{
	int	min;
	int	max;

	min = (long)stack->content;
	max = (long)stack->content;
	while (len > 1)
	{
		stack = stack->next;
		if ((long)stack->content < min)
			min = (long)stack->content;
		if ((long)stack->content > max)
			max = (long)stack->content;
		len--;
	}
	return ((min + max) / 2);
}

void	bucket_it(t_list **stack_a, t_list **stack_b, int side, int len)
{
	int	mid;

	if (side == 0)
	{
		mid = find_mid(*stack_a, len);
		while (len > 0)
		{
			if ((long)(*stack_a)->content <= mid)
				ps_exec_print("pb", stack_a, stack_b);
			else
				ps_exec_print("ra", stack_a, stack_b);
			len--;
		}
		return ;
	}
	mid = find_mid(*stack_b, len);
	while (len > 0)
	{
		if ((long)(*stack_b)->content > mid)
			ps_exec_print("pa", stack_a, stack_b);
		else
			ps_exec_print("rb", stack_a, stack_b);
		len--;
	}
}

void	bucket_sort_a(t_list **stack_a, t_list **stack_b, int len_a, int len_b)
{
	if (len_a == 2 && (*stack_a)->content > (*stack_a)->next->content)
		ps_exec_print("sa", stack_a, stack_b);
	else if (len_a > 2)
	{
		bucket_it(stack_a, stack_b, 0, len_a);
		bucket_sort_a(stack_a, stack_b, len_a / 2, (len_a + 1) / 2);
	}
	if (len_b == 2 && (*stack_b)->content < (*stack_b)->next->content)
		ps_exec_print("sb", stack_a, stack_b);
	else if (len_b > 2)
	{
		bucket_it(stack_a, stack_b, 1, len_b);
		bucket_sort_b(stack_a, stack_b, (len_b + 1) / 2, len_b / 2);
	}
	while (len_b > 0)
	{
		ps_exec_print("pa", stack_a, stack_b);
		len_b--;
	}
}

void	bucket_sort_b(t_list **stack_a, t_list **stack_b, int len_a, int len_b)
{
	if (len_b == 2 && (*stack_b)->content < (*stack_b)->next->content)
		ps_exec_print("sb", stack_a, stack_b);
	else if (len_b > 2)
	{
		bucket_it(stack_a, stack_b, 1, len_b);
		bucket_sort_b(stack_a, stack_b, len_b / 2, (len_b + 1) / 2);
	}
	if (len_a == 2 && (*stack_a)->content > (*stack_a)->next->content)
		ps_exec_print("sa", stack_a, stack_b);
	else if (len_a > 2)
	{
		bucket_it(stack_a, stack_b, 0, len_a);
		bucket_sort_a(stack_a, stack_b, (len_a + 1) / 2, len_a / 2);
	}
	while (len_a > 0)
	{
		ps_exec_print("pb", stack_a, stack_b);
		len_a--;
	}
}

void	bucket_sort(t_list **stack_a, t_list **stack_b)
{
	bucket_sort_a(stack_a, stack_b, ft_lstsize(*stack_a), 0);
}
