#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>


// Question 1 Fork,exec,pipe
int main(int argc, char* argv[]){
    if(argc < 3){
        std::cerr << "Usage: " << argv[0] << " command1 | command2" << std::endl;
        return 1;
    }

    // Trouver l'index du pipe '|' dans argv
    int pipeIndex = -1;
    for(int i = 1; i < argc; ++i) {
        if(std::string(argv[i]) == "|") {
            pipeIndex = i;
            break;
        }
    }

    if(pipeIndex == -1) {
        std::cerr << "Error: Pipe symbol '|' not found." << std::endl;
        return 1;
    }

    // Construire deux tableaux d'arguments
    std::vector<const char*> cmd1(argv + 1, argv + pipeIndex);
    std::vector<const char*> cmd2(argv + pipeIndex + 1, argv + argc);
    cmd1.push_back(nullptr);
    cmd2.push_back(nullptr);

    // Création du pipe
    int tube[2];
    pipe(tube);

    pid_t pid = fork();
    if(pid == 0) { // Fils
        close(tube[1]);
        dup2(tube[0], STDIN_FILENO);
        close(tube[0]);

        execv(cmd2[0], const_cast<char* const*>(cmd2.data()));
        perror("execv child");
        exit(1);
    } else { // Père
        close(tube[0]);
        dup2(tube[1], STDOUT_FILENO);
        close(tube[1]);

        execv(cmd1[0], const_cast<char* const*>(cmd1.data()));
        perror("execv parent");
        exit(1);
    }

    waitpid(pid, NULL, 0);
    return 0;
}
