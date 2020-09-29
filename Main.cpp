/*  Program: Project 2
    Author: Idenia Ayala
    Class: CSCI 230
    Date: 4/20/20
    Description:

    I certify that the code below is my own work.

     Exception(s): N/A

*/

#include <iostream>
#include <string>
#include <fstream>
#include "Sorting.h"
#include "Comparator.h"
using namespace std;

int main()
{

     cout << "Author: Idenia Ayala\n\n";

     string sort;   // holds sorting algorithm
     string file_name;   // holds name of file to read input file

     cout << "Enter name of file\n";         // enter file name to open
     cin >> file_name;

    Sorting<int, string, Comparator> S(file_name);    // use when doing <int, string> pairs
  // Sorting<string, int, Comparator> S(file_name);    // uncomment when doing <string, int> pairs

   ofstream outFile("integer-key.txt");      // create output txt file
  // ofstream outFile("string-key.txt");     // uncomment when doing <string, int> pairs

     // run through all test cases at one go      // comment out for large txt file
     auto start1 = chrono::steady_clock::now();        
     S.insertionSort();                                               // insertion sort
     auto end1 = chrono::steady_clock::now();
     auto time1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);   // gets run time
     S.report(outFile, "Insertion-Sort", time1);                      // outputs report

     auto start2 = chrono::steady_clock::now();    
     S.mergeSort();                                                   // merge sort
     auto end2 = chrono::steady_clock::now();
     auto time2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
     S.report(outFile, "Merge-Sort", time2);

     auto start3 = chrono::steady_clock::now();
     S.quickSort();                                                   // quicksort
     auto end3 = chrono::steady_clock::now();
     auto time3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3);
     S.report(outFile, "Quick-Sort", time3);

     auto start4 = chrono::steady_clock::now();
     S.quickSort3();;                                                 // quicksort3
     auto end4 = chrono::steady_clock::now();
     auto time4 = chrono::duration_cast<chrono::milliseconds>(end4 - start4);
     S.report(outFile, "Quick-Sort3", time4);

     auto start5 = chrono::steady_clock::now();
     S.heapSort();                                                    // heap sort
     auto end5 = chrono::steady_clock::now();
     auto time5 = chrono::duration_cast<chrono::milliseconds>(end5 - start5);
     S.report(outFile, "Heap-Sort", time5);

     auto start6 = chrono::steady_clock::now();
     S.shellSort();                                                   // shell sort
     auto end6 = chrono::steady_clock::now();
     auto time6 = chrono::duration_cast<chrono::milliseconds>(end6 - start6);
     S.report(outFile, "Shell-Sort", time6);

     outFile.close();

     cout << "Output text file created.\n"; // output relevant info for input data to a txt file
     
     /*
     do {                                  // will output txt file for each chosen sorting method

          cout << "\nEnter sorting algorithm or enter q to quit\n";      //  enter sorting method 
          cin >> sort;
          cout << endl;
          if (sort == "insertion-sort") {
               auto start = chrono::steady_clock::now();
               S.insertionSort();
               auto end = chrono::steady_clock::now();
               auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
               S.report(sort, time);
          }
          if (sort == "merge-sort") {
               auto start = chrono::steady_clock::now();
               S.mergeSort();
               auto end = chrono::steady_clock::now();
               auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
               S.report(sort, time);
          }
          if (sort == "quick-sort") {
               auto start = chrono::steady_clock::now();
               S.quickSort();
               auto end = chrono::steady_clock::now();
               auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
               S.report(sort, time);
          }
          if (sort == "quick-sort3") {
               auto start = chrono::steady_clock::now();
               S.quickSort3();;
               auto end = chrono::steady_clock::now();
               auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
               S.report(sort, time);
          }
          if (sort == "heap-sort") {
               auto start = chrono::steady_clock::now();
               S.heapSort();
               auto end = chrono::steady_clock::now();
               auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
               S.report(sort, time);
          }
          if (sort == "shell-sort") {
               auto start = chrono::steady_clock::now();
               S.shellSort();
               auto end = chrono::steady_clock::now();
               auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
               S.report(sort, time);
          }
     }
     while (sort != "q");
     */

     return 0;
}