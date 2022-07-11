/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 14:28:58 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/05 12:34:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lars_util.h"

int	which_group(int n, t_lars_data *data)
{
	const int	extra = data->total_size % data->num_groups;
	const int	group_size = data->total_size / data->num_groups;
	const int	regular = group_size * (data->num_groups - extra);

	if (n < regular)
		return (n / group_size);
	return ((n - regular) / (group_size + 1) + (data->num_groups - extra));
}

int	group_size(int n, t_lars_data *data)
{
	const int	extra = data->total_size % data->num_groups;
	const int	group_size = data->total_size / data->num_groups;

	if (n < data->num_groups - extra)
		return (group_size);
	return (group_size + 1);
}

t_group_type	in_group(int v, t_family *group)
{
	if (group->ones[group->index] == v)
		return (ONES);
	if (group->threes[group->index].low == v)
		return (THREES_LOW);
	if (group->threes[group->index].middle == v)
		return (THREES_MIDDLE);
	if (group->threes[group->index].high == v)
		return (THREES_HIGH);
	return (OTHER);
}

int	anywhere_in_family(int v, t_family *group)
{
	int	i;

	i = 0;
	while (i < group->size)
	{
		if (group->ones[i] == v
			|| group->threes[i].low == v
			|| group->threes[i].middle == v
			|| group->threes[i].high == v)
			return (1);
		i++;
	}
	return (0);
}
