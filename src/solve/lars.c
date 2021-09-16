/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lars.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 17:49:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/16 18:01:22 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ________________________        ________________________
//    1-3-4   |     2                   4     |     3
//            |                               |     2
//            |                               |     1
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |
//            |                               |


// ________________________       ________________________       ________________________
//    2-4-6   |     3                1-5-7   |     4                  6     |     5
//    1-5-7   |                        6     |     3                  7     |     4
//            |                              |     2                        |     3
//            |                              |                              |     2
//            |                              |                              |     1
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |
//            |                              |                              |



// ________________________       ________________________       ________________________       ________________________
//    3-5-8   |     4                2-6-9   |     5                1-7-10  |     6                  8     |     7
//    2-6-9   |                      1-7-10  |     4                  8     |     5                  9     |     6
//    1-7-10  |                        8     |     3                  9     |     4                  10    |     5
//            |                              |                              |     3                        |     4
//            |                              |                              |     2                        |     3
//            |                              |                              |                              |     2
//            |                              |                              |                              |     1
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |
//            |                              |                              |                              |





// ___________________________________________
//    l+n -  m+q+1  - h-n   |         m+q
//            ...           |         ...
//    l+3 - m+q+n-3 - h-3   |         m+3
//    l+2 - m+q+n-2 - h-2   |         m+2
//    l+1 - m+q+n-1 - h-1   |         m+1
//     l  - m+q+n   -  h    |       m=l+n+1



// m = l + n + 1
// ___________________________________________
//                      |     (l+1 - m+4 - h-1) - (l+n-1 - m+2 - h-n-1) - (m+1)
//                      |     (l - m+n - h)     - (l+n - m+1 - h-n) - (m)
//                      |         m+q
//                      |         ...
//                      |         m+3
//                      |         m+2



//_________________        ________________________________        ______________________________        ______________________________    ______________________________    ______________________________
//    57   |                    57/3=19   |    57/3=19                  3   |    19 - 4 = 15                  15 - 4 = 11   |    19             3   |    11 - 4 = 7              7-4=3   |    19
//                                             57/3=19                      |    19                           3             |    19             3   |    19                       3      |    19
//                                                                          |    19                           3             |    1              3   |    19                       3      |    1
//                                                                          |    1                                          |    1                  |    1                        3      |    1
//                                                                                                                                                  |    1                        3      |    1
//                                                                                                                                                  |    1

//   (groups / 3) % 4 = 1 => perfect
//   (groups / 3) % 4 = 0 => prefect 2 ?

//    ______________________________
//       19 - 4 = 15  |    19
//         3          |    1
//         3          |    1
//         3          |    1
//         3          |    1
//         3          |

// #3s = #1s + o=(1,2)

// #l: n + 1     #m: q + 1    #h: n + 1
// o == 1
//     #l + #m + #h = (n + 1) * 2 + n = 3n + 2
// o == 2
//     #l + #m + #h = (n + 1) * 2 + (n - 1) = 3n + 1


// 1_groups = groups % 4 = 1
// 3_groups = groups % 4 = (0, 2, 3)



// 15_group = 3_group + 11_group + 1_group
// 11_group = 3_group + 7_group + 1_group
// 7_group = 3_group + 3_group + 1_group

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

t_3_group	create_3_group(t_1_group low, t_1_group middle, t_1_group high)
{
	t_3_group	group;
	int			i;

	group.low = low;
	group.middle = middle;
	group.high = high;
	group.size = 0;
	return (group);
}

t_group	create_group(int len)
{
	t_group	group;

	group.ones = malloc(len * sizeof(t_1_group *));
	if (group.ones == NULL)
		return (group);
	group.threes = malloc(len * sizeof(t_3_group *));
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

t_3_group	**free_3_groups(t_3_group ***threes)
{
	int	i;

	if (*threes == NULL)
		return (NULL);
	i = 0;
	while ((*threes)[i] != NULL)
	{
		free((*threes)[i]);
		i++;
	}
	free(*threes);
	*threes = NULL;
	return (NULL);
}

t_group	*free_group(t_group **group)
{
	if (*group == NULL)
		return (NULL);
	if ((*group)->ones != NULL)
		free((*group)->ones);
	if ((*group)->threes != NULL)
		free_3_groups(&(*group)->threes);
	free(*group);
	*group = NULL;
	return (NULL);
}

t_group	**free_groups(t_group ***groups)
{
	int	i;

	if (*groups == NULL)
		return (NULL);
	i = 0;
	while ((*groups)[i] != NULL)
	{
		free_group(&(*groups)[i]);
		i++;
	}
	free(*groups);
	*groups = NULL;
	return (NULL);
}

t_3_group	**create_3_groups(int n_groups)
{
	t_3_group	*group_3s;
	int			i;

	group_3s = malloc((n_groups / 4) * sizeof(t_3_group));
	if (group_3s == NULL)
		return (NULL);
	i = 0;
	while (i < n_groups / 4)
	{
		group_3s[n_groups / 4 - 1 - i] = create_3_group(
				i,
				n_groups - n_groups / 4 - 1 - i,
				n_groups - i - 1);
		i++;
	}
	return (group_3s);
}

t_group	*create_groups(int n_groups, t_3_group *group_3s)
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
		i++;
	}
	return (groups);
}

