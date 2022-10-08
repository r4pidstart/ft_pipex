all: fclean
	make -C push_swap all
fclean:
	make -C push_swap fclean
bonus:
	make -C push_swap bonus