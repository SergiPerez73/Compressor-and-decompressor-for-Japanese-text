OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
all: compressor decompressor 


compresor: compresor.cc 
	g++ -o compresor compresor.cc $(OPCIONS)

descompressor: decompressor.cc
	g++ -o decompresor decompressor.cc $(OPCIONS)

clear:
	rm -f *.o
	rm -f compressor
	rm -f decompressor
