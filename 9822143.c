#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//---------------------Do Not Change This!---------------------
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <termios.h>
char c;//the input character
int input_count = 0;//the input count
char a[100][8]; // the Spaceee
int stop_count = 0, jzb_cnt = 0; //special disks counters
int score = 0, health = 3; // first needs
int input_check;
int test_mode = 0;
void mymain(); //your main() method will be implemented later
void help();
void newgame();
void testmode();
char rand_deh();
int doreghami(int n);
int last( );
void delete(char b,int jaht);// jahat(1:Right , 2:Left)
void refresh( );
void refresh_test();
void walls( );
void print( );
void firstdesign( );
void convert_to(char to);
int rand_jzb();
void healthdone();
void zaribsaz();
void zarib_two();
void zarib_four();
void *keypress_callback(void *arg){
  while(1) {
    c = getchar();
    if(c == 'q'){
      printf("\n\nYour Score is : %d \nBye\n", score);
      exit(0);
    }
    input_count++;
  }
  return 0;
}
void starter(){
  struct termios info;
  tcgetattr(0, &info);      
  info.c_lflag &= ~ (ICANON | ECHO) ;  
  info.c_cc[VMIN] = 1;
  info.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &info); 
  pthread_t tid1;
  pthread_create(&tid1, NULL, &keypress_callback, NULL);
}
int main(){
  starter();
  mymain();
  return 0;
}
//---------------------Do Not Change This!---------------------
//Assume that the latest input character is in variable c 
//You can check the input_count to check if there was any key press.
void mymain(){
  //this code is for your testing:
  char choice;
  system("clear");
  printf("Welcome to Orbis!\nYou've 5 seconds to choose...\n\n");
  printf("1.New Game\n2.Test Mode\n3.Help\n4.Exit\n");
  sleep(5);
  choice = c;
  switch(choice){
    case '1':
      score = 0, health = 3; 
      input_check = input_count ;
      firstdesign(a);
      walls(a);
      zaribsaz();
      newgame();
      return;
      break;
    case '2':
      score = 0, health = 3; 
      input_check = input_count ;
      firstdesign(a);
      walls(a);
      zaribsaz();
      testmode();
      break;
    case '3':
      help();
      break;
    case '4':
      printf("\n\nGood Bye\n\n");
      sleep(2);
      return;
      break;
    default:
      system("clear");
      printf("\nWrong Input!\n\n");
      sleep(2);
      mymain();
      break;
  }
  return;
}
void newgame(){
  while(1){
    system("clear");
    print();
    sleep(1);
    char enterance = c;
    if(enterance == 'z'){
      system("clear");
      printf("\n\nYour Score is  : %d \n\n", score);
      sleep(2);
      score = 0, health = 3; 
      input_check = input_count ;
      firstdesign(a);
      walls(a);
      mymain();
      exit(0);
    }
    if( a[last()][3] == '#' && (input_count != input_check || jzb_cnt > 0)){ // #->
      if(stop_count > 0) stop_count--;
      if(enterance == 'C' || jzb_cnt > 0) score += a[last()][7];
      else if(jzb_cnt == 0) health--;
      input_check = input_count;
      if(enterance == 'C' || jzb_cnt > 0) delete('#' , 1);
      else if (enterance == 'D') delete('#' , 2);
      newgame();
    }
    else if(a[last()][3] == '*' && (input_count != input_check || jzb_cnt > 0)){ // <-
      if(stop_count > 0) stop_count--;
      if(enterance == 'D' || jzb_cnt > 0) score += a[last()][7];
      else if(jzb_cnt == 0) health--;
      input_check = input_count;
      if(enterance == 'D' || jzb_cnt > 0) delete('*' , 2);
      else if (enterance == 'C') delete('*' , 1);
      newgame();
    }
    else if(a[last()][3] == '$' && ((enterance == 'D' && input_count != input_check) || jzb_cnt > 0)){ // $
      if(stop_count > 0) stop_count--;
      score += a[last()][7];
      input_check = input_count;
      convert_to('*');
      delete('$', 2);
      newgame();
    }
    else if(a[last()][3] == '$' && ((enterance == 'C' && input_count != input_check) || jzb_cnt > 0)){ // $
      if(stop_count > 0) stop_count--;
      score += a[last()][7];
      input_check = input_count;
      convert_to('#');
      delete('$', 1);
      newgame();
    }
    else if(a[last()][3] == '+' && (input_count != input_check || jzb_cnt > 0)){
      if(stop_count > 0) stop_count--;
      if(health < 3) health++;
      input_check = input_count;
      if(jzb_cnt > 0) delete('+', rand_jzb());
      else if(enterance == 'C') delete('+' , 1);
      else if (enterance == 'D') delete('+' , 2);
      newgame();
    }
    else if(a[last()][3] == '2' && (input_count != input_check || jzb_cnt > 0)){
      if(stop_count > 0) stop_count--;
      input_check = input_count;
      zarib_two();
      //////////// 
      if(jzb_cnt > 0) delete('2', rand_jzb());
      else if(enterance == 'C') delete('2' , 1);
      else if (enterance == 'D') delete('2' , 2);
      newgame();
    }
    else if(a[last()][3] == '4' && (input_count != input_check || jzb_cnt > 0)){
      if(stop_count > 0) stop_count--;
      input_check = input_count;
      zarib_four();
      ////////
      if(jzb_cnt > 0) delete('4', rand_jzb());
      else if(enterance == 'C') delete('4' , 1);
      else if (enterance == 'D') delete('4' , 2);
      newgame();
    }
    else if (a[last()][3] == '|' && (input_count != input_check || jzb_cnt > 0)){
      input_check = input_count;
      stop_count = 3;
      if(jzb_cnt > 0) delete('|', rand_jzb());
      else if(enterance == 'C') delete('|' , 1);
      else if (enterance == 'D') delete('|' , 2);
      newgame();
    }
    else if(a[last()][3] == '~' && (input_count != input_check || jzb_cnt > 0)){
      if(stop_count > 0) stop_count--;
      input_check = input_count;
      if(jzb_cnt > 0) delete('~', rand_jzb());
      else if(enterance == 'C') delete('~' , 1);
      else if (enterance == 'D') delete('~' , 2);
      jzb_cnt ++;
      newgame();
    }
    else if(a[last()][3] == '=' && (input_count != input_check || jzb_cnt > 0)){
      if(stop_count > 0) stop_count--;
      input_check = input_count;
      if(jzb_cnt > 0) jzb_cnt --;
      if(jzb_cnt > 0) delete('=', rand_jzb());
      else if(enterance == 'C') delete('=' , 1);
      else if (enterance == 'D') delete('=' , 2);
      newgame();
    }
    if(a[last()][3] == '?'){
      a[last()][3] = a[last()][4] = rand_deh();
      print();
    }
    if (health == 0) { // health is done by entering wrong input to "*" and "#"
      system("clear");
      printf("\n\nYour Score is  : %d \n\n", score);
      sleep(3);
      score = 0, health = 3; 
      input_check = input_count ;
      firstdesign(a);
      walls(a);
      mymain();
      return;
    }
    if(last() == 1){// stack is full
      health --;
      if(health == 0){
        system("clear");
        printf("\n\nYour Score is  : %d \n\n", score);
        sleep(3);
        score = 0, health = 3; 
        input_check = input_count;
        firstdesign(a);
        walls(a);
        mymain();
      }
      else{
        jzb_cnt = 1;
        newgame();
      }
    }
    if(stop_count == 0 && test_mode == 0) refresh();
    else if (test_mode == 0)stop_count--;
    else if(stop_count == 0 && test_mode == 1) refresh_test();
    else stop_count--;
  }
}
void testmode(){
  test_mode = 1;
  /*a[1][3] = a[1][4] =   ' ';
  a[2][3] = a[2][4] =   ' ';
  a[3][3] = a[3][4] =   ' ';
  a[4][3] = a[4][4] =   ' ';
  a[5][3] = a[5][4] =   ' ';*/
  a[6][3] = a[6][4] =   '~';
  a[7][3] = a[7][4] =   '*';
  a[8][3] = a[8][4] =   '4';
  a[9][3] = a[9][4] =   '*';
  a[10][3] = a[10][4] = '4';
  a[11][3] = a[11][4] = '*';
  a[12][3] = a[12][4] = '*';
  a[13][3] = a[13][4] = '*';
  a[14][3] = a[14][4] = '*';
  a[15][3] = a[15][4] = '*';
  a[16][3] = a[16][4] = '*';
  a[17][3] = a[17][4] = ' ';
  a[18][3] = a[18][4] = ' ';
  a[19][3] = a[19][4] = ' ';
  a[20][3] = a[20][4] = ' ';
  a[21][3] = a[21][4] = ' ';
  a[22][3] = a[22][4] = ' ';
  a[23][3] = a[23][4] = ' ';
  a[24][3] = a[24][4] = ' ';
  a[25][3] = a[25][4] = ' ';
  a[26][3] = a[26][4] = ' ';
  a[27][3] = a[27][4] = ' ';
  a[28][3] = a[28][4] = ' ';
  a[29][3] = a[29][4] = ' ';
  a[30][3] = a[30][4] = ' ';
  newgame();
  return;
}
void firstdesign( ){
  for(int i = 1; i <= 10; i++){
    for(int j = 1; j <= 6; j++){
      a[i][j] = ' ';
    }
  }
  refresh();
  refresh();
  refresh();
  refresh();
}
void walls( ){
  for(int i = 1; i <= 10; i ++){
    a[i][1] = '*';
  }
  for(int i = 1; i <= 10; i ++){
    a[i][6] = '#';
  }
}
void print( ){
  for(int i = 1; i <= 10; i++){
    for(int j = 1; j <= 6;j++){
      printf("%c", a[i][j]); 
    }
    printf("\n");
  }
  printf("_______ score : %d , Health : %d\n",score, health);
}
void refresh( ){
  for(int i = 1; i <= 10; i++){
    a[i-1][3] = a[i][3];
    a[i-1][4] = a[i][4];
    a[i-1][7] = a[i][7];
  }
  a[10][3] = a[10][4] = rand_deh();
  srand(time(0));
  usleep(4500);
}
void refresh_test(){
  for(int i = 1; i <= 30; i++){
    a[i-1][3] = a[i][3];
    a[i-1][4] = a[i][4];
    a[i-1][7] = a[i][7];
  }

}
char rand_deh(){
  srand(time(0));
  int n = doreghami(rand());
  if(n>=0 && n <=30) return '*';
  else if(n>30 && n <=60) return '#';
  else if(n>60 && n <=65) return '?';
  else if(n>65 && n <=70) return '$';
  else if(n>70 && n <=73) return '+';
  else if(n>73 && n <=76) return '2';
  else if(n>76 && n <=80) return '4';
  else if(n>80 && n <=85) return '|';
  else if(n>85 && n <=90) return '~';
  else if(n>90 && n <=100) return '=';
  }
