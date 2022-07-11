/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lars_util.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 14:59:41 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/11 17:22:51 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LARS_UTIL_H
# define LARS_UTIL_H

# include "libft.h"
# include "utils.h"

typedef enum e_group_type
{
	ONES,
	THREES_LOW,
	THREES_MIDDLE,
	THREES_HIGH,
	OTHER
}	t_group_type;

typedef int	t_1_group;

typedef struct s_3_group
{
	t_1_group	low;
	t_1_group	middle;
	t_1_group	high;
	int			size;
}				t_3_group;

typedef struct s_family
{
	t_1_group	*ones;
	t_3_group	*threes;
	int			size;
	int			index;
	int			total_size;
	int			size_to_index;
}				t_family;

typedef enum e_3_order
{
	O_123,
	O_132,
	O_213,
	O_231,
	O_312,
	O_321,
}	t_3_order;

typedef struct s_lars_data
{
	t_family	families[3];
	t_list		**stack_a;
	t_list		**stack_b;
	t_list		**ops;
	int			total_size;
	int			num_groups;
}			t_lars_data;

t_status		create_family(int len, t_family *family);
t_status		create_3_groups(int n_groups, t_3_group **group_3s);
void			free_families(t_family families[3], int amount);
t_status		create_families(int n_groups, t_family families[3]);
t_status		get_families(int n_groups, t_family families[3]);
int				which_group(int n, t_lars_data *data);
int				group_size(int n, t_lars_data *data);
t_group_type	in_group(int v, t_family *group);
int				anywhere_in_family(int v, t_family *group);
t_status		resolve_family(t_family *group, int starting_side,
					t_lars_data *data);
t_status		sort_left(t_list **stack_a, t_lars_data *data);
t_status		sort_right(t_list **stack_b, t_lars_data *data);

#endif
