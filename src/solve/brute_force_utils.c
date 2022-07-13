/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 17:24:59 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/13 17:25:04 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	power(int base, int pow)
{
	int	ans;

	ans = 1;
	while (pow != 0)
	{
		pow--;
		ans *= base;
	}
	return (ans);
}
