/*********************************************************************
 File:     chromakey.cpp

 Author: Sama Manchanda

 Email address: samamanc@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and 
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
  // Image data array
  // Note:  DON'T use the static keyword except where we expressly say so.
  //        It puts the large array in a separate, fixed, area of memory. 
  //        It is bad practice. But useful until we have dynamic allocation.
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  if (argc < 6) {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold " 
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }
	
  if (readRGBBMP(argv[1], inputImage)) {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage)) {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }
  
  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
  threshold = atof(argv[3]);


  // Call Method 1 Function
  method1(inputImage,chromaMask, threshold);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage)) {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }	

  // Call Method 2 Function
  method2(inputImage,chromaMask);

  // Produce the output by calling replace()
  replace(chromaMask,inputImage,bgrndImage,outputImage);

  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage)) {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }	

  return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold)
{	

	double avgr, avgg, avgb;
	double backR, backG, backB;
	backR = 0;
	backG = 0;
	backB = 0;
	int count = 0;
	for (int i = 0; i < 50; i ++){
		for (int j = 0; j < 50; j ++){
			count ++;
			backR += inImage[i][j][0];
			backG += inImage[i][j][1];
			backB += inImage[i][j][2];
		}
	}
	avgr = backR/count;
	avgg = backG/count;
	avgb = backB/count;

	double distance;

	for(int i = 0; i < 256; i++){
		for (int j = 0; j < 256; j++){
			distance = sqrt((pow((inImage[i][j][0] - avgr),2)) + (pow((inImage[i][j][1] - avgg),2)) + (pow((inImage[i][j][2] - avgb),2)));
			if (distance > threshold){
				mask[i][j] = 1;
			}
			else{
				mask[i][j] = 0;
			}
		}
	}


}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE])  
{
	double avgr, avgg, avgb;
	double backR, backG, backB;
	backR = 0;
	backG = 0;
	backB = 0;
	int count = 0;
	for (int i = 0; i < 50; i ++){
		for (int j = 0; j < 50; j ++){
			count ++;
			backR += inImage[i][j][0];
			backG += inImage[i][j][1];
			backB += inImage[i][j][2];
		}
	}
	avgr = backR/count;
	avgg = backG/count;
	avgb = backB/count;

	double distance;
	double distArray[256][256];

	for (int i = 0; i < 256; i++){
		for (int j =0; j < 256; j++){
			distance = sqrt((pow((inImage[i][j][0] - avgr),2)) + (pow((inImage[i][j][1] - avgg),2)) + (pow((inImage[i][j][2] - avgb),2)));
			distArray[i][j] = distance;
			}
		}

	double sum = 0.0;
	double average;
	for (int i = 0; i < 256; i ++){
		for (int j = 0; j < 256; j ++){
			sum += distArray[i][j];
		}
	}
	average = sum/65536;

	for (int i = 0; i < 256; i ++){
		for (int j = 0; j < 256; j ++){
			if (distArray[i][j] > (average * 1.5) ){
					mask[i][j] = 1;
				}
			else{
				mask[i][j] = 0;
				}
		}
	}

}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image
	for (int i = 0; i < 256; i ++){
		for (int j = 0; j < 256; j ++){
			if (mask[i][j] == 1){
				outImage[i][j][0] = inImage[i][j][0];
				outImage[i][j][1] = inImage[i][j][1];
				outImage[i][j][2] = inImage[i][j][2];

			}
			else if (mask[i][j] == 0){
				outImage[i][j][0] = bgImage[i][j][0];
				outImage[i][j][1] = bgImage[i][j][1];
				outImage[i][j][2] = bgImage[i][j][2];
			}
		}
	}
}
