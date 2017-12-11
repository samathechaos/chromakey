CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name: Sama Manchanda

Email Address: samamanc@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | ( 58  , 132   , 121   )  |  n/a
Arm                  | ( 255  , 155   , 103   )  |
Vest                 | ( 26  , 31   , 27   )  |
Shirt                | ( 254  , 213   , 243   )  |

================================== Review ===================================
1. Discuss and justify which pixels you chose to compute the average 
background value for method 1. Was there a reason not to choose more or
fewer pixels?

Response 1: I chose the square in the top right of the screen from 0-50 across and down because it was part of the background in every one of the images we were testing. In the astro one, it had details of the most amount of the gray pixels i could get in the background without compromising and adding too many more green pixels. I didn't want to use more pixels because I thought that if i increased the square further, i would include more green in my average when i wanted the grey to have a higher weightage in the average since there are inconsistencies for astro. 

2. For method 1, do some experiments to find the range of distance thresholds 
for which the program seems to operate the best. You may use different 
thresholds for the two different sample images (Colbert and Bird). 
Note: threshold values that are too low will cause certain portions of the 
chroma key to stay in the picture; values that are too high will cause parts 
of the foreground image to disappear.

Response 2:

  Image                  Min Threshold           Max Threshold
  Colbert range:  from   75   to 85
  Bird range:     from   45   to 95


3. For method 2, explain what you implemented and why.  How did you go about 
implementing it? Walk us through a high-level description of what you did in 
your code (and use comments in the actual .cpp file to fill in the details). 
What other alternatives did you consider either before or after you
implemented your selected method?  What are the relative pros and cons of 
these methods? [This question is open-ended!]

Response 3:

For method 2, my method essentially automatically computes a threshold and does a similar comparison as is done in method 1. I took the distance from the average background pixel to every single pixel in the image and stored those values in an array. I then took the average of every distance multiplied that value by 1.5. This became my new threshold value. From here, I compared each pixel distance to the threshold value and the pixels whose distance were above the threshold were considered foreground while the distances whose distances were equal to or below the threshold value were considered background pixels.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:

Do you have any other remarks?

: 