#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char userIn[256];
char strNsp[256];

// removes characters ' ' and ',' from userIn
char *remove_c(char userIn[]) {
  int ii = 0; // initialize ii in function
  // loop til end of userIn
  for (int i = 0; userIn[i] != '\n'; ++i) {
    // userIn not ' ' or ',' set strNsp[ii] to
    // could be done w/ pointers but whatev
    if (userIn[i] != ' ' && userIn[i] != ',') {
      strNsp[ii] = userIn[i];
      ++ii;
    }
  }
  // append new line to check end of read
  // prob better way to check but whatev
  strcat(strNsp, "\n");
  return strNsp;
}

int main() {

  char assignChar[] = {'F', 'D', 'C', 'B', 'A'}; // list of valid char
                                                 // could prob be done not rev

  char userChar[256]; // user input stored
  double addedG = 0;  // added of grades
  double fG;          //
  int arrNum[256];    // letter grade to num put to this arr
  int assignNum = 0;  // shitty brute force way to assign num to arr
  int divNum;         // cuz pa gets changed and want value of pa at end
  int pa = 0;         // # of passes
  int duf = 1;        // default unfilled courses
  int cToI;           // convert str to int
  int v = 0;

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
  printf("\ndefault unfilled courses to A's? [Y/n] ");
  fgets(userIn, 8, stdin);
  if (userIn[0] == 'y' || userIn[0] == 'Y' || userIn[0] == '\n')
    duf = 1;
  else if (userIn[0] == 'n')
    duf = 0;
  else
    return 0;

  if (duf) {
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
    // printf("\nwhT %d\n", whT);
  }

  int nh = 0; // number of honors
  int na = 0; // number of aps
  // how many honors
  if (whT) {
    printf("\nHow many honors: ");
    nh = atoi(fgets(userIn, 128, stdin));
  }
  if (waT) {
    printf("\nHow many APs: ");
    na = atoi(fgets(userIn, 128, stdin));
  }
  // printf("\nNH %d\n", nh);

  // takes user letter grade input
  printf("\ninput your letter grades (ie: A B C D F): ");
  remove_c(fgets(userIn, 256, stdin));

  if (strNsp[0] == '\n') {
    pa = 0;
  } else {
    // iterate through str til end
    for (int i = 0; strNsp[i] != '\n'; ++i) {
      // set arrNum[i] to coresponding letter in arr
      while (strNsp[i] != assignChar[assignNum])
        ++assignNum;
      // printf("\nassign num %d\n", assignNum);
      arrNum[i] = assignNum;
      ++pa;
      assignNum = 0;
    }
  }

  divNum = pa;

  // addeds nums in int arr
  for (int i = 0; pa > 0; ++i) {
    // printf("\nJBRJJR %d\n", arrNum[i]);
    addedG = addedG + arrNum[i];
    --pa;
  }
  if (!duf)
    fG = addedG / divNum; // divide by total # of c
  else
    fG = (addedG + (((nh + na) + (4 * (cToI - divNum))))) / cToI;

  printf("\nfinal gpa is %f\n", fG);
}