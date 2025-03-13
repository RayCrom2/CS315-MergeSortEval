/* program to time several versions of the merge sort algorithm on data sets of various sizes
 */

 #include <stdio.h>
 #include <stdlib.h>   // for malloc, free
 #include <time.h>     // for time
 
 /** *********************************************************************************
  * tradtional merge Sort procedure                                                  *
  * based on tutorialpoint.com:                                                      *
  *      https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort    *
  *      See URL for parameters, etc.                                                *
  *                                                                                  *
  * with slight variation that does not impact correctness                           *
  *                                                                                  *
  * this procedure merges segment [left, mid] with [mid, right] in array             * 
  *                                                                                  *
  * @param   left    left endpoint of array segment to be merged                     *
  * @param   mid     midpoint of array segment to be merged                          *
  * @param   right  right endpoint of array segment to be merged                     *
  *                                                                                  *
  * @pre  segments [left, mid] and [mid+1, right] are ordered                        *
  * @post segment [left, right] is ordered                                           *
  *                                                                                  *
  * @remark dynamic memory allocation to avoid segmentation fault                    *
  * for moderately large array size                                                  *
  *                                                                                  *
  ************************************************************************************/
 void traditionalMerge (int *array, int left, int mid, int right) {
     int i, j, k;
     int lsize = mid-left+1;     //size of left and right sub-arrays
     int rsize =  right-mid;
     
     int * larr = malloc (lsize * sizeof(int));
     int * rarr = malloc (rsize * sizeof(int));

     
     //fill left and right sub-arrays
     for(i = 0; i<lsize; i++)
         larr[i] = array[left+i];
     for(j = 0; j<rsize; j++)
         rarr[j] = array[mid+j+1];
     i = 0;
     j = 0;
     k = left;
     
     //marge temp arrays to real array
     while(i < lsize && j<rsize) {
         if(larr[i] < rarr[j]) {
             array[k] = larr[i];
             i++;
         }else{
             array[k] = rarr[j];
             j++;
         }
         k++;
     }
 
     // with one helper array completely copied, copy the other one
     while(i<lsize) {       //extra element(s) in left array
         array[k] = larr[i];
         i++;
         k++;
     }
     while(j<rsize) {       //extra element(s) in right array
         array[k] = rarr[j];
         j++;
         k++;
     }
     free(larr); free(rarr);
 }
 
 /** **************************************************************************************
  * tradtional merge Sort procedure, with left/right (start/end)parameters, renamed from  *
  * source:  tutorialpoint.com:                                                           *
  * https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort              *
  *                                                                                       *
  * this procedure oversees sorting of the segment [left, right] within array             * 
  *                                                                                       *
  * @param   left    left endpoint of array segment to be sorted                          *
  * @param   rightt  right endpoint of array segment to be sorted                         *
  *                                                                                       *
  *****************************************************************************************/
 
 void traditionalMergeHelper(int *array, int start, int end) {
     int mid;
     if (start < end) {
         int mid = start+(end-start)/2;
         // Sort first and second arrays
         traditionalMergeHelper(array, start, mid);
         traditionalMergeHelper(array, mid+1, end);
         traditionalMerge(array, start, mid, end);
     }
 }
 
 /** **************************************************************************************
  * traditional recursive merge Sort procedure                                            *
  *                                                                                       *
  * @param  arr  the array to be sorted                                                   *
  * @param  n  the size of the array                                                      *
  * @post  the first n elements of a are sorted in non-descending order                   *
  * @remark segmentation fault for n-1 >= 256000 or so                                    *
   ****************************************************************************************/
 void traditionalMergeSort  (int arr [ ], int n) {
     traditionalMergeHelper (arr, 0, n-1);
 }
 
 
 /*****************************************************************************************
  * * * * * * * * * * * * * procedures to check sorting correctness * * * * * * * * * * * *
  ****************************************************************************************/
 
 /** **************************************************************************************
  * check all array elements have values 0, 2, 4, . . ., 2(n-1)                           *
  * @param  a  the array to be sorted                                                     *
  * @param  n  the size of the array                                                      *
  * returns  "ok" if array contains required elements; "NO" if not                        *
  *****************************************************************************************/
 
 char * checkAscValues (int a [ ], int n) {
     for (int i = 0; i < n; i++) {
         if (a[i] != 2*i) {
             //printf ("%4d %4d", i, a[i]);  // index of first error
             return "Er";
         }
     }
     return "ok";
 }
 
 /** **************************************************************************************
  * check all array elements are in non-descending order                                  *
  * @param  a  the array to be sorted                                                     *
  * @param  n  the size of the array                                                      *
  * returns  "ok" if array elements in non-descending order; "NO" otherwise               *
  *****************************************************************************************/
 
 char * checkAscending (int a [ ], int n) {
     for (int i = 0; i < n-1; i++) {
         if (a[i] > a[i+1])
             return "NO";
     }
     return "ok";
 }
 
 
 /** **************************************************************************************
  * driver program for testing and timing sorting algorithms                              *
  *****************************************************************************************/
 
 int main ( ) {
     //size variables
   int minDataSetSize =   800000;
   int maxDataSetSize = 25600000;
   int algTimeLimit = 15; // do not print results after algorithm taks this long (in seconds)
 
   // randomize random number generator's seed
   srandom (time ((time_t *) 0) );
   
   // print headings
   printf ("Data Set                                Times\n");
   printf ("  Size        Ascending Order       Random Order   Descending Order      ascEcxFirTen       randomData2\n");
 
   int size;
   for (size = minDataSetSize; size <= maxDataSetSize; size *= 2) {
   //for (size = 1600000; size <= maxDataSetSize; size += 100000) {
       // create and initialize control data set arrays
      int * ascendData = (int *) malloc (size * sizeof(int));   //array with ascending data
      int * randomData = (int *) malloc (size * sizeof(int));   //array with random data
      int * descenData = (int *) malloc (size * sizeof(int));   // array with descending data
      int * ascExcFirTen = (int *) malloc (size * sizeof(int));   // array with ascending data except first 10 and last 10 are switched
      int * randomData2 = (int *) malloc (size * sizeof(int));   // array with ascending data except first 10 and last 10 are switched

 
      int i;
      for (i = 0; i< size; i++) {
         ascendData[i] = 2*i;
         randomData[i] = random();
         descenData[i] = 2*(size - i - 1); 
         ascExcFirTen[i] = 2*i;
         randomData2[i] = random();
      }
      int temp;
      for(int i = 0; i < 10; ++i){
        temp = ascExcFirTen[i];
        ascExcFirTen[i] = ascExcFirTen[(size - 1) - i];
        ascExcFirTen[(size - 1) - i] = temp;
      }
 
      // timing variables
      clock_t start_time, end_time;
      double elapsed_time;
 
      // timing for sorting algorithm
      printf ("%8d", size);
 
      // ascending data
      start_time = clock ();
      traditionalMergeSort (ascendData, size);
      end_time = clock();
      elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
      printf ("%14.1lf  %2s", elapsed_time, checkAscValues (ascendData, size));
        
      // random data
      start_time = clock ();
      traditionalMergeSort (randomData, size);
      end_time = clock();
      elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
      printf ("%15.1lf  %2s", elapsed_time, checkAscending (randomData, size));
        
      // descending data
      start_time = clock ();
      traditionalMergeSort (descenData, size);
      end_time = clock();
      elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
      printf ("%15.1lf  %2s", elapsed_time, checkAscValues (descenData, size));

      start_time = clock ();
      traditionalMergeSort (ascExcFirTen, size);
      end_time = clock();
      elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
      printf ("%15.1lf  %2s", elapsed_time, checkAscValues (ascExcFirTen, size));

      start_time = clock ();
      traditionalMergeSort (randomData2, size);
      end_time = clock();
      elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
      printf ("%15.1lf  %2s", elapsed_time, checkAscending (randomData2, size));
 
      printf ("\n");
 
      // clean up original test arrays
      free (ascendData);
      free (randomData);
      free (descenData);
      free (ascExcFirTen);
      free (randomData2);
 
   } // end of loop for testing procedures with different array sizes
 
   return 0;
 }
 
 