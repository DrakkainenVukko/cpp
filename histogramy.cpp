
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
Mat bazowy, hsv_bazowy;
Mat obraz1, hsv_obraz1;
Mat obraz2, hsv_obraz2;
Mat polowa;

if( argc < 4 )
{
printf(" ./histogramy <obraz bazowy> <obraz1> <obraz2>\n");
return -1;
}
bazowy = imread( argv[1], 1 );
obraz1 = imread( argv[2], 1 );
obraz2 = imread( argv[3], 1 );

cvtColor( bazowy, hsv_bazowy, COLOR_BGR2HSV );
cvtColor( obraz1, hsv_obraz1, COLOR_BGR2HSV );
cvtColor( obraz2, hsv_obraz2, COLOR_BGR2HSV );
polowa = hsv_bazowy( Range( hsv_bazowy.rows/2, hsv_bazowy.rows - 1 ), Range( 0, hsv_bazowy.cols - 1 ) );

int h_bins = 50; int s_bins = 60;
int histSize[] = { h_bins, s_bins };

float h_ranges[] = { 0, 180 };
float s_ranges[] = { 0, 256 };
const float* ranges[] = { h_ranges, s_ranges };

int channels[] = { 0, 1 };

MatND hist_bazowy;
MatND hist_polowa;
MatND hist_obraz1;
MatND hist_obraz2;

calcHist( &hsv_bazowy, 1, channels, Mat(), hist_bazowy, 2, histSize, ranges, true, false );
normalize( hist_bazowy, hist_bazowy, 0, 1, NORM_MINMAX, -1, Mat() );
calcHist( &polowa, 1, channels, Mat(), hist_polowa, 2, histSize, ranges, true, false );
normalize( hist_polowa, hist_polowa, 0, 1, NORM_MINMAX, -1, Mat() );
calcHist( &hsv_obraz1, 1, channels, Mat(), hist_obraz1, 2, histSize, ranges, true, false );
normalize( hist_obraz1, hist_obraz1, 0, 1, NORM_MINMAX, -1, Mat() );
calcHist( &hsv_obraz2, 1, channels, Mat(), hist_obraz2, 2, histSize, ranges, true, false );
normalize( hist_obraz2, hist_obraz2, 0, 1, NORM_MINMAX, -1, Mat() );

for( int i = 0; i < 4; i++ )
{
int compare_method = i;
double base_bazowy = compareHist( hist_bazowy, hist_bazowy, compare_method );
double base_polowa = compareHist( hist_bazowy, hist_polowa, compare_method );
double base_obraz1 = compareHist( hist_bazowy, hist_obraz1, compare_method );
double base_obraz2 = compareHist( hist_bazowy, hist_obraz2, compare_method );
printf( "  [%d] Perfect, Base-Polowa, Base-Obraz1, Base-Obraz2 : %f, %f, %f, %f \n", i, base_bazowy, base_polowa , base_obraz1, base_obraz2 );
}
return 0;
}
