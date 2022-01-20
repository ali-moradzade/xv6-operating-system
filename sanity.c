#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	int n = 0;
	if (argc!=2) {
		printf(1, "should get number(n) as parameter!\n");
		exit();
	}
	n = atoi(argv[1]);
	i = n; //unimportant
	int pd;
	for(i = 0; i < 3 * n; i++){
    	j = (j == 2) ? 0 : 3;
    	//printf(1, "%d\n", i);
    	pd = fork();
    	if (pd == 0){//child
    		switch(j){
    			case (0): //CPU‐bound process (CPU):
    			for( k =0; k< 100; k++){
    				for (j=0; j<1000000; j++){}
    			}
    			printf(1, "yo! 11\n");
    				break;
    			case (1): //short tasks based CPU‐bound process (S‐CPU):
    				for( k =0; k< 100; k++){
    					for (j=0; j<1000000; j++){}
    				}
    				//	yield();
    				break;

    			case (2):// I/O bound process (IO)
    				for( k =0; k< 100; k++){
    					sleep(1);
    				}
    				break;
    		}
    		exit();
    	}
    	if (pd>0){//father
    		continue;
    	}
    	printf(1, "panic! fork falild in sanity!\n");
    }

  exit();
}
