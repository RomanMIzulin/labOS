#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
int interrupt_counter = 0;     // counter of keyboard interruptions

void interrupt_handler()       // handler of keyboard interrupt signal
{
    interrupt_counter++;       // increase the counter of keyboard interruptions
    if (interrupt_counter % 2) // do it every odd counter value
    {
        printf("\n");          // beautifier

        if (fork() == 0)       // execute action in parallel process
        {
            // child process
            // this command outputs all non-binary files in current directory
            execl("/usr/bin/find",  "find",  ".", "-maxdepth", "1", "-type", "f", "-exec", "grep", "-Iq", ".", "{}", "\;", "-print", 0);
        }
        else
        {
            // wait until child process die
            wait();
        }

    }
}

int main(){
	struct sigaction keyboard_interrupt;
        keyboard_interrupt.sa_handler = interrupt_handler; // we make our function the handler of KeyboardInterrupt handler
        sigemptyset(&keyboard_interrupt.sa_mask);          // no additional blocking signals
        sigprocmask(0,0,&keyboard_interrupt.sa_mask);      // save current mask
        keyboard_interrupt.sa_flags = 0;                   // not to perform special actions
        sigaction(SIGINT, &keyboard_interrupt, 0);         // we set our handler

	const char *fileToWrite ="out.txt";
	const char *filename ="text.txt";
	printf("%d ",access(filename,0));
	int count = 0;
	if(!(access(filename,0)||access(fileToWrite,0))){
		if(!((access(filename,4) && access(filename,3))||(access(fileToWrite,2)&&access(fileToWrite,4)))){
			
			printf("here1");
			int fToWrite = open(fileToWrite,O_WRONLY);
			int fFromRead = open(filename,O_RDONLY);
			char arr[512];
			while(read(fFromRead,arr,512)>0){
				write(fToWrite,arr,512);
				count+=1;
			}
			close(fToWrite);
			close(fFromRead);
		}
	}
	if(!(access(filename,0)||(access(filename,4)&& access(filename,3))||(!access(fileToWrite,0)))){
		printf("here");
		int fToWrite = open(fileToWrite,O_CREAT	| O_WRONLY);
		int fFromRead = open(filename,O_RDONLY);
		char arr[512];
		while(read(fFromRead,arr,512)>0){
			write(fToWrite,arr,512);
			count+=1;
		}
		close(fToWrite);
		close(fFromRead);
	}
printf("\n %d blocks wrote in %s. %d bytes wrote at all.",count, fileToWrite,count*512);
}
