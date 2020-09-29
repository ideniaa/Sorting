#pragma once
#include "Entry.h"
#include "Comparator.h"
#include <iostream>
#include <type_traits>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;

template <typename K, typename V, typename C>
class Sorting
{
public:
     typedef Entry<K, V> Entry;
     Sorting(string filename);               // constructor
     // sorting algorithms
     void insertionSort();
     void quickSort();
     void mergeSort();
     void heapSort();
     void shellSort();                    // outputs text file
     // outputs relevant info report
     void report(ofstream& outFile, string sort, chrono::milliseconds time);
protected:
     // local utilities
     typename vector<Entry> unsorted;        // holds intial unsorted values
     typename vector<Entry> S;              // holds sorted vector
     C less;                                 // comparator
     void merge(vector<Entry>& in, vector<Entry>& out, int b, int m);
     void quickSortStep(int a, int b);
     void heapify(int length, int i);
private:
     int n;                             // size of file
     string file;                       // file name
     int compares = 0;                      // num of key compares
     int moves = 0;                         // num of data moves
};

template <typename K, typename V, typename C>  // constructor
Sorting<K, V, C>::Sorting(string filename)
{
     fstream myFile;
     K key;
     V value;
     myFile.open(filename);   // open file
     if (!myFile)
     {
          cout << "Error opening file.\n";
          exit(1);
     }

     // set size and file name
     if (filename == "small1k.txt")
     {
          n = 1000;
          file = "small1k.txt";
     }
     else
     {
          n = 100000;
          file = "large100k.txt"; 
     }

     while (!myFile.eof())
     {
          myFile >> key; // get key num from text file

          // must comment out this if statement when doing <string, int>
          // and leave only the code inside the else box
         if (typeid(K) == typeid(int)) {
              string v = to_string(key);    // create string value if key is int
              value = v;                    
          }
          else 
          {
               stringstream k(key);          // create int value if key is string
               int v;
               k >> v;
               value = v;
          }

          unsorted.push_back(Entry(key, value));
     }
     S = unsorted;  // copy unsorted values to vector S to be sorted by methods
     myFile.close();     // close file
}



/* Insertion Sort */

template <typename K, typename V, typename C>      // insertion-sort
inline void Sorting<K, V, C>::insertionSort()
{
     for (int i = 1; i < n; i++)
     {
          int curr = i;
          for (int j = i - 1; j >= 0; j--)
          {
               compares++;
               if (less(S[i], S[j])) 
               {
                    curr = j;
               }
               else
                    break;
          }
          if (curr != i)
          {
               for (int k = i; k > curr; k--)
               {
                    swap(S[k], S[k - 1]);
                    moves += 3;
               }
          }
     }
}



/* Quick Sort */

template <typename K, typename V, typename C>		// quick-sort S
inline void Sorting<K, V, C>::quickSort()
{
     if (S.size() <= 1) return;				// already sorted
     quickSortStep(0, S.size() - 1);		// call sort utility
}

template <typename K, typename V, typename C>
inline void Sorting<K, V, C>::quickSortStep(int a, int b) {
     if (a >= b) return;					// 0 or 1 left? done
     Entry pivot = S[b];					// select last as pivot
     int l = a; 						// left edge
     int r = b - 1;					// right edge
     while (l <= r) {
          while (l <= r && !less(pivot, S[l])) {
               l++;		// scan right till larger
               compares++;
          }
          while (r >= l && !less(S[r], pivot)) {
               r--;		// scan left till smaller
               compares++;
          }
          if (l < r) {				// both elements found
               swap(S[l], S[r]);
               moves += 3;
          }
     }							// until indices cross
     swap(S[l], S[b]);				// store pivot at l
     moves += 3;
     quickSortStep(a, l - 1);			// recur on both sides
     quickSortStep(l + 1, b);
}



/* Merge Sort */

template <typename K, typename V, typename C>		// merge-sort S
inline void Sorting<K, V, C>::mergeSort() {
     typedef vector<Entry> vect;
     vect v1(S);  vect* in = &v1;			// initial input vector
     vect v2(n);  vect* out = &v2;			// initial output vector
     for (int m = 1; m < n; m *= 2) {			// list sizes doubling
          for (int b = 0; b < n; b += 2 * m) {		// beginning of list
               merge(*in, *out, b, m);			// merge sublists
          }
          swap(in, out);				// swap input with output
          moves += 3;
     }
     S = *in;						// copy sorted array to S
}


