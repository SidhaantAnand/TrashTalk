//Environmental Survey

#include <stdio.h> 
#include <time.h> 
#include <string.h> 
#include <stdlib.h> 
#include <math.h>

char ques[7][100];
char options[5][100];
char ans[2][4];
	

void initializeQues()
{
	strcpy(ques[0], "Do you segregate waste?");
	strcpy(ques[1], "Did you trash non-biodegradable trash today?");
	strcpy(ques[2], "Did you waste food today?");
	strcpy(ques[3], "Do you know how many kids die of starvation in Africa?");
	strcpy(ques[4], "Do you see people throwing food around you everyday?");
	strcpy(ques[5], "Do you do your bit?");
	strcpy(ques[6], "Are you happy with your life?");
	
}
	
void initializeAns()
{
	strcpy(options[0], "Non-Woven Fabric");
	strcpy(options[0], "Ribbon");
	strcpy(options[0], "Paper Cups");
	strcpy(options[0], "Nylon");
	strcpy(options[0], "Thermocol");
	
}

void initializeOptions()
{
	strcpy(options[0], "Yes");
	strcpy(options[0], "No");
}

int askQuestion(char *currQuestion)
{
	// printf("LOl");    
//	printf(currQuestion);
   
  puts(currQuestion);
  puts( "Enter Yes or No :");
   char currAnswer[4];
   gets(currAnswer);
   
   if((strcmp(currAnswer,"yes") == 0) || (strcmp(currAnswer,"YES") == 0))
   {
	   strcpy(currAnswer,"Yes");
	   
   }
   if((strcmp(currAnswer,"no") == 0) || (strcmp(currAnswer, "NO") == 0))
	    strcpy(currAnswer,"No");
   if((strcmp(currAnswer,"Yes") != 0) && (strcmp(currAnswer,"No") != 0))
   {
	   puts("Don't be a rebel, please put in the correct value!");
	   return 0;
   }
	   
   
//	puts(currAnswer);
	
	/* if(currAnswer != options[0] || currAnswer != options[1])
	{
		printf("IN1");
		return -1;
	}
else
{ */
	
		FILE *ifp;
        char *mode = "r";
		int c;

        ifp = fopen("cfile.txt", mode);

         if (ifp == NULL) {
         fprintf(stderr, "Can't open input file in.list!\n");
		 printf("cant open file");
         exit(1);
		 return -1;
        }
		
		
		
	/*	char readQues[7][100];
		char yeses[7];
		char nos[7];
		
		for(int line = 0; line<7; line++)
		{
		
		 yeses[line] = getc(ifp);
		printf("%c", yeses[line]);
		 getc(ifp);
		 nos[line] = getc(ifp);
		 printf("%c", nos[line]);
		 getc(ifp);
		 
		 char toPut[100];
		 int a;
		 int k = 0;
		while('\n' != (a = fgetc(ifp))) {
			toPut[k] = a;
			k++;
        printf("%c",a);
    }
	
	
		 
		 strcpy(readQues[line], toPut);
		// printf(readQues[line]); 
		}
 //  } */
 

 // extract intoo lines
 char lines[7][1000];
 
 
	char ch = getc ( ifp );
	int line = 0;
    int index = 0;
	
    while ( ch != EOF ) {
		
        if ( ch != '\n'){
			
            lines[line][index++] = ch;
        }else {
		
             lines[line][index] = '\0';
		   
			// printf("%i",line); printf(lines[0]);
            index = 0;
			line++;

            // printf (lines[line] );
        }
        ch = getc ( ifp );
		
    }
	
/*	for(int i = 0; i<7; i++)
		puts(lines[i]); */


/*
        char readQues[7][100];
		char yeses[7];
		char nos[7];
		int yesnocount = 0;
		int readQuesCount = 0;
		
		for(int line = 0; line <7; line++)
		{
			char c = lines[line][0];
			puts("IN");
			int  k = 0;
			while(c != '\0')
			{
				
				printf("%",c);
				if(k==0)
				{
					yeses[yesnocount] = lines[line][0];
				}
				
				else if(k==2)
				{
					nos[yesnocount] = lines[line][2];
					yesnocount++;
				}
				
				else
				{
					readQues[line][readQuesCount] = lines[line][k];
					readQuesCount++;
				}
				
				k++;
			}
		}
		*/
		
		// extract int yes, no and ques
		char readQues[7][100];
		char yeses[7][3];
		char nos[7][3];
		int yindex = 0;
		int nindex = 0;
		int rqindex = 0;
		int k = 0;
		
		for(int line = 0; line <7; line++)
		{
			k = 0;
			yeses[line][0] = lines[line][0];
			yeses[line][1] = lines[line][1];
			yeses[line][2] = '\0';
			// puts(yeses[line]);
			nos[line][0] = lines[line][2];
			nos[line][1] = lines[line][3];
			nos[line][2] = '\0';
			
			int currindex = 4;
			char curr = lines[line][4];
			while(curr != '.')
			{
				//printf("%c",curr);
				readQues[line][k] = curr;
				k++;
				currindex++;
				curr = lines[line][currindex];
			}
			
			readQues[line][k] = '\0';
			
			
		}
		
	/*	for(int i = 0; i<7; i++)
		puts(readQues[i]); */
	
	fclose(ifp);
	
	
	
	int found = 0;
	
	// puts(currQuestion);
	for(int i = 0; i<7;i++)
	{
		if(strcmp(currQuestion,readQues[i]) == 0)
			found = i;
		
	}
	
	FILE *ofp = fopen("cfile.txt", "w");
	
	
	for(int i = 0; i<7; i++)
	{
		if(i == found)
		{
			if(strcmp(currAnswer,"Yes") == 0)
			{
				char no_of_yes = yeses[i][0] - '0';
				no_of_yes = no_of_yes + 1;
				char putitback = no_of_yes  + '0';
				// printf("%c",putitback);
				yeses[i][0] = putitback;
				
			fputs(yeses[i], ofp);
			fputs(nos[i],ofp);
			fputs(readQues[i], ofp);
			fputc('.',ofp);
			fputc('\n',ofp);
				
		}
		
		if(strcmp(currAnswer,"No") == 0)
			{
				char no_of_no = nos[i][0] - '0';
				no_of_no = no_of_no + 1;
				char putitback = no_of_no + '0';
			//	printf("%c",putitback);
				nos[i][0] = putitback;
				
			fputs(yeses[i], ofp);
			fputs(nos[i],ofp);
			fputs(readQues[i], ofp);
			fputc('.',ofp);
			fputc('\n',ofp);
				
		}
		
		
		}
		else
		{
			fputs(yeses[i], ofp);
			fputs(nos[i],ofp);
			fputs(readQues[i], ofp);
			fputc('.',ofp);
			fputc('\n',ofp);
		}
	}
	
	fclose(ofp);
	
	
return 0; 

}
		 
			

