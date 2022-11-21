NAME = simulator

CC = gcc
SRCS = simulator.c execute.c
OBJS = $(SRCS:.c=.o)

RESULT = Optimal_result.txt FIFO_result.txt LIFO_result.txt LRU_result.txt LFU_result.txt SC_result.txt ESC_result.txt

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS)
	@echo "\033[32m[$(NAME)]: compiled\033[0m"

%.o: %.c
	$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@rm -rf $(NAME)
	@rm -rf $(RESULT)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "clean"

re: clean all

.PHONY: all clean re