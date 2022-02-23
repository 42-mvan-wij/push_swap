/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 15:07:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/23 14:44:17 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"

static void	move_to_b(t_list **stack_a, t_list **stack_b, int digit, int base)
{
	int	i;
	int	val;
	int	len;

	i = 0;
	while (i < base - 1)
	{
		len = ft_lstsize(*stack_a);
		while (len > 0)
		{
			val = ((long)(*stack_a)->content / digit) % base;
			if (val == i)
				ps_exec_print("pb", stack_a, stack_b);
			else
				ps_exec_print("ra", stack_a, stack_b);
			len--;
		}
		i++;
	}
}

void	radix_sort(t_list **stack_a, t_list **stack_b, int base)
{
	int		len;
	int		digit;

	len = ft_lstsize(*stack_a);
	digit = 1;
	while ((len - 1) / digit != 0)
	{
		move_to_b(stack_a, stack_b, digit, base);
		while (*stack_b != NULL)
			ps_exec_print("pa", stack_a, stack_b);
		digit *= base;
		len = ft_lstsize(*stack_a);
	}
}
