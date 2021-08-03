/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 15:07:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/03 16:27:38 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"

void	sort(t_list **stack_a, t_list **stack_b)
{
	int		len;
	long	val;
	int		max_bits;

	len = ft_lstsize(*stack_a);
	max_bits = 0;
	while (len >> max_bits != 0)
		max_bits++;
	while (max_bits > 0)
	{
		while (len > 0)
		{
			val = (long)(*stack_a)->content & 1;
			(*stack_a)->content = (void *)((long)(*stack_a)->content >> 1);
			if (val == 0)
				ps_exec_print("ra", stack_a, stack_b);
			else
				ps_exec_print("pb", stack_a, stack_b);
			len--;
		}
		while (*stack_b != NULL)
			ps_exec_print("pa", stack_a, stack_b);
		max_bits--;
	}
}
