/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   final_sorts.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 15:18:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/11 17:25:40 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "libft.h"
#include "lars_util.h"

t_3_order	get_group_order_3(t_list *stack)
{
	if (stack->content < stack->next->content)
	{
		if (stack->content > stack->next->next->content)
			return (O_231);
		if (stack->next->content < stack->next->next->content)
			return (O_123);
		return (O_132);
	}
	if (stack->content < stack->next->next->content)
		return (O_213);
	if (stack->next->content < stack->next->next->content)
		return (O_312);
	return (O_321);
}

t_status	sort_group_left_3(t_lars_data *data)
{
	t_3_order const	order = get_group_order_3(*data->stack_a);

	if (order == O_231 || order == O_312 || order == O_321)
		ps_exec_store(PB, data->stack_a, data->stack_b, data->ops);
	if (order == O_123 || order == O_132 || order == O_312)
		ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	if (order == O_132 || order == O_213 || order == O_231 || order == O_321)
		ps_exec_store(SA, data->stack_a, data->stack_b, data->ops);
	ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	if (order == O_123 || order == O_132 || order == O_213 || order == O_321)
		ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	if (order == O_231 || order == O_312 || order == O_321)
		ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	if (order == O_213 || order == O_231 || order == O_312 || order == O_321)
		ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	if (order == O_231)
		ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	return (ps_get_error());
}

t_status	sort_group_left(int group_size, t_lars_data *data)
{
	if (group_size == 0)
		return (OK);
	if (group_size == 3)
		return (sort_group_left_3(data));
	if (group_size == 1)
		return (ps_exec_store(RA, data->stack_a, data->stack_b, data->ops));
	if ((*data->stack_a)->content > (*data->stack_a)->next->content)
		ps_exec_store(SA, data->stack_a, data->stack_b, data->ops);
	ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	return (ps_get_error());
}

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

t_status	sort_left(t_list **stack_a, t_lars_data *data)
{
	int	len;
	int	size;

	len = ft_lstsize(*stack_a);
	while (len > 0)
	{
		size = group_size(which_group((long)(*stack_a)->content, data), data);
		if (sort_group_left(size, data) != OK)
			return (ps_get_error());
		len -= size;
	}
	return (OK);
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
