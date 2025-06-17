##
## EPITECH PROJECT, 2025
## make
## File description:
## make
##

all:
	mkdir -p build
	cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
	cmake --build build --target all

clean:
	rm -rf build

fclean: clean
	rm -rf plugins/*

re: fclean all