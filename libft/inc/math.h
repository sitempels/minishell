/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 04:36:40 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "libft.h"

int				ft_abs(int x);
double			ft_acos(double x);
double			ft_acot(double x);
double			ft_acsc(double x);
double			ft_asec(double x);
double			ft_asin(double x);
double			ft_atan(double x);
double			ft_atan2(double y, double x);
double			ft_cbrt(double x);
int				ft_ceil(double x);
double			ft_cos(double x);
double			ft_cosh(double x);
double			ft_cot(double x);
double			ft_csc(double x);
double			ft_exp(double x, int n);
double			ft_exp2(double x);
long			ft_fact(int n);
long			ft_fibon(int n);
int				ft_floor(double x);
double			ft_fract(double x);
int				ft_gcd(int a, int b);
double			ft_hypot(double x, double y);
int				ft_iterfact(int nb);
int				ft_iterpow(int nb, int power);
int				ft_lcm(int a, int b);
double			ft_ln(double x);
double			ft_log(double x);
double			ft_log2(double x);
double			ft_log10(double x);
int				ft_max(int a, int b);
double			ft_mean(int *arr, int n);
int				ft_min(int a, int b);
double			ft_pow2(double x);
unsigned long	ft_pow(unsigned long base, unsigned int exp);
int				*ft_range(int min, int max);
int				ft_recfact(int nb);
int				ft_recpow(int nb, int power);
int				ft_round(double x);
double			ft_sec(double x);
double			ft_sin(double x);
double			ft_sinc(double x);
double			ft_sinh(double x);
double			ft_sqrt(double n);
double			ft_tan(double x);
double			ft_tanh(double x);
double			ft_trunc(double x);
int				ft_math_ultrange(int **range, int min, int max);

#endif