int printStatistic()
{
	FILE *ifp;
        char *mode = "r";
		int c;

        ifp = fopen("cfile.txt", mode);

         if (ifp == NULL) {
         fprintf(stderr, "Can't open input file in.list!\n");
		 printf("cant open file");
         exit(1);
		 return -1;
        }
		
		char lines[7][1000];
 
 
	char ch = getc ( ifp );
	int line = 0;
    int index = 0;
	
    while ( ch != EOF ) {
		
        if ( ch != '\n'){
			
            lines[line][index++] = ch;
        }else {
		
             lines[line][index] = '\0';
		   
			// printf("%i",line); printf(lines[0]);
            index = 0;
			line++;

            // printf (lines[line] );
        }
        ch = getc ( ifp );
		
    }
	
	char readQues[7][100];
		char yeses[7][3];
		char nos[7][3];
		int yindex = 0;
		int nindex = 0;
		int rqindex = 0;
		int k = 0;
		
		for(int line = 0; line <7; line++)
		{
			k = 0;
			yeses[line][0] = lines[line][0];
			yeses[line][1] = lines[line][1];
			yeses[line][2] = '\0';
			// puts(yeses[line]);
			nos[line][0] = lines[line][2];
			nos[line][1] = lines[line][3];
			nos[line][2] = '\0';
			
			int currindex = 4;
			char curr = lines[line][4];
			while(curr != '.')
			{
				//printf("%c",curr);
				readQues[line][k] = curr;
				k++;
				currindex++;
				curr = lines[line][currindex];
			}
			
			readQues[line][k] = '\0';
			
			
		}
		
	/*	for(int i = 0; i<7; i++)
		puts(readQues[i]); */
	
	fclose(ifp);
	
	for(int line = 0; line <7; line++)
	{
		puts(readQues[line]);
		puts("Number of Yeses :");
		puts(yeses[line]);
		puts("Number of Nos :");
		puts(nos[line]);
	}
	
	// calculating mean
		int sum1 = 0;
	int sum2 = 0;
	for(int line = 0; line<7;line++)
	{
		sum1 = sum1 + (yeses[line][0] - '0');
		sum2 = sum2 + (nos[line][0] - '0');
	}
	
	float meany = (float)sum1/7;
	float meann = (float)sum2/7;
	
	puts("Mean of the number of yeses : ");
	printf("%f\n", meany);
	puts("Mean of the number of nos : ");
	printf("%f\n", meann);
	
	int numYes[7];
	int numNo[7];
	
	for(int line = 0; line<7;line++)
	{
		numYes[line] = yeses[line][0] - '0';
		numNo[line] = nos[line][0] - '0';
	}
	
	// sorting
	int tmp = 0;
	for(int i = 0; i<7; i++)
	{
		for(int j = 0; j<7 - i - 1; j++)
		{
			if(numYes[j] > numYes[j+1])
			{
				tmp = numYes[j];
				numYes[j] = numYes[j+1];
				numYes[j+1] = tmp;
			}
		}
	}
	
	tmp = 0;
	for(int i = 0; i<7; i++)
	{
		for(int j = 0; j<7 - i - 1; j++)
		{
			if(numNo[j] > numNo[j+1])
			{
				tmp = numNo[j];
				numNo[j] = numNo[j+1];
				numNo[j+1] = tmp;
			}
		}
	}
	
	puts("Median of the number of yeses :");
	printf("%i\n", (numYes[3]));
	
	puts("Median of the number of nos :");
	printf("%i\n", (numNo[3]));
	
	// standard sampleDeviationn
	
	float sum3 = 0;
	for (int i = 0; i < 7; i++)
    sum3 = sum3 + (((float)numYes[i]) - ((float)(sum1/7))) * (((float)numYes[i]) - ((float)(sum1/7)));

    float sampleDeviation1 = sqrt((sum3 / (6)));
	
	puts("Standard Sample Deviation of  the number of yeses");
	printf("%f\n", (sampleDeviation1));
	
	float sum4 = 0;
	for (int i = 0; i < 7; i++)
    sum4 = sum4 + (((float)numNo[i]) - ((float)(sum2/7))) * (((float)numNo[i]) - ((float)(sum2/7)));

    float sampleDeviation2 = sqrt((sum4 / (6)));
	
	puts("Standard Sample Deviation of  the number of nos");
	printf("%f\n", (sampleDeviation2));
	
	//  population sample deviation
	
	float popDeviation1 = sqrt((sum3 / (7)));
	float popDeviation2 = sqrt((sum4 / (7)));
	
	puts("Population Sample Deviation of  the number of yeses");
	printf("%f\n", (popDeviation1));
	puts("Population Sample Deviation of  the number of nos");
	printf("%f\n", (popDeviation2));

	
	
	// Mode
	
		
		
}

