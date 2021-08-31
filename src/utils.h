/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 17:41:46 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/31 14:09:10 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

void	*ps_protect(void *ptr);
int		ps_atoi(char *num);
t_list	*ps_init_stack(int size, char **nums);
int		ps_is_sorted(t_list *stack_a, t_list *stack_b);

#endif
