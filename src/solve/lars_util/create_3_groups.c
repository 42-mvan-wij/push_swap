/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_3_groups.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 17:30:37 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/13 17:32:00 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lars_util.h"
#include <stdlib.h>

t_status	create_3_groups(int n_groups, t_3_group **group_3s)
{
	int	i;

	*group_3s = malloc((n_groups / 4) * sizeof(t_3_group));
	if (*group_3s == NULL)
		return (ps_set_error(E_MALLOC));
	i = 0;
	while (i < n_groups / 4)
	{
		(*group_3s)[n_groups / 4 - 1 - i].low = i;
		(*group_3s)[n_groups / 4 - 1 - i].middle = \
			n_groups - n_groups / 4 - 1 - i;
		(*group_3s)[n_groups / 4 - 1 - i].high = n_groups - i - 1;
		i++;
	}
	return (OK);
}
