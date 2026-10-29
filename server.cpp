#include <iostream>

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
 int main() {
   WSAData wsaData;
   int result = WSAStartup(MAKEWORD(2,2), &wsaData);
   if(result !=0){
      
      std::cerr << "WSAStarup failed:"<< result << std::endl;
      WSACleanup();
      return 1;
   }
   std::cout << "WSAStartup successful" << std::endl;
   int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   
   if(sock == INVALID_SOCKET){
      int error = WSAGetLastError();
      std::cerr << "socket failed:"<< error << std::endl;
      WSACleanup();
      return 1;
   }
   std::cout << "Socket created sucessfully "<<std::endl;
   
   closesocket(sock);
   std::cout << "SOcket closed sucessfully"<<std::endl;
   WSACleanup();
   std::cout << "WSACleanup sucessful"<<std::endl;
   return 0;
 }