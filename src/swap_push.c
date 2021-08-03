/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_push.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 22:40:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/03 14:57:59 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ps_swap(t_list **stack)
{
	t_list	*next;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	next = (*stack)->next;
	(*stack)->next = (*stack)->next->next;
	next->next = (*stack);
	*stack = next;
}

void	ps_swap2(t_list **stack_a, t_list **stack_b)
{
	ps_swap(stack_a);
	ps_swap(stack_b);
}

void	ps_push(t_list **to_stack, t_list **from_stack)
{
	t_list	*next;

	if (*from_stack == NULL)
		return ;
	next = (*from_stack)->next;
	ft_lstadd_front(to_stack, *from_stack);
	*from_stack = next;
}
