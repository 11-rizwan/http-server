#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")

void communicatewithserver(SOCKET SOC_CONNECT){
   //Request sending
   const char* httprequest = 
         "GET /index.html HTTP/1.1\r\n"
         "Host: example.com\r\n"
         "Connection: Close\r\n"
         "\r\n";
   int sendreq = send(SOC_CONNECT,httprequest,(int)strlen(httprequest),0);
   if(sendreq == SOCKET_ERROR){
      std::cerr<<"request failed with error"<<WSAGetLastError()<<std::endl;
   }
   //Receiving request
      char incommingbuffer[4096];
      int bytesread =0;
      while((bytesread = recv(SOC_CONNECT,incommingbuffer,sizeof(incommingbuffer) -1,0))>0){
         incommingbuffer[bytesread] = '\0';
         std::cout<<incommingbuffer;
      }
      if (bytesread == 0){
         std::cout<<"connection closed by server"<<std::endl;
      }
      else if(bytesread == SOCKET_ERROR){
         std::cerr<<"Receive failed with error"<<WSAGetLastError()<<std::endl;
      }

}
 int main() {
   WSAData wsaData;
   int wsresult = WSAStartup(MAKEWORD(2,2), &wsaData);
   if(wsresult !=0){
      std::cerr << "WSAStarup failed:"<< wsresult << std::endl;
      return 1;
   }
   
   std::cout << "WSAStartup successful" << std::endl;
   
   struct addrinfo serverAddr{};
   struct addrinfo* ptr = NULL;
   struct addrinfo* result = NULL;
   SOCKET SOC_CONNECT = INVALID_SOCKET;


   ZeroMemory(&serverAddr,sizeof(serverAddr));
   serverAddr.ai_family = AF_UNSPEC;
   serverAddr.ai_socktype = SOCK_STREAM;
   serverAddr.ai_protocol = IPPROTO_TCP;

   int iresult = getaddrinfo("example.com","80",&serverAddr,&result);
   if(iresult !=0){
      std::cerr<<"getaddrinfo failed" <<iresult <<std::endl;
      WSACleanup();
      return 1;
   }
   for(ptr = result; ptr != nullptr; ptr = ptr->ai_next){
      SOC_CONNECT=socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
      if(SOC_CONNECT == INVALID_SOCKET){
         std::cout<<"This one failed ,trying another"<<std::endl;
         continue;
      }
      int iResult = connect(SOC_CONNECT,ptr->ai_addr,(int)ptr->ai_addrlen);
      if(iResult == SOCKET_ERROR){
         std::cout<<"couldn't connect closing socket"<<std::endl;
         closesocket(SOC_CONNECT);
         SOC_CONNECT = INVALID_SOCKET;
         continue;

      }
      std::cout<<"socket connected sucessfully"<<std::endl;
      break;
   }
   
   if(SOC_CONNECT != INVALID_SOCKET){
      communicatewithserver(SOC_CONNECT);
         int close_soc = closesocket(SOC_CONNECT);
         if (close_soc == 0){
         std::cout << "SOcket closed sucessfully"<<std::endl;
         }
         else{
            std::cerr<<"socket close failed"<<WSAGetLastError()<<std::endl;
         }
   }
   else{
      std::cout<< "no connection established"<<std::endl;
   }
   freeaddrinfo(result);
   WSACleanup();
   std::cout << "WSACleanup sucessful"<<std::endl;
   return 0;
  
 }
