#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char userIn[256]; // user inputs being stored
char strNsp[256]; // string no space
char strUp[256];  // string uppercase
int semi = 1;
double addedG = 0, fG; // added of grades // final gpa
int semo = 0;          // semester y/n
double nh = 0;         // number of honors
double na = 0;         // number of aps

void hnsemo() {
  int i = 1;
  for (int ii = semi; ii > 0; --ii && ++i) {
    printf("\nhow many honors in semester %d: ", i);
    nh = nh + atoi(fgets(userIn, 128, stdin));
  }
  nh = nh / semi;
}
void ansemo() {
  int i = 1;
  for (int ii = semi; ii > 0; --ii && ++i) {
    printf("\nhow many APs in semester %d: ", i);
    na = na + atoi(fgets(userIn, 128, stdin));
  }
  na = na / semi;
}
// addeds nums in int arr
void sem() {
  printf("\nhow many semesters: ");
  semi = atoi(fgets(userIn, 128, stdin));
  semo = 1;
}

char *upperstr(char strNsp[]) {
  int ii = 0;
  char cap[] = {'A', 'B', 'C', 'D', 'F'};
  char noCap[] = {'a', 'b', 'c', 'd', 'f'};

  for (int i = 0; strNsp[i] != '\n'; ++i) {
    while (noCap[ii] != strNsp[i] && cap[ii] != strNsp[i])
      ++ii;
    strUp[i] = cap[ii];
    ii = 0;
  }

  strcat(strUp, "\n");
  return strUp;
}

// removes characters ' ' and ',' from userIn
char *remove_c(char userIn[]) {
  int i = 0;
  // loop til end of userIn
  for (char *p = &userIn[0]; *p != '\n'; ++p && ++i) {
    // userIn ' ' or ',' move to next char in arr
    while (*p == ' ' || *p == ',') {
      ++p;
    }
    strNsp[i] = *p;
  }
  // append new line esc, pass through upperstr
  return upperstr(strcat(strNsp, "\n"));
}

int main() {

  char assignChar[] = {'F', 'D', 'C', 'B', 'A'}; // list of valid char
                                                 // could prob be done not rev

  int arrNum[256];   // letter grade to num put to this arr
  int assignNum = 0; // shitty brute force way to assign num to arr
  int divNum, cToI;  // div by num of passes // convert str to int
  int pa = 0;        // # of passes
  int duf = 1;       // default unfilled courses
  int v = 0;         // valid answer
  // display x or not
  char wHonC[2] = {' ', 'X'};
  char wApC[2] = {' ', 'X'};
  char wpC[2] = {' ', 'X'};
  char wmC[2] = {' ', 'X'};

  // toggle for weighting options
  int whT = 0;
  int waT = 0;
  int wpT = 0;
  int wmT = 0;

  int usel = 0; // determ if user selected

  printf("======================================================\n||           "
         "                                       ||\n||                  GPA "
         "CALCULATOR                  "
         "||\n||                                                  ||"
         "\n======================================================\n");
  printf("\nCount by semesters? [y/N] ");
  fgets(userIn, 8, stdin);
  if (userIn[0] == 'y' || userIn[0] == 'Y') {
    sem();
  } else if (userIn[0] == 'n' || userIn[0] == 'N' || userIn[0] == '\n')
    semo = 0;
  else
    return 0;

  printf("\ndefault unfilled courses to A's? [Y/n] ");
  fgets(userIn, 8, stdin);
  if (userIn[0] == 'y' || userIn[0] == 'Y' || userIn[0] == '\n')
    duf = 1;
  else if (userIn[0] == 'n' || userIn[0] == 'N')
    duf = 0;
  else
    return 0;

  if (duf && !semo) {
    while (!v) {
      printf("\nhow many courses to account for (default 7): ");
      fgets(userIn, 32, stdin);
      cToI = atoi(userIn);
      if (userIn[0] == '\n') {
        cToI = 7;
        v = 1;
      } else if (!cToI) {
        printf("\ninvalid input, try again");
        v = 0;
      } else
        v = 1;
    }
  } else if (semo) {
    while (!v) {
      printf("\nhow many courses per semester (default 7): ");
      fgets(userIn, 32, stdin);
      cToI = semi * atoi(userIn);
      if (userIn[0] == '\n') {
        cToI = semi * 7;
        v = 1;
      } else if (!cToI) {
        printf("\ninvalid input, try again");
        v = 0;
      } else
        v = 1;
    }
  }

  printf("\nhow would you like your gpa weighted: \n");
  while (!usel) {
    printf("\n1.) weigh honors [%c] 2.) weigh ap [%c] 3.) weigh plus [%c] 4.) "
           "weigh "
           "minus [%c]: ",
           wHonC[whT], wApC[waT], wpC[wpT], wmC[wmT]);
    fgets(userIn, 256, stdin);

    if (atoi(&userIn[0]) == 1)
      whT = !whT;
    else if (atoi(&userIn[0]) == 2)
      waT = !waT;
    else if (atoi(&userIn[0]) == 3)
      wpT = !wpT;
    else if (atoi(&userIn[0]) == 4)
      wmT = !wmT;
    else if (userIn[0] == '\n')
      usel = 1;
    else
      printf("\nInvalid input, try again\n");
  }

  // how many honors
  if (!semo) {
    if (whT) {
      printf("\nHow many honors: ");
      nh = atoi(fgets(userIn, 128, stdin));
    }
    if (waT) {
      printf("\nHow many APs: ");
      na = atoi(fgets(userIn, 128, stdin));
    }
  } else if (semo) {
    if (whT) {
      hnsemo();
    }
    if (waT) {
      ansemo();
    }
  }

  // takes user letter grade input
  printf("\ninput your letter grades (ie: A B C D F): ");
  remove_c(fgets(userIn, 256, stdin));

  if (strUp[0] == '\n') {
    pa = 0;
  } else {
    // iterate through str til end
    for (int i = 0; strUp[i] != '\n'; ++i) {
      // set arrNum[i] to coresponding letter in arr
      while (strUp[i] != assignChar[assignNum])
        ++assignNum;
      arrNum[i] = assignNum;
      ++pa;
      assignNum = 0;
    }
  }

  divNum = pa;

  // addeds nums in int arr
  for (int i = 0; pa > 0; ++i) {
    addedG = addedG + arrNum[i];
    --pa;
  }
  if (!duf)
    fG = addedG / divNum; // divide by total # of c
  else
    fG = (addedG + ((semi * (nh + na) + (4 * (cToI - divNum))))) / cToI;

  printf("\nfinal gpa is %f\n", fG);
}
