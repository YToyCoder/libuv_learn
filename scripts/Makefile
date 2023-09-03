libuvPath=D:/App/libuv
includePath=$(libuvPath)/include
out_dir = build

main:  main.c
	@if [ ! -d $(out_dir) ]; then mkdir build; fi
	gcc -I$(includePath) -L $(libuvPath) -luv -o $(out_dir)/main  main.c  $(libuvPath)/libuv.lib 
	@if  [ ! -e  $(out_dir)/libuv.dll ]; then cp $(libuvPath)/**.dll $(out_dir)/ ; fi

cli: client.c
	@if [ ! -d $(out_dir) ]; then mkdir build; fi
	gcc -I$(includePath) -L $(libuvPath) -luv -o $(out_dir)/client client.c  $(libuvPath)/libuv.lib 
	@if  [ ! -e  $(out_dir)/libuv.dll ]; then cp $(libuvPath)/**.dll $(out_dir)/ ; fi

run: main
	build/main.exe
# ifeq ($(wildcard $(out_dir)/libuv.dll),)
# 	cp $(libuvPath)/**.dll $(out_dir)/
# endif
# ifeq ($(wildcard $(out_dir)/*), )
# 	mkdir build
# endif
#gcc -I$(includePath) -o $(out_dir)/main  main.c  $(libuvPath)/libuv.lib 

clean: 
	rm -r build
#gcc -I$(includePath)  -L $(libuvPath) -l uv -o main  main.c 
#$(libuvPath)/libuv.lib
#gcc main.c  -I$(includePath) -L $(libuvPath) -l uv -o main 