t_group	*get_groups(int n_groups)
{
	const t_3_group	*threes = create_3_groups(n_groups);
	const t_group	*groups = create_groups(n_groups, threes);
	const int		middle_ones_low = n_groups / 4;
	int				i;
	int				j;

	if (threes == NULL)
		return (NULL);
	i = 0;
	while (i < groups[0].size)
	{
		groups[0].ones[i] = middle_ones_low + i;
		groups[0].threes[i] = threes[i];
		i++;
	}
	print_group(&groups[0]);
	printf("\n\n---------------\n\n");
	j = 0;
	while (j < groups[1].size)
	{
		groups[1].ones[j] = middle_ones_low + i;
		groups[1].threes[j] = threes[i];
		i++;
		j++;
	}
	print_group(&groups[1]);
	printf("\n\n---------------\n\n");
	j = 0;
	while (j < groups[2].size)
	{
		groups[2].ones[j] = middle_ones_low + i;
		groups[2].threes[j] = threes[i];
		j++;
		i++;
	}
	print_group(&groups[2]);
	printf("\n\n---------------\n\n");
	return (groups);
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

int	is_anywhere_in_group(int v, t_group *group)
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

int	is_in_group(int v, t_group *group)
{
	int	i;

	i = 0;
	while (i < group->size)
	{
		if (group->ones[i] == v)
			return (1);
		if (group->threes[i].low == v
			|| group->threes[i].middle == v
			|| group->threes[i].high == v)
			return (2);
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
		top_value_group = which_group((*data->stack_a)->content, data);
		if (is_anywhere_in_group(top_value_group, &data->groups[0]))
			ps_exec_print("ra", data->stack_a, data->stack_b);
		else
		{
			ps_exec_print("pb", data->stack_a, data->stack_b);
			if (is_anywhere_in_group(top_value_group, &data->groups[2]))
				ps_exec_print("rb", data->stack_a, data->stack_b);
		}
		i++;
	}
}

void	resolve_group_value(t_group *group, int side, int value, t_lars_data *data)
{
	const int	g = in_group(value, group);

	if (side == 0) // stack a
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

	i = group->total_size - group->size_to_index;
	while (i > 0)
	{
		if (side == 0)
			resolve_group_value(group, side, which_group((*data->stack_a)->content, data), data);
		else
			resolve_group_value(group, side, which_group((*data->stack_b)->content, data), data);
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
	int			i;
	int			group;
	int			j;
	int			k;

	data.stack_a = stack_a;
	data.stack_b = stack_b;
	data.total_size = ft_lstsize(*stack_a);
	data.num_groups = num_groups;
	data.groups = get_groups(num_groups);
	// fix_group_sizes(&data);
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
			value_group = which_group((*data->stack_a)->content, data);
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

typedef struct s_debug_list {
	long content;
	struct s_debug_list *next;
} t_debug_list;
typedef struct s_debug_data {
	struct {
		int ones[3];
		t_3_group threes[3];
		int size;
		int index;
	} *groups[3];
	t_debug_list	**stack_a;
	t_list	**stack_b;
	int		total_size;
	int		num_groups;
} t_debug_data;

int	sort_lars(t_list **stack_a, t_list **stack_b)
{
	const int num_groups = 12 * 3;
	t_lars_data	data = create_data(num_groups, stack_a, stack_b);
	t_debug_data db_data = *((t_debug_data*)&data);
	db_data.stack_a = data.stack_a;
	db_data.stack_b = data.stack_b;
	if (data.groups == NULL)
		return (EXIT_FAILURE);
	int i = 0;
	while (i < 3)
	{
		print_group(&data.groups[i]);
		printf("\n");
		i++;
	}

	split_to_three(&data);
	resolve_group(&data.groups[0], 0, &data);
	resolve_group(&data.groups[1], 1, &data);
	resolve_group(&data.groups[2], 1, &data);
	// print_stacks(*data.stack_a, *data.stack_b);
	print_group(&data.groups[0]);
	print_group(&data.groups[1]);
	print_group(&data.groups[2]);
	// solve_threes(&data.groups[0], &data);
	// solve_threes(&data.groups[1], &data);
	// solve_threes(&data.groups[2], &data);
	print_stacks(*data.stack_a, *data.stack_b);

	// t_list	*cur = *data.stack_a;
	// while (cur != NULL)
	// {
	// 	cur->content = which_group(cur->content, &data);
	// 	cur = cur->next;
	// }
	// cur = *data.stack_b;
	// while (cur != NULL)
	// {
	// 	cur->content = which_group(cur->content, &data);
	// 	cur = cur->next;
	// }
	// print_stacks(*data.stack_a, *data.stack_b);


	return (EXIT_SUCCESS);
}

// int	main2(void)
// {
// 	const int num_groups = 12 * 3;
// 	t_list **stack_a;
// 	t_list **stack_b;
// 	*stack_a = NULL;
// 	*stack_b = NULL;
// 	t_lars_data	data = create_data(num_groups, stack_a, stack_b);
// 	if (data.groups == NULL)
// 		return (EXIT_FAILURE);
// 	int i = 0;
// 	while (data.groups[i] != NULL)
// 	{
// 		print_group(data.groups[i]);
// 		printf("\n");
// 		i++;
// 	}

// 	split_to_three(&data);
// 	resolve_group(data.groups[0], 0, &data);
// 	resolve_group(data.groups[1], 1, &data);
// 	resolve_group(data.groups[2], 1, &data);
// }
