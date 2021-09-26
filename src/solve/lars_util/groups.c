/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   groups.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 14:31:38 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/23 14:31:38 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lars_util.h"
#include <stdlib.h>

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
	t_group	*groups;
	int		i;

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
	free((void *)threes);
	return ((t_group *) groups);
}
