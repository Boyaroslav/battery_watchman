#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <gio/gio.h>

int toint(char arr[]){
  int p=0;
  int ans=0;
  while(arr[p] && arr[p] != '\n'){
    ans = ans * 10 + (arr[p] - '0');
    p++;
  }
  return ans;
}



int main(int argc, char* argv[])
{

  int nochdir = 0;
  int f;

  int noclose = 0;

  // вот тут то он его и демонизирует
  if(daemon(nochdir, noclose))
    perror("daemon");

  char buf[4];
  int I_KNOW_SHUT_UP_10 = 0;
  int I_KNOW_SHUT_UP_5 = 0;
  int status;
  GNotification *notification;
  GApplication *application = g_application_new ("the.end", G_APPLICATION_FLAGS_NONE);
  g_application_register (application, NULL, NULL);

  for(;;){
    f = open("/sys/class/power_supply/BAT0/capacity", O_RDONLY);

    read(f, buf, 4);
    if (toint(buf) <= 10 && !(I_KNOW_SHUT_UP_10)){
        notification = g_notification_new ("Мы щас все помрем, 10%");
        g_notification_set_body (notification, "The End.");
        g_application_send_notification (application, NULL, notification);
  
        g_object_unref (notification);
        I_KNOW_SHUT_UP_10 = 1;
    }
    if (toint(buf) <= 5 && !(I_KNOW_SHUT_UP_5)){
        notification = g_notification_new ("Ты баран? 5%");
        g_notification_set_body (notification, "The End.");
        g_application_send_notification (application, NULL, notification);

        g_object_unref (notification);
        I_KNOW_SHUT_UP_10 = 5;
    }
    if (toint(buf) > 10){I_KNOW_SHUT_UP_10 = 0;}
    if (toint(buf) > 5){I_KNOW_SHUT_UP_5 = 0;}


    close(f);

    sleep(30);
  }
  close(f);
  

  return 0;
}