int doreghami(int n){
  for(;n >100 ;) n /= 10;
    return n;
}
int last( ){
  for(int i = 0; i <= 10; i++){
    if(a[i][3] != ' ') return i;
  }
}
void delete(char b,int jaht){
  int ind = last();
  if(jaht == 1){ // move to right
    a[ind][3] = ' ';
    a[ind][5] = b;
    system("clear");
    print() ;
    usleep(35000);
    a[ind][4] = ' ';
    system("clear");
    print() ;
    a[ind][2] = a[ind][3] = a[ind][4] = a[ind][5] = ' ';
    usleep(35000);
    system("clear");
    print();
    printf("\a");
    return;
  }
  else if(jaht == 2){ // move to left
    a[ind][4] = ' ';
    a[ind][2] = b;
    system("clear");
    print() ;
    usleep(35000);
    a[ind][3] = ' ';
    system("clear");
    print() ;
    a[ind][2] = a[ind][3] = a[ind][4] = a[ind][5] = ' '; 
    usleep(35000);
    system("clear");
    print() ;
    printf("\a");
    return;
  }
}
void help(){
  printf("\nMove disks with the keys ""->"" and ""<-"" to increase your score\n");
  printf("You have 3 healthes to play and don't let the disks to reach to the top :)\n");
  printf("Good luck\npress ""q"" to quit...\npress ""z"" to show score and return to mymain");
  printf("You will be returned to the menu in 5 seconds...\n\n");
  sleep(5);
  mymain();
}
void convert_to(char to){
  for(int i = last()+1; i <= 10; i++){
      a[i][3] = a[i][4] = to;
  }
  return;
}
int rand_jzb(){
  srand(time(0));
  int n = doreghami(rand());
  if( n >= 0 && n < 50) return 1;
  else return 2;
}
void zaribsaz(){
  for(int i = 1; i < 100; i++){
    a[i][7] = 1;
  }
}
void zarib_two(){
  for(int i = last()+1; i <= last()+3; i++){
    a[i][7] *= 2;
  }
}
void zarib_four(){
  for(int i = last()+1; i <= last()+3; i++){
    a[i][7] *= 4;
  }
}