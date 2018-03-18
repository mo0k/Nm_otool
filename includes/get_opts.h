/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:31:35 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/16 00:14:10 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_OPTS_H
# define GET_OPTS_H

# include <stdio.h>
# include <string.h>
# include <stdint.h>

# define OPTIONS "prjx"
# define LEN_OPTIONS (strlen(OPTIONS) > 32) ? 32 : strlen(OPTIONS)
# define SET_BIT(opts, index) (opts |= (get_mask()[index] | opts))
# define GET_BIT(opts, index) (get_mask()[index] & opts)
# define BIT(index) (index - 1)

enum e_options
{
	SUCCESS,
	NO_ARGS,
	ARGS_NULL,
	NO_INDEX,
	NO_VAR_OPTION,
	BAD_OPTION
};

int			get_opts(int nb_arg, char **args, uint32_t *index, uint32_t *opts);
int			*get_mask();
int			print_error(int error);

#endif
