/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lars.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 17:49:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/13 15:06:07 by mvan-wij      ########   odam.nl         */
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

#include <stdlib.h>

typedef	int t_1_group;

typedef struct {
	t_1_group	low;
	t_1_group	middle;
	t_1_group	high;
} t_3_group;

typedef struct {
	t_1_group	*ones;
	t_3_group	**threes;
	int			size;
} t_group;

t_3_group	*create_3_group(t_1_group low, t_1_group middle, t_1_group high)
{
	t_3_group	*group;

	group = malloc(sizeof(t_3_group));
	if (group == NULL)
		return (NULL);
	group->low = low;
	group->middle = middle;
	group->high = high;
	return (group);
}

t_group	*create_group(int len)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (group == NULL)
		return (NULL);
	group->ones = malloc((len + 1) * sizeof(t_1_group));
	if (group->ones == NULL)
	{
		free(group);
		return (NULL);
	}
	group->threes = malloc((len + 1) * sizeof(t_3_group *));
	if (group->threes == NULL)
	{
		free(group->ones);
		free(group);
		return (NULL);
	}
	group->ones[len] = -1;
	group->threes[len] = NULL;
	group->size = len;
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
	t_3_group	**group_3s;
	int			i;

	group_3s = malloc((n_groups / 4 + 1) * sizeof(t_3_group *));
	if (group_3s == NULL)
		return (NULL);
	i = 0;
	while (i < n_groups / 4)
	{
		group_3s[n_groups / 4 - 1 - i] = create_3_group(i, n_groups - n_groups / 4 - 1 - i, n_groups - i - 1);
		if (group_3s[n_groups / 4 - 1 - i] == NULL)
			return (free_3_groups(&group_3s));
		i++;
	}
	group_3s[i] = NULL;
	return (group_3s);
}

t_group	**create_groups(int n_groups, t_3_group **group_3s)
{
	t_group		**groups;
	int			i;

	if (group_3s == NULL)
		return (NULL);
	groups = malloc(4 * sizeof(t_group *));
	if (groups == NULL)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		groups[i] = create_group(n_groups / 12);
		if (groups[i] == NULL)
			return (free_groups(&groups));
		i++;
	}
	groups[i] = NULL;
	return (groups);
}

t_group	**get_groups(int n_groups)
{
	const t_3_group	**threes = create_3_groups(n_groups);
	const t_group	**groups = create_groups(n_groups, threes);
	const int		middle_ones_high = n_groups / 4 * 2 - 1;
	int				i;
	int				j;

	if (threes == NULL)
		return (NULL);
	i = 0;
	while (i < groups[0]->size)
	{
		groups[0]->ones[i] = middle_ones_high - i;
		groups[0]->threes[i] = threes[i];
		i++;
	}
	j = 0;
	while (j < groups[1]->size)
	{
		groups[1]->ones[j] = middle_ones_high - i;
		groups[1]->threes[j] = threes[i];
		i++;
		j++;
	}
	j = 0;
	while (j < groups[2]->size)
	{
		groups[2]->ones[j] = middle_ones_high - i;
		groups[2]->threes[j] = threes[i];
		j++;
		i++;
	}
	return ((t_group **)groups);
}

#include <stdio.h>

void	print_group(t_group *group)
{
	int i = 0;
	printf("size: %i\nones: ", group->size);
	while (i < group->size)
	{
		printf("[%i] ", group->ones[i]);
		i++;
	}
	printf("\nthrees: ");
	i = 0;
	while (i < group->size)
	{
		printf("[%i, %i, %i] ", group->threes[i]->low, group->threes[i]->middle, group->threes[i]->high);
		i++;
	}
	printf("\n");
}

int	in_group(int v, t_group *group)
{
	if (group->ones[0] == v)
		return (1);
	if (group->threes[0]->low == v)
		return (2);
	if (group->threes[0]->middle == v)
		return (3);
	if (group->threes[0]->high == v)
		return (4);
	return (0);
}

int	is_anywhere_in_group(int v, t_group *group)
{
	int	i;

	i = 0;
	while (i < group->size)
	{
		if (group->ones[0] == v
			|| group->threes[0]->low == v
			|| group->threes[0]->middle == v
			|| group->threes[0]->high == v)
			return (1);
	}
	return (0);
}

int	is_in_group(int v, t_group *group)
{
	int	i;

	i = 0;
	while (i < group->size)
	{
		if (group->ones[0] == v)
			return (1);
		if (group->threes[0]->low == v
			|| group->threes[0]->middle == v
			|| group->threes[0]->high == v)
			return (2);
	}
	return (0);
}

void	split_to_three(t_group **groups)
{
	int	i;

	i = 0;
	while (i < stack_size)
	{
		if (is_anywhere_in_group(top_value_group, groups[0]))
			exec("ra"); // rra?
		else
		{
			exec("pb");
			if (is_anywhere_in_group(top_value_group, groups[2]))
				exec("rb"); // rrb?
		}
		i++;
	}
}

void	resolve_group_value(t_group *group, int side, int value)
{
	const int	g = in_group(value, group);

	if (side == 0) // stack a
	{
		if (g == 0 || g == 1)
			exec("pb");
		if (g == 1)
			exec("rb"); // rrb?
		else if (g != 0)
			exec("ra"); // rra?
		return ;
	}
	if (g == 0 || g == 1)
		exec("pa");
	if (g == 1)
		exec("ra"); // rra?
	else if (g != 0)
		exec("rb"); // rrb?
}

void	resolve_group_step(t_group *group, int side)
{
	int	i;

	i = group->size * 4;
	while (i > 0)
	{
		if (side == 0)
			resolve_group_value(group, side, top_a_value_group);
		else
			resolve_group_value(group, side, top_b_value_group);
		i--;
	}
	group->size--;
}

void	resolve_group(t_group *group, int starting_side)
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
	while (group->size > 0)
	{
		resolve_group_step(group, side0);
		if (group->size > 0)
			resolve_group_step(group, side1);
	}
}

int	main(void)
{
	t_group	**groups = get_groups(12 * 3);
	if (groups == NULL)
		return (EXIT_FAILURE);
	int i = 0;
	while (groups[i] != NULL)
	{
		print_group(groups[i]);
		printf("\n");
		i++;
	}

	split_to_three(groups);
	resolve_group(groups[0], 0);
	resolve_group(groups[1], 1);
	resolve_group(groups[2], 1);
}
