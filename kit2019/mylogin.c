/*
 * Shows user info from local pwfile.
 *  
 * Usage: userinfo username
 */

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwdblib.h"   /* include header declarations for pwdblib.c */

/* Define some constants. */
#define USERNAME_SIZE (32)
#define PASSWORD_SIZE (32)
#define NOUSER (-1)


int print_info(const char *username)
{
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  if (p != NULL) {
    printf("Name: %s\n", p->pw_name);
    printf("Passwd: %s\n", p->pw_passwd);
    printf("Uid: %u\n", p->pw_uid);
    printf("Gid: %u\n", p->pw_gid);
    printf("Real name: %s\n", p->pw_gecos);
    printf("Home dir: %s\n",p->pw_dir);
    printf("Shell: %s\n", p->pw_shell);
	return 0;
  } else {
    return NOUSER;
  }
}

void read_username(char *username)
{
  printf("login: ");
  fgets(username, USERNAME_SIZE, stdin);

  /* remove the newline included by getline() */
  username[strlen(username) - 1] = '\0';
}
int read_password(char *password, const char *username)
{
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  if(p == NULL){
     getpass("password: " ); 
     printf("\nUn-known user or incorrect password.\n");
    return 0;
  }  
  char* salt = malloc(2);
  salt[3] ='\0';
  strncpy(salt, p->pw_passwd, 2);
  password = crypt(getpass("password: " ), salt);
 if(strcmp(password, p->pw_passwd) == 0){
   printf("\nUser authenticated successfully.\n");
 }
 else{
    printf("\nUn-known user or incorrect password.\n"); 
 }
  
}

int main(int argc, char **argv)
{
  
  char username[USERNAME_SIZE];
  char password[PASSWORD_SIZE];
  while(1){
  read_username(username);
  read_password(password, username);
  
  }
  /* 
   * Write "login: " and read user input. Copies the username to the
   * username variable.
   */
  

  /* Show user info from our local pwfile. 
  if (print_info(username) == NOUSER) {
      /* if there are no user with that usename... 
      printf("\n Un-known user or incorrect password.");   
      return 0;
  }
  */
 
}
  

  
