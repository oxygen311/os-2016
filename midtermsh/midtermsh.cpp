#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
const size_t BUFF_SIZE = 1024;
int pid;
bool running = false;
int first_pipe[2];
int second_pipe[2];

void handler(int x) {
    if (x != SIGINT) return;
    if (running) {
        kill(pid, SIGINT);
    } else {
        exit(0);
    }
}

void delete_spaces(string &s) {
    const auto beg = s.find_first_not_of(" ");
    s = s.substr(beg, s.find_last_not_of(" ") - beg + 1);
}

string get_line() {
    ssize_t size = 0;
    char buf[BUFF_SIZE];
    string res;
    while ((size = read(0, buf, BUFF_SIZE)) != 0) {
        if (size == -1) if (errno == EINTR) {
            perror("EINTR caught\n");
            continue;
        } else
            exit(errno);
        res += buf;
        if (buf[size - 1] == '\n') break;
    }
    return res.substr(0, res.find('\n'));
}

vector<string> split(const string &s, char delim) {
    vector<string> ans;
    stringstream ss(s);
    string tmp;
    while (getline(ss, tmp, delim)) {
        delete_spaces(tmp);
        ans.push_back(tmp);
    }
    return ans;
}

vector<char *> vectro_c_str(vector<string> vec) {
    vector<char *> ans;
    for (auto s : vec) {
        char *cstr = new char[s.length() + 1];
        std::strcpy(cstr, s.c_str());
        ans.push_back(cstr);
    }
    ans.push_back(NULL);
    return ans;
}

int execute(char **commands, bool is_first, bool is_last) {
    pipe(second_pipe);
    pid = fork();
    if (pid == 0) {
        if (!is_first) {
            dup2(first_pipe[0], 0);
            close(first_pipe[0]);
            close(first_pipe[1]);
        }
        if (!is_last) {
            dup2(second_pipe[1], 1);
        }
        close(second_pipe[0]);
        close(second_pipe[1]);
        execvp(commands[0], commands);
        return 0;
    } else {
        if (!is_first) {
            close(first_pipe[0]);
            close(first_pipe[1]);
        }
        if (is_last) {
            close(second_pipe[0]);
            close(second_pipe[1]);
        }
    }
    first_pipe[0] = second_pipe[0];
    first_pipe[1] = second_pipe[1];
    return 1;
}

void execute_line(string line) {
    auto pipers = split(line, '|');
    size_t i = 0;
    for (auto com : pipers) {
        auto commands = vectro_c_str(split(com, ' '));
        execute(&commands[0], i == 0, (i == pipers.size() - 1));
        i++;
    }
    running = true;
    int stat;
    while ((pid = wait(&stat)) > 0);
    running = false;
}

int main() {
    while (1) {
        write(STDOUT_FILENO, "$ ", 2);
        auto s = get_line();
        if (s.size() == 0) break;
        delete_spaces(s);
        execute_line(s);
    }
}
