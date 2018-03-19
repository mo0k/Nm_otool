/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:25:16 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 21:14:58 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <mach-o/nlist.h>
# include <libft.h>
# include <symbol.h>
# include <common.h>
# include <data.h>
# include <get_opts.h> 

t_pfunc				get_printfunc(uint32_t options);
void				print_option_none(t_list *list);
void				print_option_j(t_list *list);
void				print_option_x(t_list *list);
void				print_option_m(t_list *list);

#endif
