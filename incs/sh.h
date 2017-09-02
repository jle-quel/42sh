/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 21:07:41 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/30 21:07:00 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

#include <libft.h>
#include <unistd.h>
#include <struct.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <define.h>
#include <termios.h>
#include <fcntl.h>
#include <curses.h>
#include <term.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>

//DEBUG
int fdb;

int					shell(void);
void				insert_one_line(void);

/*
**				FUNCTION READ && PRINT AND RETURN A STRUCT
*/

t_read				*read_stdin(void);
int 				prompt(unsigned char flags, char *str);
t_cmd				*create_element(char c);
int					print_struct(t_read *read_std);
int					my_put(int c);
t_read				*init_struct_for_read(void);
void				make_list_hist(t_read *read_std);
t_cmd				*first_cmd(t_cmd *cmd, int history);
t_cmd				*gbl_save_read(t_cmd *read_std);
int					print_list(int to_select, t_cmd *cmd, t_cmd *stop, t_read *read_std);
void				restore_cursor_(t_cursor cur);
int					check_cmd(t_read **read_std);

/*
**				HASH FUNCTION
*/

unsigned int		hash_value(char *str);
t_hash				*hash_board(void);
char				*search_path(char *binary);
void				add_hash(char *bin, char *path);

/*
**				FUNCTION FOR COMPLETION
*/

int					place_cursor(t_read **read_std, int t);
int	        		check_word(t_cmd *cmd);
int			        len_cmd(t_cmd **cmd);
int					print_tab(t_read **read_std);
int         	    my_togo(int li, int co);
int					my_tobackto(int li, int co);
void				back_completion(t_read **read_std);
void				add_little_char(unsigned char type);
void				to_up(t_read **read_std);
int					to_down(t_read **read_std);
void				init_completion(t_read **read_std);
void				complete_path(t_read **read_std, t_path f);
void				complete_binary(t_read **read_std);
void				continue_completion(t_read **read_std);
void				complete_command(t_read **read_std);
int					print_tab(t_read **read_std);
int					print_element(t_file *file, int color);
void				create_comp(t_read **read_std, t_path f);
void				color_completion(unsigned char type, int color);
void				init_files(t_file **file, char *name, unsigned char type, int index);
void				completion(t_read **read_std);
void				update_index(t_read **read_std, int i);
int		        	init_tab_(t_tab *tab_, int li);

/*
**				POINTER ON FUNCTION FOR READ
*/

int					key_print_(t_read **read_std, char c);
int		        	is_token(char c);
int					key_tab(t_read **read_std);
void				finish_read_std(t_read **read_std);
int					key_enter_(t_read **read_std);
int					key_interrupt(t_read **read_std);
int					key_clear_(t_read **read_std);
int					key_eof(t_read **read_std);
int					key_arrow_left(t_read **read_std);
int					key_arrow_right(t_read **read_std);
int					key_arrow_up(t_read **read_std);
int					key_arrow_down(t_read **read_std);
int					key_home_(t_read **read_std);
int					key_del(t_read **read_std);
int					key_shift_up(t_read **read);
int					key_shift_down(t_read **read);
int					key_shift_left(t_read **read);
int					key_shift_right(t_read **read);
int					key_end_(t_read **read_std);
int					key_delete_here(t_read **read_std);

/*
**				ENVIRONEMENT FUNCTION
*/

t_env				*gbl_save_env(unsigned short flags, t_env *env);
void				init_env(void);
void				split_env(char *env);
void				add_list_env(char *name, char *value);
char				*my_getenv(char *str);

/*
**				HISTORY FUNCTION
*/

void		        reset_history(void);
void				init_history(void);
void				copy_cmd(t_read **read_std, t_cmd *cpy);
t_hist				*gbl_save_history(t_hist *hist);
void				make_list_hist(t_read *read_std);
void				previous_history(t_read **read_std);
void				next_history(t_read **read_std);

/*
**				SIGNAL FUNCTION
*/

void				init_signal(void);
void				reset_signal(void);

/*
**				TERMIOS FUNCTION
*/

struct termios		keep_term_struct(unsigned short flags, struct termios *term);
void				set_termios(unsigned short flags);
int					init_fd(void);
int					init_term(void);

/*
**				FUNCTION MEMDEL STRUCTURE
*/

int					memdel_completion(t_completion **comp);
int					memdel_read(t_read **read_std);
int					memdel_cmd(t_cmd **cmd);

/*
**				ERROR FUNCTION
*/

int					bip(void);

#endif
