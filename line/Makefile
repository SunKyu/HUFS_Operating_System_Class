#
# Makfile
#

CC= arm-linux-gnueabi-gcc
FLAGS= -std=c99

OBJS= main.o uart_api.o robot_protocol.o keyboard.o stack.o Node.o dijkstra.o
SOURCE= main.c uart_api robot_protocol keyboard stack Node dijkstra


all: LineTracer_exam

LineTracer_exam: $(OBJS)
	$(CC)  -o $@ $^

$(SOURCE):
	$(CC) -c -std=c99 $@

clean:
	rm -f $(OBJS) LineTracer_exam
