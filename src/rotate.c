/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 23:10:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/31 16:24:35 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ps_rotate(t_list **stack)
{
	t_list	*next;

	if (*stack == NULL || (*stack)->next == NULL)
		return (0);
	ft_lstadd_back(stack, *stack);
	next = (*stack)->next;
	(*stack)->next = NULL;
	*stack = next;
	return (1);
}

int	ps_reverse_rotate(t_list **stack)
{
	t_list	*before_last;

	if (*stack == NULL || (*stack)->next == NULL)
		return (0);
	before_last = *stack;
	while (before_last->next->next != NULL)
		before_last = before_last->next;
	before_last->next->next = *stack;
	*stack = before_last->next;
	before_last->next = NULL;
	return (1);
}

int	ps_rotate2(t_list **stack_a, t_list **stack_b)
{
	int	did_something;

	did_something = ps_rotate(stack_a);
	return (ps_rotate(stack_b) || did_something);
}

int	ps_reverse_rotate2(t_list **stack_a, t_list **stack_b)
{
	int	did_something;

	did_something = ps_reverse_rotate(stack_a);
	return (ps_reverse_rotate(stack_b) || did_something);
}
