/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   final_sorts.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 15:18:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/23 15:18:20 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "libft.h"
#include "lars_util.h"

void	sort_group(int group_size, t_list **stack_a)
{
	if (group_size <= 1)
		return ;
	if ((*stack_a)->content > (*stack_a)->next->content)
		ps_exec_print("sa", stack_a, NULL);
	if (group_size == 2)
		return ;
	if ((*stack_a)->next->content > (*stack_a)->next->next->content)
	{
		ps_exec_print("ra", stack_a, NULL);
		ps_exec_print("sa", stack_a, NULL);
		ps_exec_print("rra", stack_a, NULL);
	}
	if ((*stack_a)->content > (*stack_a)->next->content)
		ps_exec_print("sa", stack_a, NULL);
}

void	sort_left(t_list **stack_a, t_lars_data *data)
{
	int	len;
	int	size;

	len = ft_lstsize(*stack_a);
	while (len > 0)
	{
		size = group_size(which_group((long)(*stack_a)->content, data), data);
		sort_group(size, stack_a);
		len -= size;
		while (size > 0)
		{
			ps_exec_print("ra", stack_a, NULL);
			size--;
		}
	}
}

void	sort_right(t_list **stack_a, t_list **stack_b, t_lars_data *data)
{
	int	size;
	int	i;

	while (*stack_b != NULL)
	{
		size = group_size(which_group((long)(*stack_b)->content, data), data);
		i = 0;
		while (i < size)
		{
			ps_exec_print("pa", stack_a, stack_b);
			i++;
		}
		sort_group(size, stack_a);
	}
}
