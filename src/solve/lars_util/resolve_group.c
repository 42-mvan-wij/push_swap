/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resolve_group.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 15:12:25 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/23 15:12:25 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "lars_util.h"

static void	resolve_v(t_group *group, int side, int value, t_lars_data *data)
{
	const int	g = in_group(value, group);

	if (side == 0)
	{
		if (g == 0 || g == 1)
			ps_exec_print("pb", data->stack_a, data->stack_b);
		if (g == 1)
			ps_exec_print("rb", data->stack_a, data->stack_b);
		else if (g != 0)
			ps_exec_print("ra", data->stack_a, data->stack_b);
		return ;
	}
	if (g == 1)
		ps_exec_print("rb", data->stack_a, data->stack_b);
	if (g != 1)
		ps_exec_print("pa", data->stack_a, data->stack_b);
	if (g != 0 && g != 1)
		ps_exec_print("ra", data->stack_a, data->stack_b);
}

static void	resolve_group_step(t_group *group, int side, t_lars_data *data)
{
	t_list	**stack;
	int		i;
	int		value_group;

	if (side == 0)
		stack = data->stack_a;
	else
		stack = data->stack_b;
	i = group->total_size - group->size_to_index;
	while (i > 0)
	{
		value_group = which_group((long)(*stack)->content, data);
		resolve_group_v(group, side, value_group, data);
		i--;
	}
	group->size_to_index
		+= group_size(group->ones[group->index], data)
		+ group->threes[group->index].size;
	group->index++;
}

void	resolve_group(t_group *group, int starting_side, t_lars_data *data)
{
	int	side0;
	int	side1;

	side0 = 0;
	side1 = 1;
	if (starting_side == 1)
	{
		side0 = 1;
		side1 = 0;
	}
	while (group->index < group->size)
	{
		resolve_group_step(group, side0, data);
		if (group->index < group->size)
			resolve_group_step(group, side1, data);
	}
}
