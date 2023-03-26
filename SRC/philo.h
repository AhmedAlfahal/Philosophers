/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalfahal <aalfahal@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:26:06 by aalfahal          #+#    #+#             */
/*   Updated: 2023/03/26 05:59:25 by aalfahal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdlib.h>
# include<string.h>
# include<stdio.h>
# include<unistd.h>
# include<pthread.h>
# include<sys/time.h>
# include <limits.h>

typedef struct s_f
{
	int				p_num;
	int				dead;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	int				*forks;
}		t_f;

typedef struct s_m
{
	int			left_fork;
	int			right_fork;
	long long	last_time;
	long long	time;
	int			td;
	int			te;
	int			ts;
	int			id;
	int			meals;
	int			eaten_meals;
	pthread_t	thread;
	t_f			*fork;
}				t_m;

typedef struct s_p
{
	int				p_num;
	int				p_meals;
	int				p_td;
	int				p_te;
	int				p_ts;
	int				exit;
	int				t_count;
	long long		time;
	t_m				*thread;
	t_f				*fork;
}					t_p;

/*********************************--Parsing--*****************************/

void		check_nums(t_p *p, char **av, int ac);

/*********************************--Time--********************************/

long long	get_time(void);
void		we_sleep(long long current_time, int val);

/*********************************--Philo Life--**************************/

void		*eat(void *p);
void		grep_fork(t_m *p, int left, int right);
void		take_forks(t_m *p);
void		put_fork(t_m *p);
void		*printing(t_m *p, int msg);
void		*check_dead(t_m *p);
int			check_meals(t_p *p);
int			c_dead(t_m *p);

#endif