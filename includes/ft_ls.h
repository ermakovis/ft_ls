/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:33:11 by tcase             #+#    #+#             */
/*   Updated: 2019/06/09 21:03:52 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include "libft.h"
# define FLAGS "AGRadflnrt1-"

# define FL_HID (1 << 0)
# define FL_COL (1 << 1)
# define FL_REC (1 << 2)
# define FL_ALL (1 << 3)
# define FL_DIR (1 << 4)
# define FL_SRT (1 << 5)
# define FL_LNG (1 << 6)
# define FL_IND (1 << 7)
# define FL_REV (1 << 8)
# define FL_STM (1 << 9)
# define FL_ONE (1 << 10)
# define FL_MIN (1 << 11)

# define FL_REGNL (1 << 28)
# define FL_HEADR (1 << 29)
# define FL_SEPAR (1 << 30)
# define FL_REGFL (1 << 31)

#define RED        "\x1b[31m"
#define GREEN      "\x1b[32m"
#define BOLD_GREEN "\x1b[32;1m"
#define YELLOW     "\x1b[33m"
#define BLUE       "\x1b[34m"
#define MAGENTA    "\x1b[35m"
#define BOLD_CYAN  "\x1b[96;1m"
#define RESET      "\x1b[0m"
//# define st_atime		st_atimespec.tv_sec
//# define st_atimensec	st_atimespec.tv_nsec
//# define st_mtime		st_mtimespec.tv_sec
//# define st_mtimensec	st_mtimespec.tv_nsec
//# define st_ctime		st_ctimespec.tv_sec
//# define st_ctimensec	st_ctimespec.tv_nsec

typedef struct dirent		t_dir;
typedef struct stat			t_stat;

typedef struct				s_ls
{
	char					path[PATH_MAX];
	char					name[NAME_MAX];
	mode_t					mode;
	nlink_t					link;
	uid_t					uid;
	gid_t					gid;
	off_t					size;
	blkcnt_t				blocks;
	time_t					atime;	
	time_t					mtime;	
	time_t					ctime;	
	struct s_ls				*next;
}							t_ls;

void						cleanup(t_ls **ls, int code, char *message);
void						parse_params(int *ac, char ***av, int *flags);
void						init_ls(int ac, char **av, t_ls **ls);
void						add_ls(char path[PATH_MAX], char name[NAME_MAX], t_ls **ls);
void						print_detail(t_ls *ls, int flags);
void						print_brief(t_ls *ls, int flags);
void						print_file(t_ls **ls, int flags);
void						sort_ls(t_ls **ls, int flags);


#endif
