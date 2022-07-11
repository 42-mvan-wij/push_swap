/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   final_sorts_right.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 15:18:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/11 17:30:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "lars_util.h"

t_status	sort_group_right_3(t_lars_data *data)
{
	t_3_order const	order = get_group_order_3(*data->stack_b);

	if (order == O_123 || order == O_132 || order == O_213)
		ps_exec_store(RB, data->stack_a, data->stack_b, data->ops);
	if (order == O_123 || order == O_213 || order == O_231)
		ps_exec_store(SB, data->stack_a, data->stack_b, data->ops);
	ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	if (order != O_213)
		ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	if (order == O_123 || order == O_132 || order == O_213)
		ps_exec_store(RRB, data->stack_a, data->stack_b, data->ops);
	ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	if (order == O_213)
		ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	if (order == O_312)
		ps_exec_store(SA, data->stack_a, data->stack_b, data->ops);
	return (ps_get_error());
}

t_status	sort_group_right(int group_size, t_lars_data *data)
{
	if (group_size == 0)
		return (OK);
	if (group_size == 3)
		return (sort_group_right_3(data));
	if (group_size == 1)
		return (ps_exec_store(PA, data->stack_a, data->stack_b, data->ops));
	ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	if ((*data->stack_a)->content > (*data->stack_a)->next->content)
		ps_exec_store(SA, data->stack_a, data->stack_b, data->ops);
	return (ps_get_error());
}

t_status	sort_right(t_list **stack_b, t_lars_data *data)
{
	int	size;

	while (*stack_b != NULL)
	{
		size = group_size(which_group((long)(*stack_b)->content, data), data);
		if (sort_group_right(size, data) != OK)
			return (ps_get_error());
	}
	return (OK);
}
