/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solve.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 01:49:29 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/06 18:19:35 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include "libft.h"

int		best_base(int len);
int		count_ops(int len, int base);
void	radix_sort(t_list **stack_a, t_list **stack_b, int base);
int		brute_force_sort(t_list **stack_a, t_list **stack_b, int max_depth);
void	bucket_sort(t_list **stack_a, t_list **stack_b);

#endif
