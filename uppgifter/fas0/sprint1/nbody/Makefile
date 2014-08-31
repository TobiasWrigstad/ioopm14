# Make animate to show a nice window
# Make starsim to only benchmark

starsim:
	gcc -std=c99 main.c -o main  -lm 
animate:
	gcc -std=c99 -DANIMATE main.c -o main -lm -lX11
run:
	./main
