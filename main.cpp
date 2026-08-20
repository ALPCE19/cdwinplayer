#include<iostream>
#include<string>
#include<windows.h>
#include<mmsystem.h>

// Тут мы просим линкеру компилятора, что нужно подключить WinMM
#pragma comment(lib, "winmm.lib")
// Функция для работы с дисководом
void sendMciCommand(const std::string& command) {
  char errorBuffer[128];
  MCIERROR error = mciSendStringA(command.c_str(), NULL, 0, NULL);

  if (error != 0) {
    mciGetErrorStringA(error, errorBuffer, sizeof(errorBuffer));
    std::cerr << "cdwp error: " << errorBuffer;
  }
}
// Функция вывода помощи
void printHelp() {
  std::cout << "cdwinplayer CLI\n\n";
  std::cout << "using: cdwp.exe <command>\n";
  std::cout << "  open    - Open cd/dvd drive\n";
  std::cout << "  close    - Close cd/dvd drive\n";
  std::cout << "  play    - play AudioCD\n";
  std::cout << "  stop    - stop AudioCD\n";
  std::cout << "  pause    - pause AudioCD\n";
  std::cout << "  status    - status cd\n";

}
// Точка входа программы (Обьяснять не надо код и так интуитивно понятен)
int main(int argc, char* argv[]) {
  SetConsoleOutputCP(CP_UTF8);

  if (argc < 2) {
    printHelp();
    return 1;
  }
  std::string command = argv[1];
  if (command == "open") {
    std::cout << "Opening CD/DVD-drive..." << std::endl;
    sendMciCommand("set cdaudio door open");
  }
  else if (command == "close") {
    std::cout << "Closing CD/DVD-drive..." << std::endl;
    sendMciCommand("set cdaudio door closed");
  }
  else if (command == "play") {
    std::cout << "Initilization AudioCD and start play... Ctrl+C -> stop play" << std::endl;
    sendMciCommand("open cdaudio");
    sendMciCommand("play cdaudio wait");
  }
  else if (command == "status") {
    char returnBuffer[64];
    mciSendStringA("status cdaudio mode", returnBuffer, sizeof(returnBuffer), NULL);
    std::cout << "Status -> " << returnBuffer << std::endl;
  }
  else {
    std::cerr << "Unknown argument: " << command << "\n\n";
    printHelp();
    return 1;
  }
  return 0;
}
