/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_ops.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/29 11:35:23 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/14 12:01:41 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "operations.h"
#include <unistd.h>

int	ps_exec(t_cmd cmd, t_list **stack_a, t_list **stack_b)
{
	if (cmd == SA)
		return (ps_swap(stack_a));
	if (cmd == SB)
		return (ps_swap(stack_b));
	if (cmd == SS)
		return (ps_swap2(stack_a, stack_b));
	if (cmd == PA)
		return (ps_push(stack_a, stack_b));
	if (cmd == PB)
		return (ps_push(stack_b, stack_a));
	if (cmd == RA)
		return (ps_rotate(stack_a));
	if (cmd == RB)
		return (ps_rotate(stack_b));
	if (cmd == RR)
		return (ps_rotate2(stack_a, stack_b));
	if (cmd == RRA)
		return (ps_reverse_rotate(stack_a));
	if (cmd == RRB)
		return (ps_reverse_rotate(stack_b));
	if (cmd == RRR)
		return (ps_reverse_rotate2(stack_a, stack_b));
	return (0);
}

/**
 * ra => move top to bottom
 * rra => move bottom to top
 */
t_status	ps_exec_store(t_cmd cmd, t_data *data)
{
	ps_exec(cmd, &data->stack_a, &data->stack_b);
	if (ft_lstnew_front((void *)cmd, &data->ops) == NULL)
		return (ps_set_error(E_MALLOC));
	return (OK);
}

void	ps_undo(t_cmd cmd, t_list **stack_a, t_list **stack_b)
{
	if (cmd == PB)
		ps_push(stack_a, stack_b);
	else if (cmd == PA)
		ps_push(stack_b, stack_a);
	else if (cmd == RA)
		ps_reverse_rotate(stack_a);
	else if (cmd == RB)
		ps_reverse_rotate(stack_b);
	else if (cmd == RR)
		ps_reverse_rotate2(stack_a, stack_b);
	else if (cmd == RRA)
		ps_rotate(stack_a);
	else if (cmd == RRB)
		ps_rotate(stack_b);
	else if (cmd == RRR)
		ps_rotate2(stack_a, stack_b);
	else if (cmd == SA)
		ps_swap(stack_a);
	else if (cmd == SB)
		ps_swap(stack_b);
	else if (cmd == SS)
		ps_swap2(stack_a, stack_b);
}

static void	ps_print_cmd(t_cmd cmd)
{
	static char	*strs[] = {
	[SA] = "sa",
	[SB] = "sb",
	[SS] = "ss",
	[PA] = "pa",
	[PB] = "pb",
	[RA] = "ra",
	[RB] = "rb",
	[RR] = "rr",
	[RRA] = "rra",
	[RRB] = "rrb",
	[RRR] = "rrr",
	};

	ft_putendl_fd(strs[cmd], STDOUT_FILENO);
}

void	ps_print_ops(t_list *ops)
{
	while (ops != NULL)
	{
		ps_print_cmd((t_cmd)ops->content);
		ops = ops->next;
	}
}
