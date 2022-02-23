/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lars.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 17:49:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/23 14:44:01 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "lars_util/lars_util.h"
#include "libft.h"
#include <stdlib.h>

void	split_to_three(t_lars_data *data)
{
	int	top_value_group;
	int	i;

	i = 0;
	while (i < data->total_size)
	{
		top_value_group = which_group((long)(*data->stack_a)->content, data);
		if (anywhere_in_group(top_value_group, &data->groups[0]))
			ps_exec_print("ra", data->stack_a, data->stack_b);
		else
		{
			ps_exec_print("pb", data->stack_a, data->stack_b);
			if (anywhere_in_group(top_value_group, &data->groups[2]))
				ps_exec_print("rb", data->stack_a, data->stack_b);
		}
		i++;
	}
}

void	fix_group_sizes(t_lars_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < data->groups[i].size)
		{
			data->groups[i].threes[j].size
				= group_size(data->groups[i].threes[j].low, data)
				+ group_size(data->groups[i].threes[j].middle, data)
				+ group_size(data->groups[i].threes[j].high, data);
			data->groups[i].total_size
				+= data->groups[i].threes[j].size
				+ group_size(data->groups[i].ones[j], data);
			j++;
		}
		i++;
	}
}

t_lars_data	create_data(int num_groups, t_list **stack_a, t_list **stack_b)
{
	t_lars_data	data;

	data.stack_a = stack_a;
	data.stack_b = stack_b;
	data.total_size = ft_lstsize(*stack_a);
	data.num_groups = num_groups;
	data.groups = get_groups(num_groups);
	fix_group_sizes(&data);
	return (data);
}

void	solve_threes(t_group *group, t_lars_data *data)
{
	int	value_group;
	int	which_three;
	int	i;

	group->index = 0;
	while (group->index < group->size)
	{
		i = group->threes[group->index].size;
		while (i > 0)
		{
			value_group = which_group((long)(*data->stack_a)->content, data);
			which_three = in_group(value_group, group) - 2;
			if (which_three == 0 || which_three == 1)
				ps_exec_print("pb", data->stack_a, data->stack_b);
			else
				ps_exec_print("ra", data->stack_a, data->stack_b);
			if (which_three == 0)
				ps_exec_print("rb", data->stack_a, data->stack_b);
			i--;
		}
		group->index++;
	}
}

int	sort_lars(t_list **stack_a, t_list **stack_b)
{
	const int	size = ft_lstsize(*stack_a);
	int			num_groups;
	t_lars_data	data;

	num_groups = size / 3;
	if (num_groups % 12 != 0)
		num_groups += 12 - (num_groups % 12);
	data = create_data(num_groups, stack_a, stack_b);
	if (data.groups == NULL)
		return (EXIT_FAILURE);
	split_to_three(&data);
	resolve_group(&data.groups[0], 0, &data);
	resolve_group(&data.groups[1], 1, &data);
	resolve_group(&data.groups[2], 1, &data);
	solve_threes(&data.groups[0], &data);
	solve_threes(&data.groups[1], &data);
	solve_threes(&data.groups[2], &data);
	sort_left(stack_a, &data);
	sort_right(stack_a, stack_b, &data);
	free_groups(data.groups);
	return (EXIT_SUCCESS);
}
