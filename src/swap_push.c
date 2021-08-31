/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_push.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 22:40:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/31 16:21:34 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ps_swap(t_list **stack)
{
	t_list	*next;

	if (*stack == NULL || (*stack)->next == NULL)
		return (0);
	next = (*stack)->next;
	(*stack)->next = (*stack)->next->next;
	next->next = (*stack);
	*stack = next;
	return (1);
}

int	ps_swap2(t_list **stack_a, t_list **stack_b)
{
	int	did_something;

	did_something = ps_swap(stack_a);
	return (ps_swap(stack_b) || did_something);
}

int	ps_push(t_list **to_stack, t_list **from_stack)
{
	t_list	*next;

	if (*from_stack == NULL)
		return (0);
	next = (*from_stack)->next;
	ft_lstadd_front(to_stack, *from_stack);
	*from_stack = next;
	return (1);
}
