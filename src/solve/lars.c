/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lars.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 17:49:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/08 16:23:09 by mvan-wij      ########   odam.nl         */
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
	group->ones[len] = NULL;
	group->threes = malloc((len + 1) * sizeof(t_3_group *));
	group->threes[len] = NULL;
	group->size = len * 4;
	return (group);
}

t_group	*free_group(t_group **group)
{
	if (*group == NULL)
		return ;
	if ((*group)->ones != NULL)
		free((*group)->ones);
	if ((*group)->threes != NULL)
		free_3_groups(&(*group)->threes);
	free(*group);
	*group = NULL;
	return (NULL);
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
		if (group_3s[i] == NULL)
			return (free_3_groups(group_3s));
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
	groups = malloc(3 * sizeof(t_group **));
	if (groups == NULL)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		groups[i] = create_group(n_groups / 3);
		if (groups[i] == NULL)
			return (free_groups(groups));
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
	while (groups[0]->ones[i] != NULL)
	{
		groups[0]->ones[i] = middle_ones_high - i;
		groups[0]->threes[0] = threes[i];
		i++;
	}
	j = 0;
	while (groups[1]->ones[j] != NULL)
	{
		groups[0]->ones[i] = middle_ones_high - i;
		groups[0]->threes[0] = threes[i];
		i++;
		j++;
	}
	while (j > 0)
	{
		j--;
		groups[0]->ones[i] = middle_ones_high - i;
		groups[0]->threes[0] = threes[i];
		i++;
	}
	return (groups);
}
