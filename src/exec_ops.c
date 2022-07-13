/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_ops.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/29 11:35:23 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/11 17:35:53 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "operations.h"
#include <unistd.h>

typedef int	(*t_exec_fn)(t_list **stack_a, t_list **stack_b);

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

void	ps_print_cmd(t_cmd cmd)
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

/**
 * ra => move top to bottom
 * rra => move bottom to top
 */
void	ps_exec_print2(t_cmd cmd, t_list **stack_a, t_list **stack_b)
{
	ps_exec(cmd, stack_a, stack_b);
	ps_print_cmd(cmd);
}

t_status	ps_exec_store(t_cmd cmd, t_data *data)
{
	ps_exec(cmd, &data->stack_a, &data->stack_b);
	if (ft_lstnew_front((void *)cmd, &data->ops) == NULL)
		return (ps_set_error(E_MALLOC));
	return (OK);
}

bool	either(t_cmd first, t_cmd second, t_cmd a, t_cmd b)
{
	return ((first == a && second == b) || (first == b && second == a));
}

t_cmd	ps_reduces_to(t_cmd first, t_cmd second)
{
	if ((first == SA && second == SA) || (first == SB && second == SB)
		|| (first == SS && second == SS) || either(first, second, PA, PB)
		|| either(first, second, RA, RRA) || either(first, second, RB, RRB)
		|| either(first, second, RR, RRR))
		return (NONE);
	if (either(first, second, SA, SB))
		return (SS);
	if (either(first, second, SA, SS))
		return (SB);
	if (either(first, second, SB, SS))
		return (SA);
	if (either(first, second, RA, RB))
		return (RR);
	if (either(first, second, RA, RRR))
		return (RRB);
	if (either(first, second, RB, RRR))
		return (RRA);
	if (either(first, second, RR, RRA))
		return (RB);
	if (either(first, second, RR, RRB))
		return (RA);
	if (either(first, second, RRA, RRB))
		return (RRR);
	return (NO_REDUCTION);
}

t_status	listify_reduction(t_list **reduction, int amount, int *replaced,
			t_cmd cmds[])
{
	int		i;

	*replaced = amount;
	*reduction = NULL;
	i = 0;
	while (cmds[i] != NONE)
	{
		if (ft_lstnew_front((void *)cmds[i], reduction) == NULL)
			return (ps_set_error(E_MALLOC));
		i++;
	}
	ft_lstreverse(reduction);
	return (OK);
}

t_status	ps_reduces_two(t_list *ops, int *replaced, t_list **reduction)
{
	t_cmd		reduction_with_two;
	t_cmd const	first = (t_cmd)ops->content;
	t_cmd const	second = (t_cmd)ops->next->content;
	t_cmd		third;

	reduction_with_two = ps_reduces_to(first, second);
	if (reduction_with_two != NO_REDUCTION)
		return (listify_reduction(reduction, 2, replaced,
				(t_cmd[]){reduction_with_two, NONE}));
	if (ops->next->next == NULL)
		return (listify_reduction(reduction, 0, replaced, (t_cmd[]){NONE}));
	third = (t_cmd)ops->next->next->content;
	if (first == PA && second == RA && third == SA)
		return (listify_reduction(reduction, 3, replaced,
				(t_cmd[]){SA, PA, RA, NONE}));
	if (first == PB && second == RB && third == SB)
		return (listify_reduction(reduction, 3, replaced,
				(t_cmd[]){SB, PB, RB, NONE}));
	return (listify_reduction(reduction, 0, replaced, (t_cmd[]){NONE}));
}

t_status	ps_reduce_ops_once(t_list **ops, bool *did_reduce)
{
	int		amount_replaced;
	t_list	*replacer;

	if (*ops == NULL || (*ops)->next == NULL)
		return (OK);
	if (ps_reduces_two(*ops, &amount_replaced, &replacer) != OK)
		return (ps_get_error());
	if (amount_replaced == 0)
		return (OK);
	while (amount_replaced > 0)
	{
		ft_lstnext(ops, NULL);
		amount_replaced--;
	}
	if (replacer != NULL)
		ft_lstinsert(ops, replacer, 0);
	*did_reduce = true;
	return (OK);
}

t_status	ps_reduce_ops(t_list **ops)
{
	t_list	**original;
	bool	did_reduce;
	bool	did_reduce_inner;

	original = ops;
	did_reduce = true;
	while (did_reduce)
	{
		did_reduce = false;
		ops = original;
		while (*ops != NULL)
		{
			did_reduce_inner = false;
			if (ps_reduce_ops_once(ops, &did_reduce_inner) != OK)
				return (ps_get_error());
			if (!did_reduce_inner)
				ops = &(*ops)->next;
			else
				did_reduce = true;
		}
	}
	return (OK);
}

void	ps_print_ops(t_list *ops)
{
	while (ops != NULL)
	{
		ps_print_cmd((t_cmd)ops->content);
		ops = ops->next;
	}
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
