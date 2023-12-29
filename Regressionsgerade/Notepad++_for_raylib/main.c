//made in "Notepad++ for raylib"

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <math.h>

double getratio(double Xval[], double Yval[], int ValAmount, double *minmaxvalues);
int drawing(double Xval[], double Yval[], int ValAmount, double *minmaxvalues, double *drawLine);
int drawAverageLine(double Xval[], double Yval[], int ValAmount, double *lineVal);
    
int main(int argc, char **argv){
    FILE *file;
    double xValues[100];
    double yValues[100];
    int step=0;

    file = fopen("test.csv", "r");
    
    if (file == NULL){
        printf("Error openimg the file\n");
        return 1;
    }
    do{
        fscanf(file, "%lf, %lf", &xValues[step], &yValues[step]);
        step++; 
    }while(!feof(file));

    fclose(file);

    //get ratio
    double *minmaxData;
    minmaxData = malloc(sizeof(double)*4); //maxX, maxY, minX, minY
    getratio(xValues, yValues, step, minmaxData);
    for (int i=0; i<4; i++){
           printf("Data: %lf\n", minmaxData[i]);
    }
    
    //drawing stuff
    double *lineValues;
    lineValues = malloc(sizeof(double)*2);
    drawAverageLine(xValues, yValues, step, lineValues);
    printf("\ny = %lf x + (%lf)\n", lineValues[0], lineValues[1]);
    
    drawing(xValues, yValues, step, minmaxData, lineValues);
    
    return 0;
}

