#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void sizeSum(double x1[], double y1[], int size);
//double funcCal(double xVal, bool ch, double *c, int size);
void CalcLoser(double oldM, double *MM);

enum choice {pos, neg, neu};

int fileinput(char filename[]){
    
    int i=0, a, q=0;
    char name[1000];
    double x[100];
    double y[100];

    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL){
        printf("Error reading file\n");
        return 1;
    }else{
        do{
            fscanf(file,"%lf, %lf\n", &x[i], &y[i]);
            i++;
        }while (!feof(file));
    }
    fclose(file);
    sizeSum(x, y, i);
}






void sizeSum(double x[], double y[], int size){ //calc Size of deltaY
    double m; double *pm = &m;
    double y1=0, y2=0, sum1=0, sum2=0, truesum=0;
    double *MM = malloc(sizeof(int)*2); MM[0]=-1; MM[1]=1;
    int count=0;

    do{
        printf("\n\nSum: %lf vs %lf\n", sum1, sum2);
        printf("--truesum: %lf\n", truesum);
        printf("m: MM[0]= %lf, MM[1]= %lf\n", MM[0], MM[1]);

        for (int i=0; i<size; i++){
            //y1 = funcCal(x[i], 1, pm, size);
            //y2 = funcCal(x[i], 0, pm, size);
             
            printf("y: y1= %lf, y2= %lf\n", y1, y2);

            y1 = MM[0]*x[i];
            y2 = MM[1]*x[i];

            sum1 += abs(y[i] - y1); //integral value
            sum2 += abs(y[i] - y2);
        }

        if (sum1<sum2){
            CalcLoser(MM[0], MM);
            truesum = sum1;
        }else{
            CalcLoser(MM[1], MM);
            truesum = sum2;
        }
        count++; 


    }while(count < 10); // truesum to check for if it's good enough
    free(MM);
}
/*
double funcCal(double xVal, bool ch, double *c, int size){ //Calc new Graphs
    static double m1=1, m2=-1, repeat=1, Numamout=0;
    double y=0;
    
    if (repeat == 0 && *c == 1){
        m1 = m1*2;
        m2 = m1*0.5;
        repeat = 1;
        printf("switch1\n");
    }else if(repeat == 0 && *c == 0){
        m1 = m2*0.5;
        m2 = m2*2;
        repeat = 1;
        printf("switch2\n");

    }
    Numamout++;
    if (Numamout == size){ Numamout = 0; repeat=0;} 

    
    if (ch){
        y = m1*xVal;
    }else{
        y = m2*xVal;
    }
    return y;
}

double funcCal(double xVal, int size, double *MM){


    return y;
}
*/
/*
double CalcWinner(double oldM){
    double m;
    m = oldM * 2;
    return m;
}*/
void CalcLoser(double oldM, double *MM){
    double m;
    double x=2, y, xNew, yNew;
    double winM = oldM * 2;
    y = winM * x;

    xNew = (x-winM*y)/(1+pow(winM, 2));
    yNew = ((2*winM*x)+y*(1-pow(winM, 2))) / (1+pow(winM, 2));

    m = yNew / xNew;
    MM[0] = winM;
    MM[1] = m;

}