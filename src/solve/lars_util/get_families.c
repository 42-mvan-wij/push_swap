/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_families.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 14:31:38 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/13 17:31:22 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lars_util.h"
#include <stdlib.h>

t_status	create_family(int len, t_family *family)
{
	family->ones = malloc(len * sizeof(t_1_group));
	if (family->ones == NULL)
		return (ps_set_error(E_MALLOC));
	family->threes = malloc(len * sizeof(t_3_group));
	if (family->threes == NULL)
	{
		free(family->ones);
		family->ones = NULL;
		return (ps_set_error(E_MALLOC));
	}
	family->size = len;
	family->index = 0;
	family->total_size = 0;
	family->size_to_index = 0;
	return (OK);
}

void	free_families(t_family families[3], int amount)
{
	while (amount > 0)
	{
		--amount;
		free(families[amount].ones);
		free(families[amount].threes);
	}
}

t_status	create_families(int n_groups, t_family families[3])
{
	int			i;

	i = 0;
	while (i < 3)
	{
		if (create_family(n_groups / 12, &families[i]) != OK)
			return (ps_get_error());
		i++;
	}
	return (OK);
}

void	fill_families(int n_groups, t_family families[3], t_3_group *threes)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (k < 3)
	{
		j = 0;
		while (j < families[k].size)
		{
			families[k].ones[j] = n_groups / 4 * 2 - 1 - i;
			families[k].threes[j] = threes[i];
			i++;
			j++;
		}
		k++;
	}
}

t_status	get_families(int n_groups, t_family families[3])
{
	t_3_group	*threes;

	if (create_3_groups(n_groups, &threes) != OK)
		return (ps_get_error());
	if (create_families(n_groups, families) != OK)
	{
		free(threes);
		return (ps_get_error());
	}
	fill_families(n_groups, families, threes);
	free(threes);
	return (OK);
}
