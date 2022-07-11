/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   final_sorts.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 15:18:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/06 12:52:15 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "libft.h"
#include "lars_util.h"

t_status	sort_group(int group_size, t_list **stack_a, t_lars_data *data)
{
	if (group_size <= 1)
		return (OK);
	if ((*stack_a)->content > (*stack_a)->next->content)
		ps_exec_store(SA, stack_a, NULL, data->ops);
	if (group_size == 2)
		return (ps_get_error());
	if ((*stack_a)->next->content > (*stack_a)->next->next->content)
	{
		ps_exec_store(RA, stack_a, NULL, data->ops);
		ps_exec_store(SA, stack_a, NULL, data->ops);
		ps_exec_store(RRA, stack_a, NULL, data->ops);
	}
	if ((*stack_a)->content > (*stack_a)->next->content)
		ps_exec_store(SA, stack_a, NULL, data->ops);
	return (ps_get_error());
}

t_status	sort_left(t_list **stack_a, t_lars_data *data)
{
	int	len;
	int	size;

	len = ft_lstsize(*stack_a);
	while (len > 0)
	{
		size = group_size(which_group((long)(*stack_a)->content, data), data);
		if (sort_group(size, stack_a, data) != OK)
			return (ps_get_error());
		len -= size;
		while (size > 0)
		{
			if (ps_exec_store(RA, stack_a, NULL, data->ops) != OK)
				return (ps_get_error());
			size--;
		}
	}
	return (OK);
}

t_status	sort_right(t_list **stack_a, t_list **stack_b, t_lars_data *data)
{
	int	size;
	int	i;

	while (*stack_b != NULL)
	{
		size = group_size(which_group((long)(*stack_b)->content, data), data);
		i = 0;
		while (i < size)
		{
			if (ps_exec_store(PA, stack_a, stack_b, data->ops) != OK)
				return (ps_get_error());
			i++;
		}
		if (sort_group(size, stack_a, data) != OK)
			return (ps_get_error());
	}
	return (OK);
}
