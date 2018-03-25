/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:25:16 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/22 22:37:47 by mo0k             ###   ########.fr       */
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

t_pfunc				get_printfunc_arch32(uint32_t options);
void				print_option_none_arch32(t_list *list);
void				print_option_j_arch32(t_list *list);
void				print_option_x_arch32(t_list *list);
void				print_option_m_arch32(t_list *list);

t_pfunc				get_printfunc_arch64(uint32_t options);
void				print_option_none_arch64(t_list *list);
void				print_option_j_arch64(t_list *list);
void				print_option_x_arch64(t_list *list);
void				print_option_m_arch64(t_list *list);


#endif
