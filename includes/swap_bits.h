/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 21:57:31 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/28 22:02:24 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_BITS_H
# define SWAP_BITS_H

# define SWAP16(f, v) ((f) ? swap_uint16(v) : v)
# define SWAP32(f, v) ((f) ? swap_uint32(v) : v)
# define SWAP64(f, v) ((f) ? swap_uint64(v) : v)

uint16_t	swap_uint16(uint16_t value);
uint32_t	swap_uint32(uint32_t value);
uint64_t	swap_uint64(uint64_t value);

#endif