/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 06:51:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/05 22:37:22 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCH64_H
# define ARCH64_H

# include "data.h"
# include "common.h"
# include "get_opts.h"

void		handler64(void *ptr, t_meta *meta);
void 		display64(t_meta *meta, void *ptr);

#endif
