#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

#define REG_CURRENT_PROCESS 101

#define SIGNEW 44

int8_t write_buf[1024];
int8_t read_buf[1024];

void sig_event_handler(int n, siginfo_t *info, void *unused)
{
    int check;
    if (n == SIGNEW) {
        check = info->si_int;
        printf ("Received signal from kernel : from device with fd =  %u\n", check);
    }
}

int main()
{
	char filename [64];

	int num_cpus = get_nprocs_conf();
	int num_online_cpus = get_nprocs();
	
	pid_t cpid;

	for (cpu = 0; cpu < num_cpus; cpu++) {
		sprintf(filename, "/dev/cpu/%d/ibs/op", cpu);
		fd[cpu] = open(filename, O_RDONLY | O_NONBLOCK);

		if (fd[cpu] < 0) {
                	fprintf(stderr, "Could not open %s\n", filename);
                	continue;
            	}

		ioctl(fd[cpu], SET_BUFFER_SIZE, buffer_size);
		//ioctl(fd[cpu], SET_POLL_SIZE, poll_size / sizeof(ibs_op_t));
		ioctl(fd[cpu], SET_MAX_CNT, op_cnt_max_to_set);
            	if (ioctl(fd[cpu], IBS_ENABLE)) {
                	fprintf(stderr, "IBS op enable failed on cpu %d\n", cpu);
                	continue;
            	}

            	//fds[count].events = POLLIN | POLLRDNORM;
            	nopfds++;
	}
	// fork child here
	/*cpid = fork();
        if (cpid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
        }*/

	for (int i = 0; i < nopfds; i++)
        	ioctl(fd[i], RESET_BUFFER);

	while (!waitpid(cpid, &i, WNOHANG));

	for (int i = 0; i < nopfds; i++) {
        	ioctl(fd[i], IBS_DISABLE);
        	close(fd[i]);
    	}

	// print results here

	/*int fd[4];
	char option;
	int number[4];
	struct sigaction act;

	printf("Welcome to the demo of character device driver...\n");

	sigemptyset(&act.sa_mask);
    	act.sa_flags = (SA_SIGINFO | SA_RESTART);
    	act.sa_sigaction = sig_event_handler;
    	sigaction(SIGNEW, &act, NULL);

	fd[0] = open("/dev/my_device0", O_RDWR);
	if(fd[0] < 0) {
		printf("Cannot open device file...\n");
		return 0;
	}

	if (ioctl(fd[0], REG_CURRENT_PROCESS,(int32_t*) &number[0])) {
        	printf("Failed\n");
        	close(fd[0]);
        	exit(1);
    	}


	fd[1] = open("/dev/my_device1", O_RDWR);
        if(fd[1] < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        if (ioctl(fd[1], REG_CURRENT_PROCESS,(int32_t*) &number[1])) {
                printf("Failed\n");
                close(fd[1]);
                exit(1);
        }

	fd[2] = open("/dev/my_device2", O_RDWR);
        if(fd[2] < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        if (ioctl(fd[2], REG_CURRENT_PROCESS,(int32_t*) &number[2])) {
                printf("Failed\n");
                close(fd[2]);
                exit(1);
        }

	fd[3] = open("/dev/my_device3", O_RDWR);
        if(fd[3] < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        if (ioctl(fd[3], REG_CURRENT_PROCESS,(int32_t*) &number[3])) {
                printf("Failed\n");
                close(fd[3]);
                exit(1);
        }

	while(1) {
		printf("*****please enter your option*****\n");
		printf("	1. Write	\n");
		printf("	2. Read		\n");
		printf("	3. Exit		\n");
		scanf("		%c",&option);
		printf("	your options = %c\n", option);

		switch(option) {
			case '1':
				printf("Enter the string to write into the driver:\n");
				scanf("	%[^\t\n]s", write_buf);
				printf("Data written....");
				write(fd[1], write_buf, strlen(write_buf)+1);
				printf("DONE...\n");
				break;
			case '2':
				printf("Data is Reading...");
				read(fd[1], read_buf, 1024);
				printf("Done...\n\n");
				printf("Data = %s\n\n", read_buf);
				break;
			case '3':
				close(fd[0]);
				close(fd[1]);
				close(fd[2]);
				close(fd[3]);
				exit(1);
				break;
			default:
				printf("Enter valid option = %c\n", option);
				break;
		}
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);*/
}
