
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sstream>
#include<sys/utsname.h>

int main() {


	pid_t i = getpid();
	std::ostringstream stream;
	stream << "/proc/" << i << "/status";
	int fd = open(stream.str().c_str(), O_RDONLY);
	if(fd == -1) {
		std::cerr << "Error opening status file\n";
		exit(EXIT_FAILURE);
	}

	ssize_t readBytes = 0;
	char buf[1024];

	while((readBytes = read(fd, buf, 1024)) > 0) {
		write(1, buf, readBytes);
	}

	close(fd);

	utsname uts;

	if(uname(&uts) == -1) {
		std::cerr << "Error calling uname..\n";
		exit(EXIT_FAILURE);
	}

	std::cout << uts.sysname << " " << uts.version << " " << uts.domainname << "\n";

	return EXIT_SUCCESS;
}
