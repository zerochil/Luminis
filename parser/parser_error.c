/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:51:23 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/14 14:48:34 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parser_error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (!error)
		return (false);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}
