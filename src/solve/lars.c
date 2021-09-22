/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lars.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 17:49:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/22 17:58:28 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "libft.h"
#include <stdlib.h>

typedef int	t_1_group;

typedef struct s_3_group {
	t_1_group	low;
	t_1_group	middle;
	t_1_group	high;
	int			size;
}	t_3_group;

typedef struct s_group {
	t_1_group	*ones;
	t_3_group	*threes;
	int			size;
	int			index;
	int			total_size;
	int			size_to_index;
}	t_group;

typedef struct s_lars_data {
	t_group	*groups;
	t_list	**stack_a;
	t_list	**stack_b;
	int		total_size;
	int		num_groups;
}	t_lars_data;

// #include <stdio.h>
#include "TMP.h"

void	print_group(t_group *group)
{
	int i = 0;
	printf("size: %i\ntotal_size: %i\nones: ", group->size, group->total_size);
	while (i < group->size)
	{
		printf("[%i] ", group->ones[i]);
		i++;
	}
	printf("\nthrees: ");
	i = 0;
	while (i < group->size)
	{
		printf("[%i, %i, %i] ", group->threes[i].low, group->threes[i].middle, group->threes[i].high);
		i++;
	}
	printf("\n");
}

t_group	create_group(int len)
{
	t_group	group;

	group.ones = malloc(len * sizeof(t_1_group));
	if (group.ones == NULL)
		return (group);
	group.threes = malloc(len * sizeof(t_3_group));
	if (group.threes == NULL)
	{
		free(group.ones);
		group.ones = NULL;
		return (group);
	}
	group.size = len;
	group.index = 0;
	group.total_size = 0;
	group.size_to_index = 0;
	return (group);
}

t_3_group	*create_3_groups(int n_groups)
{
	t_3_group	*group_3s;
	int			i;

	group_3s = malloc((n_groups / 4) * sizeof(t_3_group));
	if (group_3s == NULL)
		return (NULL);
	i = 0;
	while (i < n_groups / 4)
	{
		group_3s[n_groups / 4 - 1 - i].low = i;
		group_3s[n_groups / 4 - 1 - i].middle = n_groups - n_groups / 4 - 1 - i;
		group_3s[n_groups / 4 - 1 - i].high = n_groups - i - 1;
		i++;
	}
	return (group_3s);
}

t_group	*free_groups(t_group *groups)
{
	int	i;

	i = 0;
	while (groups[i].ones != NULL)
	{
		free(groups[i].ones);
		free(groups[i].threes);
		i++;
	}
	free(groups);
	return (NULL);
}

t_group	*create_groups(int n_groups, const t_3_group *group_3s)
{
	t_group		*groups;
	int			i;

	if (group_3s == NULL)
		return (NULL);
	groups = malloc(3 * sizeof(t_group));
	if (groups == NULL)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		groups[i] = create_group(n_groups / 12);
		if (groups[i].ones == NULL)
			return (free_groups(groups));
		i++;
	}
	return (groups);
}

t_group	*get_groups(int n_groups)
{
	const t_3_group	*threes = create_3_groups(n_groups);
	const t_group	*groups = create_groups(n_groups, threes);
	int				i;
	int				j;
	int				k;

	if (threes == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (k < 3)
	{
		j = 0;
		while (j < groups[k].size)
		{
			groups[k].ones[j] = n_groups / 4 * 2 - 1 - i;
			groups[k].threes[j] = threes[i];
			i++;
			j++;
		}
		k++;
	}
	return ((t_group *)groups);
}

int	in_group(int v, t_group *group)
{
	if (group->ones[group->index] == v)
		return (1);
	if (group->threes[group->index].low == v)
		return (2);
	if (group->threes[group->index].middle == v)
		return (3);
	if (group->threes[group->index].high == v)
		return (4);
	return (0);
}

int	anywhere_in_group(int v, t_group *group)
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

void	split_to_three(t_lars_data *data)
{
	int			top_value_group;
	int			i;

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

void	resolve_group_v(t_group *group, int side, int value, t_lars_data *data)
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

void	resolve_group_step(t_group *group, int side, t_lars_data *data)
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

void	sort_left(t_list **stack_a, t_lars_data  *data)
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

void	sort_right(t_list **stack_a, t_list **stack_b, t_lars_data  *data)
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
	return (EXIT_SUCCESS);
}
