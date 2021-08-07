/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 15:07:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/07 16:38:51 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"

#include "TMP.h"
#include <stdio.h>

void	radix_sort(t_list **stack_a, t_list **stack_b, int base)
{
	int		len;
	int		val;
	int		digit;
	int		i;

	len = ft_lstsize(*stack_a);
	digit = 1;
	while ((len - 1) / digit != 0)
	{
		i = 0;
		while (i < base - 1)
		{
			while (len > 0)
			{
				val = ((long)(*stack_a)->content / digit) % base;
				// printf("%i\n", val);
				if (val == i)
					ps_exec_print("pb", stack_a, stack_b);
				else
					ps_exec_print("ra", stack_a, stack_b);
				len--;
			}
			len = ft_lstsize(*stack_a);
			i++;
		}
		while (*stack_b != NULL)
			ps_exec_print("pa", stack_a, stack_b);
		digit *= base;
		len = ft_lstsize(*stack_a);
	}
}
// 0s + 1s + 2s  +  1s + 2s    +    0s + 1s
// 0s + 1s + 2s + 3s  +  1s + 2s + 3s  +  2s + 3s    +    0s + 1s + 2s
// 2 * 0s + 3 * 1s + 4 * 2s + 3 * 3s
