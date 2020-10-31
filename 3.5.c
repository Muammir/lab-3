#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
  void sigint_handler(int sig);
  int num, buffer;
  char s[200];
  int pipefds[2];
//  pid_t pid = fork();


  if (signal(SIGINT, sigint_handler) == SIG_ERR){
     perror("signal");
     exit(1);
  }
//if(pid == 0){
  printf("Enter a number:\n");
  scanf("%d",&num);
//	}
  if (fgets(s, 200, stdin) == NULL)
      perror("gets");
//     exit(0);
  else
      printf("you number entered: %d\n", num);


  if(pipe(pipefds) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
//if(pid != 0){
  printf("Writing a number to pipe...\n");
  write(pipefds[1], &num, sizeof(num));
  printf("Done.\n\n");

  printf("Reading a number from pipe...\n");
  read(pipefds[0], &buffer, sizeof(buffer));
  printf("Done.\n\n");

  printf("Number from pipe: %d\n", buffer);
  int i, flag = 0;
    for (i = 2; i <= buffer / 2; ++i) {

        // condition for non-prime
        if (buffer % i == 0) {
            flag = 1;
            break;
        }
    }

    if (buffer == 1) {
        printf("1 is neither prime nor composite.");
    }
    else {
        if (flag == 0)
            printf("%d is a prime number.\n", buffer);
        else
            printf("%d is not a prime number.\n", buffer);
    }

//}
  return EXIT_SUCCESS;
}

void sigint_handler(int sig)
{
  printf("bye! \n");
}


