Name: Sama Manchanda

Email Address: samamanc@usc.edu

Chromakey Method Description: 

My method essentially automatically computes a threshold and does a comparison of every pixel in the image to this threshold. To calculate the threshold for any image, the algorithm takes the distance from the average background pixel to every single pixel in the image and stored those values in an array. 
To calculate the average background pixel amount I chose the square in the top right of the screen from 0-50 across and down because it was part of the background in every one of the images I was testing. For example, in the astro image, it had details of the most amount of the gray pixels i could get in the background without compromising and adding too many more green pixels. I didn't want to use more pixels because I thought that if i increased the square further, i would include more green in my average when i wanted the grey to have a higher weightage in the average since there are inconsistencies for astro. I then took the average of every distance multiplied that value by 1.5. This became my new threshold value. 
From here, I compared each pixel distance to the threshold value and the pixels whose distance were above the threshold were considered foreground while the distances whose distances were equal to or below the threshold value were considered background pixels.
