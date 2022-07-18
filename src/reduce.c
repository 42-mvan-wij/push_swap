/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reduce.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 11:57:41 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/14 12:14:46 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"
#include "utils.h"

static t_status	listify_reduction(t_list **reduction, int amount, int *replaced,
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

static t_cmd	ps_reduce_2(t_cmd first, t_cmd second)
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

static t_status	ps_reduce(t_list *ops, int *replaced, t_list **reduction)
{
	t_cmd		reduction_with_two;
	t_cmd const	first = (t_cmd)ops->content;
	t_cmd const	second = (t_cmd)ops->next->content;
	t_cmd		third;

	reduction_with_two = ps_reduce_2(first, second);
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

static t_status	ps_reduce_ops_once(t_list **ops, bool *did_reduce)
{
	int		amount_replaced;
	t_list	*replacer;

	if (*ops == NULL || (*ops)->next == NULL)
		return (OK);
	if (ps_reduce(*ops, &amount_replaced, &replacer) != OK)
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
