/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lars_util.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 14:59:41 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/23 14:59:41 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LARS_UTIL_H
# define LARS_UTIL_H

# include "libft.h"

typedef int	t_1_group;

typedef struct s_3_group
{
	t_1_group	low;
	t_1_group	middle;
	t_1_group	high;
	int			size;
}				t_3_group;

typedef struct s_group
{
	t_1_group	*ones;
	t_3_group	*threes;
	int			size;
	int			index;
	int			total_size;
	int			size_to_index;
}				t_group;

typedef struct s_lars_data
{
	t_group	*groups;
	t_list	**stack_a;
	t_list	**stack_b;
	int		total_size;
	int		num_groups;
}			t_lars_data;

t_group		create_group(int len);
t_3_group	*create_3_groups(int n_groups);
t_group		*free_groups(t_group *groups);
t_group		*create_groups(int n_groups, const t_3_group *group_3s);
t_group		*get_groups(int n_groups);
int			which_group(int n, t_lars_data *data);
int			group_size(int n, t_lars_data *data);
int			in_group(int v, t_group *group);
int			anywhere_in_group(int v, t_group *group);
void		resolve_group(t_group *group, int starting_side, t_lars_data *data);
void		sort_left(t_list **stack_a, t_lars_data *data);
void		sort_right(t_list **stack_a, t_list **stack_b, t_lars_data *data);

#endif
