#include <iostream>
#include <ctime>
#include<cstdlib>
#include<chrono>
#include<fstream>
using namespace std;
using namespace std::chrono;
// We use this record to be returned by the function  that finds
// the maximum sub-array.
struct MaxSubArrayRecord {
	int startIndex;
	int endIndex;

	// Holds the sum of all the elements within  the  sub-array.
	long totalSum;
};

MaxSubArrayRecord MaxSubArrayBrute(int array[], int startIndex, int endIndex, int totalSum);
void RandomArray(int array[], int size);
int sizeOfArray = 0;

int main()
{
	cout << "Enter the size of Array: ";
	cin >> sizeOfArray;
	int* array = new int[sizeOfArray];			// array for storing the numbers
	RandomArray(array, sizeOfArray);			// fills the array with random generated numbers
	MaxSubArrayRecord result;

	high_resolution_clock::time_point startTime, stopTime;
	startTime = high_resolution_clock::now();			// returns the start time before the function call
	result=MaxSubArrayBrute( array,0,sizeOfArray-1,0);
	stopTime = high_resolution_clock::now();			// returns the stop time after the function call
	cout << "The maximum sub-array: \n";
	cout << "Start index: " << result.startIndex <<endl;
	cout << "  End index: " << result.endIndex <<endl;
	cout << "  Total Sum: " << result.totalSum <<endl;
	cout << "============================================\n";
	auto duration = duration_cast<microseconds>(stopTime - startTime).count();       // Compute the duration in microseconds
	cout << "Time taken by function : "<< duration << " Microseconds" << endl;

	ofstream output;
	output.open("BruteForceSubArray.csv");				// save the sorted array in csv file
	if (output.is_open())
	{
		for (int i = 0; i < sizeOfArray; ++i)
		{
			output << array[i] << endl;
		}
	}
	output.close();
	delete[]array;
	return 0;
}

MaxSubArrayRecord MaxSubArrayBrute(int array[],int startIndex,int endIndex,int totalSum)
{
    // Initialization
    startIndex = 0;
	endIndex = 0;
	totalSum = array[0];
    int sum;
	MaxSubArrayRecord res;
	for (int i = 0; i < sizeOfArray; i++) {
		// initialize the current sum with 0
		sum = 0;
		for (int j = i; j < sizeOfArray; j++) {
			// update the sum
			sum += array[j];

			if (sum > totalSum) {
				totalSum = sum;
				startIndex = i;
				endIndex = j;
			}
		}
	}

	// Load the data
	res.startIndex = startIndex;
	res.endIndex = endIndex;
	res.totalSum = totalSum;

	// return the record.
	return res;
}

void RandomArray(int array[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] = rand() % sizeOfArray;
	}
}