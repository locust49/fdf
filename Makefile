PROJECT =	fdf
CMPL	=	gcc
FLGS	=	-Wall -Wextra -Werror

NAME	=	fdf
LIBR	=	libft
LBIN	=	libft/libft.a

SRCS	=	draw.c draw_tools.c free_tools.c fdf.c list_maps.c parsing.c \
			projections.c settings_tools.c initial_tools.c hex_to_decimal.c window_fdf.c
HDRS	=	-I fdf.h

all: $(NAME)

$(NAME):
	@make -C $(LIBR)
	@$(CMPL) -lmlx -framework OpenGl -framework AppKit $(FLGS) $(SRCS) $(HDRS) $(LBIN) -o $(NAME)
	@echo "$(NAME) created and ready to show you how the world looks like."

clean:
	@make clean -C $(LIBR)
	@echo clean

fclean: clean
	@make fclean -C $(LIBR)
	@rm -f $(NAME)
	@echo fclean

re: fclean all