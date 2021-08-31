/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   brute_force.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/31 14:13:06 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/31 16:32:24 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"
#include "utils.h"
#include <stdlib.h>

#include "TMP.h"
#include <stdio.h>

/**
 * @param pos 0 is least significant digit
 */
int	digit_at_pos_base(int num, int pos, int base)
{
	while (pos > 0)
	{
		num /= base;
		pos--;
	}
	return (num % base);
}

int	set_digit_base(int num, int pos, int digit, int base)
{
	const int	prev_digit = digit_at_pos_base(num, pos, base);
	int			diff;

	diff = prev_digit - digit;
	while (pos > 0)
	{
		diff *= base;
		pos--;
	}
	return (num - diff);
}

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

	data->ops = ft_memdup(ops, 11 * sizeof(char *));
	data->base = 11;
	i = 0;
	while (i < 11)
	{
		data->ops[i] = ft_strdup(data->ops[i]);
		i++;
	}
	data->node = 0;
	data->depth = 0;
	data->done = NULL;
}

int	brute_force_sort(t_list **stack_a, t_list **stack_b, int max_depth)
{
	t_bf_data	data;
	int			i;
	int			did_something;

	fill_data(&data);
	while (data.depth < max_depth)
	{
		i = 0;
		while (i < data.base)
		{
			did_something = ps_exec(data.ops[i], stack_a, stack_b);
			if (ps_is_sorted(*stack_a, *stack_b))
				return (1);
			if (did_something)
				ps_undo(data.ops[i], stack_a, stack_b);
			i++;
		}
		data.node++;
		if (digit_at_pos_base(data.node, data.depth, data.base) == 1)
		{
			do_setup_ops(&data, stack_a, stack_b);
			set_digit_base(data.node, data.depth, 0, data.base);
			data.depth++;
		}
	}
	return (0);
}
