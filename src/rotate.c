/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 23:10:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/03 14:57:55 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ps_rotate(t_list **stack)
{
	t_list	*next;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	ft_lstadd_back(stack, *stack);
	next = (*stack)->next;
	(*stack)->next = NULL;
	*stack = next;
}

void	ps_reverse_rotate(t_list **stack)
{
	t_list	*before_last;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	before_last = *stack;
	while (before_last->next->next != NULL)
		before_last = before_last->next;
	before_last->next->next = *stack;
	*stack = before_last->next;
	before_last->next = NULL;
}

void	ps_rotate2(t_list **stack_a, t_list **stack_b)
{
	ps_rotate(stack_a);
	ps_rotate(stack_b);
}

void	ps_reverse_rotate2(t_list **stack_a, t_list **stack_b)
{
	ps_reverse_rotate(stack_a);
	ps_reverse_rotate(stack_b);
}
