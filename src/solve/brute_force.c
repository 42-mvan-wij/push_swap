/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   brute_force.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/31 14:13:06 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/06 18:17:29 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"
#include "utils.h"
#include "solve.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct s_bf_data {
	int		node;
	int		depth;
	t_list	*done;
	char	**ops;
	int		base;
}	t_bf_data;

void	do_setup_ops(t_bf_data *data, t_list **stack_a, t_list **stack_b)
{
	t_list	*next;
	int		p;
	int		d;

	while (data->done != NULL)
	{
		ps_undo(data->done->content, stack_a, stack_b);
		next = data->done->next;
		free(data->done);
		data->done = next;
	}
	p = 1;
	d = data->depth;
	while (d != 0)
	{
		p *= data->base;
		d--;
	}
	while (p != 0)
	{
		if (ps_exec(data->ops[(data->node / p) % data->base], stack_a, stack_b))
			ft_lstadd_front(&data->done,
				ft_lstnew(data->ops[(data->node / p) % data->base]));
		p /= data->base;
	}
}

void	fill_data(t_bf_data *data)
{
	const char	*ops[] = {"pa", "pb", "sa", "sb", "ss",
		"ra", "rb", "rr", "rra", "rrb", "rrr"};
	int			i;

	data->ops = malloc(11 * sizeof(char *));
	data->base = 11;
	i = 0;
	while (i < 11)
	{
		data->ops[i] = ft_strdup(ops[i]);
		i++;
	}
	data->node = 0;
	data->depth = 0;
	data->done = NULL;
}

int	can_sort(t_bf_data *data, t_list **stack_a, t_list **stack_b)
{
	int	i;
	int	did_something;

	i = 0;
	while (i < data->base)
	{
		did_something = ps_exec(data->ops[i], stack_a, stack_b);
		if (did_something && ps_is_sorted(*stack_a, *stack_b))
		{
			ft_lstadd_front(&data->done, ft_lstnew(data->ops[i]));
			return (1);
		}
		if (did_something)
			ps_undo(data->ops[i], stack_a, stack_b);
		i++;
	}
	return (0);
}

t_bf_data	get_brute_force_sort(t_list **stack_a, t_list **stack_b, int depth)
{
	t_bf_data	data;
	t_list		*next;

	fill_data(&data);
	while (data.depth < depth - 1)
	{
		if (can_sort(&data, stack_a, stack_b))
			return (data);
		do_setup_ops(&data, stack_a, stack_b);
		data.node++;
		if (ft_get_digit(data.node, data.depth + 1, data.base) == 1)
		{
			ft_set_digit(data.node, data.depth, 0, data.base);
			data.depth++;
		}
	}
	while (data.done != NULL)
	{
		ps_undo(data.done->content, stack_a, stack_b);
		next = data.done->next;
		free(data.done);
		data.done = next;
	}
	return (data);
}

int	brute_force_sort(t_list **stack_a, t_list **stack_b, int max_depth)
{
	t_bf_data	data;
	t_list		*ops;
	int			i;
	t_list		*item;

	data = get_brute_force_sort(stack_a, stack_b, max_depth);
	ops = data.done;
	if (ops != NULL)
	{
		i = ft_lstsize(ops);
		while (i > 0)
		{
			i--;
			item = ft_lstitem(ops, i);
			ft_putendl_fd(item->content, STDOUT_FILENO);
			ft_lstdelone(item, NULL);
		}
		ft_free_arr_n((void ***)&data.ops, data.base);
		return (1);
	}
	ft_free_arr_n((void ***)&data.ops, data.base);
	return (0);
}
