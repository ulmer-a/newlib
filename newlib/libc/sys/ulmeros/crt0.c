/* UlmerOS C runtime */

extern void _init_signal();
extern void exit(int status);
extern int main(int argc, char* argv[]);

char** environ;

void _start(int argc, char** argv, char** envp)
{
    _init_signal();
    environ = envp;
    int status = main(argc, argv);
    exit(status);
}