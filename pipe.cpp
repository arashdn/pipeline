#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <iostream>

#define SLEEP_TIME 5
#define BUFFER_SIZE 500

using namespace std;

int main()
{
	int pipefd[2];
	int pid1 = 0, pid2 = 0, pid3 = 0;
	char buffer [BUFFER_SIZE];
	//memset(buffer,'\0',sizeof(buffer)); //no need , first write will set it up

	pipe(pipefd);



	string st = "Arash";
	cout <<"--- PID 0 ---\n";
	cout <<"Write: "<<st<<"\n-------------\n";
	write(pipefd[1],st.c_str(),st.length());
	sleep(SLEEP_TIME);

	pid1 = fork();
	if (pid1 < 0)
	{
		cout << "Fork Error";
		return 0;
	}
	//Child process 1.
	if (pid1 == 0)
	{
		read(pipefd[0],buffer,BUFFER_SIZE);
		string s = buffer;
		cout <<"--- PID 1 ---\n";
		cout <<"Read: "<<s<<endl;
		s = s + " Dargahi";
		write(pipefd[1],s.c_str(),s.length());
		cout <<"Write: "<<s <<"\n-------------\n";
		sleep(SLEEP_TIME);
	}
	waitpid(pid1, NULL, 0);


	pid2 = fork();
	if (pid2 < 0)
	{
		cout << "Fork Error";
		return 0;
	}
	//Child process 1.
	if (pid2 == 0)
	{
		read(pipefd[0],buffer,BUFFER_SIZE);
		string s = buffer;
		cout <<"--- PID 2 ---\n";
		cout <<"Read: "<<s<<endl;
		s = s + " Nobari";
		write(pipefd[1],s.c_str(),s.length());
		cout <<"Write: "<<s <<"\n-------------\n";
		sleep(SLEEP_TIME);

	}
	waitpid(pid2, NULL, 0);

	read(pipefd[0],buffer,100);
	cout << "--- At End (PID 0) ---\nRead: "<< buffer<<endl;



	return 0;
} 