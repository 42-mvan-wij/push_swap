/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnext.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 15:33:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/13 15:33:25 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstnext(t_list **lst, void (*del)(void *content))
{
	t_list	*tmp;

	tmp = (*lst)->next;
	ft_lstdelone(*lst, del);
	*lst = tmp;
}
