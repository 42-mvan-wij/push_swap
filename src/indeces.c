/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   indeces.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 14:15:36 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/07 14:39:21 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static t_status	ps_insert_sorted(t_list **sorted, void *val)
{
	t_list	*cur;

	cur = *sorted;
	if (*sorted == NULL || (long)val < (long)cur->content)
	{
		if (ft_lstnew_front(val, sorted) == NULL)
			return (ps_set_error(E_MALLOC));
		return (OK);
	}
	while (cur->next != NULL && (long)val > (long)cur->next->content)
		cur = cur->next;
	if (ft_lstnew_front(val, &cur->next) == NULL)
		return (ps_set_error(E_MALLOC));
	return (OK);
}

long	ps_lin_search(t_list *lst, void *val)
{
	long	index;

	index = 0;
	while (lst != NULL)
	{
		if (lst->content == val)
			return (index);
		lst = lst->next;
		index++;
	}
	return (-1);
}

bool	ps_has_duplicates(t_list *sorted)
{
	void	*prev;

	prev = sorted->content;
	sorted = sorted->next;
	while (sorted != NULL)
	{
		if (sorted->content == prev)
			return (true);
		prev = sorted->content;
		sorted = sorted->next;
	}
	return (false);
}

t_status	ps_transform_to_sorted_indeces(t_list **stack)
{
	t_list	*sorted;
	t_list	*tmp_stack;

	sorted = NULL;
	tmp_stack = *stack;
	while (tmp_stack != NULL)
	{
		if (ps_insert_sorted(&sorted, tmp_stack->content) != OK)
		{
			ft_lstclear(&sorted, NULL);
			return (ps_get_error());
		}
		tmp_stack = tmp_stack->next;
	}
	if (ps_has_duplicates(sorted))
		return (ps_set_error(E_DUPLICATE));
	tmp_stack = *stack;
	while (tmp_stack != NULL)
	{
		tmp_stack->content = (void *)ps_lin_search(sorted, tmp_stack->content);
		tmp_stack = tmp_stack->next;
	}
	ft_lstclear(&sorted, NULL);
	return (OK);
}
