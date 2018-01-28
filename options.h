/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 12:26:00 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/28 21:38:27 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include <libft.h>
# include "data.h"

void				init_options(t_opts *options);
int 				set_options(t_opts *options, char *str);

#endif