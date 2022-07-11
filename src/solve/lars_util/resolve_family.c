/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resolve_family.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 15:12:25 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/11 17:29:11 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "lars_util.h"

static t_status	resolve_v(t_family *group, int side, int value,
					t_lars_data *data)
{
	const t_group_type	g = in_group(value, group);

	if (side == 0)
	{
		if (g == OTHER || g == ONES)
			ps_exec_store(PB, data->stack_a, data->stack_b, data->ops);
		if (g == ONES)
			ps_exec_store(RB, data->stack_a, data->stack_b, data->ops);
		if (g != OTHER && g != ONES)
			ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
		return (ps_get_error());
	}
	if (g == ONES)
		ps_exec_store(RB, data->stack_a, data->stack_b, data->ops);
	if (g != ONES)
		ps_exec_store(PA, data->stack_a, data->stack_b, data->ops);
	if (g != OTHER && g != ONES)
		ps_exec_store(RA, data->stack_a, data->stack_b, data->ops);
	return (ps_get_error());
}

static t_status	resolve_family_step(t_family *family, int side,
					t_lars_data *data)
{
	t_list	**stack;
	int		i;
	int		value_group;

	if (side == 0)
		stack = data->stack_a;
	else
		stack = data->stack_b;
	i = family->total_size - family->size_to_index;
	while (i > 0)
	{
		value_group = which_group((long)(*stack)->content, data);
		if (resolve_v(family, side, value_group, data) != OK)
			return (ps_get_error());
		i--;
	}
	family->size_to_index
		+= group_size(family->ones[family->index], data)
		+ family->threes[family->index].size;
	family->index++;
	return (OK);
}

// |	ones			| |		|
// |	threes_low		| |		|
// |	threes_middle	| |		|
// |	threes_high		| |		|
// |	other			| |		|

// |	threes_low		| |	other	|
// |	threes_middle	| |			|
// |	threes_high		| |			|
// |					| |	ones	|

t_status	resolve_family(t_family *family, int starting_side,
				t_lars_data *data)
{
	int	side0;
	int	side1;

	side0 = 0;
	if (starting_side == 1)
		side0 = 1;
	side1 = 1 - side0;
	while (family->index < family->size)
	{
		if (resolve_family_step(family, side0, data) != OK)
			return (ps_get_error());
		if (family->index < family->size)
			if (resolve_family_step(family, side1, data) != OK)
				return (ps_get_error());
	}
	return (OK);
}
