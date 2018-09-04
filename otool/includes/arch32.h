/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch32.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 06:51:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 23:17:45 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCH32_H
# define ARCH32_H

# include <mach-o/fat.h>
# include "data.h"
# include "common.h"
# include "get_opts.h"
# include "otool.h"

void		handler32(void *ptr, t_meta *meta);
void		handler_fat32(void *ptr, t_meta *meta);
void		display32(t_meta *meta, void *ptr);

#endif