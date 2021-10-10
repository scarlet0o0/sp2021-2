#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
	struct utsname uts;
	char str[999] = "This is a";
	bool s_t=false, n_t=false, v_t=false, m_t=false;
	if(uname(&uts) == -1){
		perror("uname");
		exit(1);
	}
	
	char *s = uts.sysname;
	char *n = uts.nodename;
	char *v = uts.release;
	char *m = uts.machine;

	if(argc == 1){
		printf("-s : print OS name\n");
		printf("-n : print nodename (hostname)\n");
		printf("-v : print release\n");
		printf("-m : print machine info\n");
	}
	else{
		for (int i =1; i<argc; i++){
			if(strcmp(argv[i],"-s")==0)
				s_t = true;
			if(strcmp(argv[i],"-n")==0)
				n_t = true;
			if(strcmp(argv[i],"-v")==0)
				v_t = true;
			if(strcmp(argv[i],"-m")==0)
				m_t = true;
		}

		if(m_t){
			strcat(str," ");
			strcat(str,m);
		}
		if(v_t){
			strcat(str," ");
			strcat(str,v);
		}
		if(s_t){
			strcat(str," ");
			strcat(str,s);
			strcat(str," machine"); 
		}
		if(n_t){
			strcat(str," named ");
			strcat(str,n);
		}

		printf("%s.\n",str);
	}
	
	return 0;
}
