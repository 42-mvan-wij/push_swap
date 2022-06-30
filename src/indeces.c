/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   indeces.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 14:15:36 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/06/23 13:42:27 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static void	ps_insert_sorted(t_list **sorted, void *val)
{
	t_list	*cur;

	cur = *sorted;
	if (*sorted == NULL || (long)val < (long)cur->content)
	{
		ft_lstadd_front(sorted, ps_protect(ft_lstnew(val)));
		return ;
	}
	while (cur->next != NULL && (long)val > (long)cur->next->content)
		cur = cur->next;
	ft_lstadd_front(&cur->next, ps_protect(ft_lstnew(val)));
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
	ps_protect(NULL);
	return (-1);
}

void	ps_error_if_duplicates(t_list *sorted)
{
	void	*prev;

	prev = sorted->content;
	sorted = sorted->next;
	while (sorted != NULL)
	{
		if (sorted->content == prev)
			ps_protect(NULL);
		prev = sorted->content;
		sorted = sorted->next;
	}
}

void	ps_transform_to_sorted_indeces(t_list **stack)
{
	t_list	*sorted;
	t_list	*tmp_stack;

	sorted = NULL;
	tmp_stack = *stack;
	while (tmp_stack != NULL)
	{
		ps_insert_sorted(&sorted, tmp_stack->content);
		tmp_stack = tmp_stack->next;
	}
	ps_error_if_duplicates(sorted);
	tmp_stack = *stack;
	while (tmp_stack != NULL)
	{
		tmp_stack->content = (void *)ps_lin_search(sorted, tmp_stack->content);
		tmp_stack = tmp_stack->next;
	}
	ft_lstclear(&sorted, NULL);
}
