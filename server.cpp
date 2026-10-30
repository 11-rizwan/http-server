#include <iostream>
#include <ws2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
 int main() {
   WSAData wsaData;
   int result = WSAStartup(MAKEWORD(2,2), &wsaData);
   if(result !=0){
      
      std::cerr << "WSAStarup failed:"<< result << std::endl;
   }
   std::cout << "WSAStartup successful" << std::endl;
   sockaddr_in serverAddr{};
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(54000);
   int result2 = inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
   if (result2 <=0){
      SOCKET err = WSAGetLastError();
      std::cerr << "ip conversion failed: "<< err <<std::endl;
      WSACleanup();
      return 1;
   }
   else{
   std::cout<< "IP conversion sucessful"<<std::endl;
   }
   int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   
   if(sock == INVALID_SOCKET){
      SOCKET error = WSAGetLastError();
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