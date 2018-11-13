CFLAGS=-Wall -g

LDFLAGS=-lm

Project_2_bkhuu_207: Project_2_bkhuu_207.c sms.c
	gcc -o Project_2_bkhuu_207 Project_2_bkhuu_207.c sms.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f Project_2_bkhuu_207
