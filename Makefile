TARGET=huge-problem

$(TARGET): huge-problem.c drawcontext.c canvas.c commands.c
	gcc -Wall -o $(TARGET) huge-problem.c drawcontext.c canvas.c commands.c -I .

clean:
	rm $(TARGET)