// merge in[b..b+m-1] and in[b+m..b+2*m-1]
template <typename K, typename V, typename C>
inline void Sorting<K, V, C>::merge(vector<Entry>& in, vector<Entry>& out, int b, int m) {
     int i = b;						// index into run #1
     int j = b + m;					// index into run #2
     int n = in.size();
     int e1 = min(b + m, n);			// end of run #1
     int e2 = min(b + 2 * m, n);			// end of run #2
     int k = b;
     while ((i < e1) && (j < e2)) {
          compares++;
          if (!less(in[j], in[i]))				// append smaller to S
               out[k++] = in[i++];
          else
               out[k++] = in[j++];
     }
     while (i < e1)					// copy rest of run 1 to S
          out[k++] = in[i++];
     while (j < e2)					// copy rest of run 2 to S
          out[k++] = in[j++];
}


/* Heap Sort */

template<typename K, typename V, typename C>
inline void Sorting<K, V, C>::heapSort()
{
     for (int i = n / 2 - 1; i >= 0; i--)
          heapify(n, i);
     for (int i = n - 1; i >= 0; i--)
     {
          swap(S[i], S[0]);
          moves += 3;
          heapify(i, 0);
     }
}

template<typename K, typename V, typename C>
inline void Sorting<K, V, C>::heapify(int length, int i)
{
     int a = 2 * i + 1;
     int b = 2 * i + 2;
     int large = i;

     if (a < length && less(S[large], S[a])) {
          large = a;
          compares++;
     }
     if (b < length && less(S[large], S[b])) {
          large = b;
          compares++;
     }
     if (large != i) {
          swap(S[i], S[large]);
          moves += 3;
          heapify(length, large);
     }

}


/* Shell Sort */

template<typename K, typename V, typename C>
inline void Sorting<K, V, C>::shellSort()
{
     for (int g = (n / 2); g > 0; g /= 2)
     {
          for (int i = g; i < n; i++)
          {
               for (int j = i - g; j >= 0; j -= g)
               {
                    compares++;
                    if (less(S[j + g], S[j]))
                    {
                         swap(S[j + g], S[j]);
                         moves += 3;
                    }
                    else
                         break;
               }
          }
     }

}


template<typename K, typename V, typename C>
inline void Sorting<K, V, C>::report(ofstream& outFile, string sort, chrono::milliseconds time)
{
     outFile << "Sorting method: " << sort << endl;
     outFile << "Input file name: " << file << endl;
     outFile << "Number of values sorted: " << n << endl;
     outFile << "Key data type: " << typeid(K).name() << endl;
     outFile << "Number of key compares: " << compares << endl;
     outFile << "Number of data moves: " << moves << endl;
     outFile << "Time in milliseconds: " << time.count() << "ms" << endl;
     outFile << "First 5 entries: ";

     int m = n - 5;
     if (typeid(K) == typeid(string))
     {
          for (auto it = S.begin(); it != S.begin() + 5; it++)
          {
               outFile << "<\"" << (*it).key() << "\", " << (*it).value() << ">, ";
          }
          outFile << endl;

          outFile << "Last 5 entries: ";
          for (auto it = S.begin() + m; it != S.end(); it++)
          {
               outFile << "<\"" << (*it).key() << "\", " << (*it).value() << ">, ";
          }
          outFile << endl << endl;
     }
     else
     {
          for (auto it = S.begin(); it != S.begin() + 5; it++)
          {
               outFile << "<" << (*it).key() << ", \"" << (*it).value() << "\">, ";
          }
          outFile << endl;

          outFile << "Last 5 entries: ";
          for (auto it = S.begin() + m; it != S.end(); it++)
          {
               outFile << "<" << (*it).key() << ", \"" << (*it).value() << "\">, ";
          }
          outFile << endl << endl;
     }


     // reset key compares and data moves counters for next sorting call
     compares = 0;
     moves = 0;

     // change vector S back to unsorted values for next sorting call
     S.clear();
     S = unsorted;
}
