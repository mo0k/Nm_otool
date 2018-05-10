/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 09:40:42 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 12:04:39 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <mach-o/nlist.h>
# include <libft.h>
# include <get_opts.h>
# include <data.h>


void			sort(t_list **lst, uint32_t opts, t_sfunc sfunc);
t_list			*sort_ascii(t_list *, t_list *);
t_sfunc			get_sortfunc(uint32_t options);


#endif