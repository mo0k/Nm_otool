/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 12:43:13 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/28 21:46:18 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

void			init_options(t_opts *options)
{
	if (!options)
		return ;
	ft_memset(options, 0, sizeof(t_opts));
	options->ascii = 1;

}

int 						set_options(t_opts *options, char *str)
{
	if (!str || !*str || !options)
		return (ERROR_ARGS);
	while (*str)
	{
		//printf("*str:'%c'\n", *str);
		if (*str == 'p')
		{
			options->nosort = 1;
			options->ascii = 0;
			options->reverse = 0;
		}
		else if (*str == 'r')
		{
			if (options->nosort == 0)
				options->reverse = 1;
		} 
		else if (*str == 'x')
		{
			if (options->just_symbol_names == 0)
				options->hexa = 1;
		}
		else if (*str == 'j')
		{
			options->just_symbol_names = 1;
			options->hexa = 0;
		}
		else
			return (ERROR_ARGS);
		++str;
	}
	return (0);
}