void pattern0()
{
 char prnt = '*';
 int i, j, k, s, sp, nos = 0, nosp = -1;
 for (i = 9; i >= 3; (i = i - 2)) {
  for (s = nos; s >= 1; s--) {
   printf("  ");
  }
  for (j = 1; j <= i; j++) {
printf("%2c", prnt);
}
for (sp = nosp; sp >= 1; sp--) {
   printf("  ");
  }
  for (k = 1; k <= i; k++) {
 if (i == 9 && k == 1) {
continue;
}
printf("%2c", prnt);
}
nos++;
nosp = nosp + 2;
printf("\n");
}
nos = 4;
for (i = 9; i >= 1; (i = i - 2)) {
  for (s = nos; s >= 1; s--) {
   printf("  ");
  }
  for (j = 1; j <= i; j++) {
   printf("%2c", prnt);
  }
  nos++;
  printf("\n");
 }
}
int triangle(int nos, int i) {
 char prnt = '*';
 int s, j;
 for (s = nos; s >= 1; s--) {    // Spacing factor
  printf("  ");
 }
 for (j = 1; j <= i; j++) {      //The inner loop
  printf("%2c", prnt);
 }
 return 0;
}

void pattern1() {
 int i, nos = 5;
 //draws the upper triangle
 for (i = 1; i <= 4; i++) {
 triangle(nos, i);    //Inner loop construction
 nos++;              // Increments the spacing factor
 printf("\n");  }
nos = 7;  //Draws the lower triangle skipping its base.
for (i = 3; i >= 1; i--) {
  int j = 1;
  triangle(nos, i);  // Inner loop construction
  nos = nos - j;     // Spacing factor
  printf("\n");
 }
}
int triangle1(int nos, int i, int skip) {
 char prnt = '*';
 int s, j;
 for (s = nos; s >= 1; s--) {
  printf("  ");
 }
 for (j = 1; j <= i; j++) {
 if (skip != 0) {
 if (i == 9 && j == 1) {
   continue;
 }
 }
if (i == 1 || i == 9) {
 printf("%2c", prnt);
}
else if (j == 1 || j == i) {
 printf("%2c", prnt);
 } else {
 printf("  ");
}  }
return 0; }
void pattern() {
int i, nos = 0, nosp = -1, nbsp = -1;
for (i = 9; i >= 1; (i = i - 2)) {
  triangle1(nos, i, 0);
  triangle1(nosp, i, 1);
  triangle1(nbsp, i, 1);
  printf("\n");
  nos++;
  nosp = nosp + 2;
  nbsp = nbsp + 2;
 }
 nos = 3, nosp = 5, nbsp = 5;
 for (i = 3; i <= 9; (i = i + 2)) {
  triangle1(nos, i, 0);
  triangle1(nosp, i, 1);
  triangle1(nbsp, i, 1);
  printf("\n");
  nos--;
  nosp = nosp - 2;
  nbsp = nbsp - 2;
 }
}
void patternintro() {
 char prnt = '*';
 int i, j, k, s, nos = -1;
 for (i = 5; i >= 1; i--) {
  for (j = 1; j <= i; j++) {
 printf("%2c", prnt);
}
for (s = nos; s >= 1; s--) {
   printf("  ");
  }
  for (k = 1; k <= i; k++) {
   if (i == 5 && k == 5) {
    continue;
   }
   printf("%2c", prnt);
  }
  nos = nos + 2;
  printf("\n");
 }
 nos = 5;
 for (i = 2; i <= 5; i++) {
  for (j = 1; j <= i; j++) {
 printf("%2c", prnt);
}
for (s = nos; s >= 1; s--) {
   printf("  ");
  }
  for (k = 1; k <= i; k++) {
   if (i == 5 && k == 5) {
    break;
   }
   printf("%2c", prnt);
  }
  nos = nos - 2;
  printf("\n");
 }
}
int main()
{
	initializeQues();
	initializeAns();
	initializeOptions();
	patternintro();
	puts(" ");
	puts(" ");
	puts(" ");
	puts(" ");
	puts("HI! WELCOME TO WASTE MANAGEMENT SYSTEM, CANADA!");
	puts(" ");
	puts(" ");
	puts(" ");
	puts(" ");
	for(int i = 0; i<7;i++) {
		if(i%2 == 0)
			pattern0();
		else
			pattern1();
	askQuestion(ques[i]);
	}

    puts("Do you want me to display the stastics");
	char input[4];
	gets(input);
	if((strcmp(input,"Yes") == 0) || (strcmp(input,"yes") == 0) || (strcmp(input,"YES") == 0))
		printStatistic();
	pattern();
	puts("THANK YOU FOR YOUR TIME! HAVE A TRASHFREE DAY!");
}
