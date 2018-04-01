/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:11:03 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/01 16:27:52 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <ft_printf.h>

# define DEBUG 0

# define P_DEBUG(fmt) ((DEBUG) ? ft_printf(fmt) : 0) 
# define P_DEBUG_VARGS(fmt, ...) ((DEBUG) ? ft_printf(fmt, __VA_ARGS__) : 0) 

#endif