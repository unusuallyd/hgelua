all:
	g++ -o main.exe main.cpp lsprite.cpp lanimation.cpp lfont.cpp lhge.cpp lrect.cpp -I./hge/include -I./lua/include -L./hge/lib -L./lua/lib -lhge -llua -lhgehelp 

run:
	main.exe main.lua
