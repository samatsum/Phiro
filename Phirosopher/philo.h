/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:21:17 by samatsum          #+#    #+#             */
/*   Updated: 2024/12/25 15:18:44 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

/* フォークの状態。簡略化のためClean/Dirty等は扱わず */
typedef struct s_fork {
	pthread_mutex_t	mutex;
	int				owner_id; /* フォークの所有者(哲学者ID) */
}	t_fork;

/* テーブル全体を管理する構造体 */
typedef struct s_table {
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	long long	start_time;
	t_fork		*forks;
	pthread_t	*threads;
}	t_table;

/* 哲学者毎の情報 */
typedef struct s_philo {
	int			id;
	int			meal_count;
	long long	last_meal;
	t_table		*table;
}	t_philo;

// まとめ
// Chandy/Misra法は「Forkの所有者」「Forkを利用したい哲学者」の間でリクエストと譲渡を行う分散制御方式です。
// 「自分が所有者になるまで待機し、使い終わったら隣に譲渡する」 という簡略版の実装です。
// スレッド間の衝突（データレース）を避けるためのmutexを適用し、fork所有者チェックと譲渡を行っています。
// 実際には死活監視スレッドや厳密なミリ秒判定などを加えて、哲学者が死なないように監視する処理を入れる必要があります。





long long	now_ms(void);
void		print_log(t_philo *p, char *msg);

#endif