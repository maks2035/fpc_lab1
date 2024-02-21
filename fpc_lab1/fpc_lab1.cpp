#include "fpc_lab1.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;
using namespace std::chrono;
mutex mtx;

void calculateFactorial(int start, int end, unsigned __int64& result)
{
   long long partialResult = 1;
   for (int i = start; i <= end; i++)
   {
      partialResult *= i;
   }

   mtx.lock();
   result *= partialResult;
   mtx.unlock();
}

int main()
{
   int num = -1;
   int num_threads = -1;

   while (num < 0 or num > 65) {
      cout << "Enter a number to calculate factorial: ";
      cin >> num;
   }
   if (num == 1 or num == 0) {
      cout << "Factorial of " << num << " is: " << 1 << endl;
      return 0;

   }

   while (num_threads < 1 or num_threads > 3) {
      cout << "Enter number of threads (1, 2 or 3): ";
      cin >> num_threads;
   }


   //high_resolution_clock::time_point start = high_resolution_clock::now();

   vector <unsigned __int64> results(3, 1);

   if (num_threads == 1) {
      high_resolution_clock::time_point start = high_resolution_clock::now();
      thread tr1([first = 1, second = num, third = &results[0]] {calculateFactorial(first, second, *third); });

      tr1.join();
      high_resolution_clock::time_point end = high_resolution_clock::now();
      nanoseconds duration = duration_cast<nanoseconds>(end - start);
      cout << "Time taken:" << duration.count() << " nanoseconds" << endl;
   }

   else if (num_threads == 2) {
      high_resolution_clock::time_point start = high_resolution_clock::now();
      thread tr1([first = 1, second = num / 2, third = &results[0]] {calculateFactorial(first, second, *third); });
      thread tr2([first = num / 2 + 1, second = num, third = &results[1]] {calculateFactorial(first, second, *third); });

      tr1.join();
      tr2.join();
      high_resolution_clock::time_point end = high_resolution_clock::now();
      nanoseconds duration = duration_cast<nanoseconds>(end - start);
      cout << "Time taken:" << duration.count() << " nanoseconds" << endl;
   }

   else if (num_threads == 3) {
      high_resolution_clock::time_point start = high_resolution_clock::now();
      thread tr1([first = 1, second = num / 3, third = &results[0]] {calculateFactorial(first, second, *third); });
      thread tr2([first = num / 3 + 1, second = 2 * num / 3, third = &results[1]] {calculateFactorial(first, second, *third); });
      thread tr3([first = 2 * num / 3 + 1, second = num, third = &results[2]] {calculateFactorial(first, second, *third); });

      tr1.join();
      tr2.join();
      tr3.join();
      high_resolution_clock::time_point end = high_resolution_clock::now();
      nanoseconds duration = duration_cast<nanoseconds>(end - start);
      cout << "Time taken:" << duration.count() << " nanoseconds" << endl;
   }

   unsigned long long result = results[0] * results[1] * results[2];
   cout << "Factorial of " << num << " is: " << result << endl;

   return 0;
}
