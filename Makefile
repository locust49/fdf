PROJECT =	fdf
CMPL	=	gcc
FLGS	=	-Wall -Wextra -Werror

NAME	=	fdf
LIBR	=	libft
LBIN	=	libft/libft.a

SRCS	=	 clean_parse.c tools.c init.c 
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