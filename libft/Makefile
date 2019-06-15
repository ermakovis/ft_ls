NAME = libft.a

INC = -I ./includes/

FLAGS = -Wall -Wextra -Werror

SRCS_NAME=ft_abs.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
		 ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
		 ft_lstnew.c ft_memalloc.c ft_memccpy.c \
		 ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
		 ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
		 ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
		 ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c \
		 ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
		 ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
		 ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
		 ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
		 ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
		 ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
		 ft_toupper.c ft_lstdelone.c ft_lstdel.c ft_strchrlen.c\
		 ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstsize.c \
		 ft_strclen.c ft_nbrlen.c ft_strtoupper.c ft_swap.c \
		 ft_power.c get_next_line.c ft_strndup.c ft_max.c ft_min.c\
		 ft_printf.c ft_parse_format.c ft_print_string.c ft_print_digit.c \
		 ft_print_unsigned_number.c ft_print_signed_number.c \
		 ft_print_float.c ft_print_cleanup.c ft_print_wchar.c

SRCS_PATH = src/
OBJ_PATH  = obj/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME):$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o:$(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
