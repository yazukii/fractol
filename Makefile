NAME = fractol

# -framework OpenGL -framework AppKit

LIBFT_PATH = libft
LIBFT = libft.a
MLX_PATH = mlx
MLX = libmlx.dylib

SRC_FILES = main.c \
			mlxfn.c \
			hooks.c \
			mandelbrot.c \
			colors.c  \
			julia.c \
			mouv.c
SRC_DIR = src/
SRC = ${addprefix ${SRC_DIR}, ${SRC_FILES}}
OBJ = ${SRC:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pg -g
AR = ar -rcs

%.o: %.c
	${CC} -c -Imlx -c $< -o $@

all: ${NAME}

libx:
	@MAKE -sC ${MLX_PATH}

libf:
	@MAKE -sC ${LIBFT_PATH}

${NAME}: libx libf ${OBJ}
	${CC} ${LIBFT_PATH}/${LIBFT} ${OBJ} ${MLX_PATH}/${MLX} -o ${NAME}

clean:
	rm -f ${OBJ}
	${MAKE} -C ${LIBFT_PATH} clean
	${MAKE} -C ${MLX_PATH} clean

fclean: clean
	rm -f ${NAME}
	${MAKE} -C ${LIBFT_PATH} fclean
	${MAKE} -C ${MLX_PATH} clean
	rm -f ${MLX_PATH}/${MLX}

re: fclean all

.PHONY: all clean flcean re