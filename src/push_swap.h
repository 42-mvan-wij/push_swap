/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 14:46:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/03 14:57:23 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

void	ps_transform_to_sorted_indeces(t_list **stack);
void	create_chunks(t_list **stack_a, t_list **stack_b,
			int s_len, int c_size);

#endif
