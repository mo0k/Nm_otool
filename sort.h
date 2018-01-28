/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 09:40:42 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/28 21:37:36 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <libft.h>
# include <mach-o/nlist.h>
# include "nm.h"

void			sort(t_list **lst, t_opts *opts, t_sfunc sfunc);
t_list			*sort_ascii(t_list *, t_list *);

#endif