int drawing(double Xval[], double Yval[], int ValAmount, double *minmaxvalues, double *drawLineAverage){
    InitWindow(1000,700,"graph plotting");
    Color linecolor = {100, 100, 100, 255}; 
    double xPos, yPos;
    int offset = 50;

    double Xgetmaxtoratio = 900 / (minmaxvalues[0] - minmaxvalues[2]);
    double Ygetmaxtoratio = 600 / (minmaxvalues[1] - minmaxvalues[3]);
    
    int y1 = (((drawLineAverage[0]*minmaxvalues[3]) - minmaxvalues[3]) + drawLineAverage[1])*Ygetmaxtoratio;
    int y2 = (((drawLineAverage[0]*minmaxvalues[1]) - minmaxvalues[3]) + drawLineAverage[1])*Ygetmaxtoratio;
    int y1true = GetScreenHeight() - y1 - offset;
    int y2true = GetScreenHeight() - y2 - offset;
    
    int trueXvalue = GetScreenWidth()-offset;
    printf("comair Extern: %d\n", GetScreenHeight()-offset);
    printf("y2true Extern: %d\n", y2true);
    if (y2true>(GetScreenHeight()-offset)){
        double m = (y2true-y1true)/(GetScreenWidth() - 2*offset);
        double n = y1true - (m*offset);
        trueXvalue = (GetScreenWidth()-offset-n)/m;
        y2true = GetScreenHeight()-offset;
        printf("trueXvalue: %lf\n", trueXvalue);
    }
            
    while (!WindowShouldClose()){

        BeginDrawing();

            DrawLine(50, GetScreenHeight()-50, GetScreenWidth()-50, GetScreenHeight()-50, BLACK);
            DrawLine(50, GetScreenHeight()-50, 50, 50, linecolor);
            
            

            ClearBackground(RAYWHITE);
            DrawText("Graph plotter: ", 420, 20, 20, LIGHTGRAY);
            for (int i=0; i<ValAmount; i++){
                xPos = ((Xval[i]-minmaxvalues[2]) * Xgetmaxtoratio) + offset;
                yPos = GetScreenHeight() - ((Yval[i]-minmaxvalues[3]) * Ygetmaxtoratio) - offset;
                
                DrawCircle(xPos, yPos, 2, BLACK);
               
                char drawValueX[10]; char drawValueY[10];
                snprintf(drawValueX, sizeof(drawValueX), "%.1lf", Xval[i]);
                snprintf(drawValueY, sizeof(drawValueX), "%.1lf", Yval[i]);
                
                DrawText(drawValueX, xPos, GetScreenHeight()-45, 5, BLACK);
                DrawText(drawValueY, 20, yPos, 5, BLACK);
            }
            
            //Check, so dass der Graph nicht in den 4ten Quadranten geht
            
           //  y =        m            *       x          +          n
            
            //printf("\n y1true: %lf  +  y2true: %lf\n", y2true, y1true);
            
            DrawLine(offset, y1true, trueXvalue, y2true, GRAY);
            
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

double getratio(double Xval[], double Yval[], int ValAmount, double *minmaxvalues){
    
     double currMaxX= Xval[0], currMaxY= Yval[0];
     double currMinX= Xval[0], currMinY= Yval[0];

    for (int i=0; i<ValAmount; i++){
        if (Xval[i]>=Xval[i+1] && Xval[i]>=currMaxX) {currMaxX = minmaxvalues[0] = Xval[i];}// maxX
        if (Yval[i]>=Yval[i+1] && Yval[i]>=currMaxY) {currMaxY = minmaxvalues[1] = Yval[i];}// maxY
        if (Xval[i]<=Xval[i+1] && Xval[i]<=currMinX) {currMinX = minmaxvalues[2] = Xval[i];}// minX
        if (Yval[i]<=Yval[i+1] && Yval[i]<=currMinY) {currMinY = minmaxvalues[3] = Yval[i];}// minY 
    }
    return 0;
}

int drawAverageLine(double Xval[], double Yval[], int ValAmount, double *lineVal){
    double MwY=0, MwX=0;
    double sumY=0, sumX=0, SAsumX=0, SAsumY=0, m=0, n=0;
    double KovarianzProdukt=0, DiffKovarianz=0;
    double Xsqu=0, Ysqu=0,XYprod=0;



    for (int i=0; i<ValAmount; i++){
        sumX += Xval[i];
        sumY += Yval[i];
    }
    MwX = sumX / ValAmount;  //Mittelwerte
    MwY = sumY / ValAmount;
    
    for (int i=0; i<ValAmount; i++){
        SAsumX += (Xval[i]-MwX)*(Xval[i]-MwX); 
        SAsumY += (Yval[i]-MwY)*(Yval[i]-MwY);
        
        KovarianzProdukt += (Xval[i]-MwX) * (Yval[i]-MwY);
        
        Xsqu += Xval[i]*Xval[i];
        Ysqu += Yval[i]*Yval[i];
        XYprod += Xval[i] * Yval[i];
    }


    DiffKovarianz = KovarianzProdukt / (ValAmount); //Kovarianz
    
    double Korrelation = (XYprod-ValAmount*MwX*MwY)/(sqrt(Xsqu-(ValAmount*(MwX*MwX)))*sqrt(Ysqu-ValAmount*(MwY*MwY))); //Korrelation
    //double Korrelation = DiffKovarianz / (MwX*MwY);
    double XStandartA = sqrt(SAsumX / ValAmount); //Standartabweichung
    double YStandartA = sqrt(SAsumY / ValAmount);
    
    lineVal[0] = m = (YStandartA/XStandartA)*(Korrelation);
    lineVal[1] = n = ((-1)*(YStandartA/XStandartA)*(Korrelation)*MwX)+MwY;
    
    printf("ValAmount: %d\nMittelwerte:\nMwX: %lf\nMwY: %lf\nKovarianz: %lf\nKorrelation: %lf\nStandartabweichungen:\nXStandart: %lf\nYStandart: %lf\n", ValAmount, MwX, MwY, DiffKovarianz, Korrelation, XStandartA, YStandartA);
    //printf("in funk: f(x) = %lf x + (%lf)\n", lineVal[0], lineVal[1]);
    
    
    return 0;

}







