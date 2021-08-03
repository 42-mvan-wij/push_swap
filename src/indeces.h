/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   indeces.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/29 16:33:54 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/03 14:57:01 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDECES_H
# define INDECES_H

# include "libft.h"

void	ps_transform_to_sorted_indeces(t_list **stack);
long	ps_lin_search(t_list *lst, void *val);

#endif
