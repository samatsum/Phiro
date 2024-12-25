/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:29:40 by samatsum          #+#    #+#             */
/*   Updated: 2024/12/25 15:16:59 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_ms(void);
void		print_log(t_philo *p, char *msg);

/* === 時間計測用関数 === */
long long	now_ms(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (long long)(tv.tv_sec)*1000 + (tv.tv_usec / 1000);
	return (ms);
}

/* === ログ出力用関数(混ざらないように排他制御すべきだが簡略) === */
void	print_log(t_philo *p, char *msg)
{
	printf("%lld %d %s\n", now_ms() - p->table->start_time, p->id, msg);
}