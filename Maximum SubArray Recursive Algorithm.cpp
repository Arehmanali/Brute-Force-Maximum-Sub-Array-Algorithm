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

MaxSubArrayRecord MaxSubArray(int array[], int START_INDEX, int END_INDEX);
MaxSubArrayRecord CrossSum(int array[], int START_INDEX, int MID_INDEX, int END_INDEX);
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
    result = MaxSubArray(array, 0, sizeOfArray - 1);
    stopTime = high_resolution_clock::now();			// returns the stop time after the function call
    cout << "The maximum sub-array: \n";
    cout << "Start index: " << result.startIndex << endl;
    cout << "  End index: " << result.endIndex << endl;
    cout << "  Total Sum: " << result.totalSum << endl;
    cout << "============================================\n";
    auto duration = duration_cast<microseconds>(stopTime - startTime).count();       // Compute the duration in microseconds
    cout << "Time taken by function : " << duration << " Microseconds" << endl;



	ofstream output;
	output.open("RecursiveMaxSubArray.csv");				// save the sorted array in csv file
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

MaxSubArrayRecord MaxSubArray(int array[],int START_INDEX,int END_INDEX)
{
    // The base case: array of a single element
    if (END_INDEX == START_INDEX) {
        // This record would hold the resulting data
        MaxSubArrayRecord result;
        
        result.startIndex = START_INDEX;
        result.endIndex = END_INDEX;
        result.totalSum = array[START_INDEX];
        return result;
    }
    else {
        
        // get the midpoint index:
        int midIndex = (START_INDEX + END_INDEX) / 2;
      
        // the records of left, right, and cross categories
        MaxSubArrayRecord left;
        MaxSubArrayRecord right;
        MaxSubArrayRecord cross;

        // Recursively, solve the sub-problems:
        left = MaxSubArray(array, START_INDEX, midIndex);
        right = MaxSubArray(array, midIndex + 1, END_INDEX);
        cross = CrossSum(array, START_INDEX, midIndex,END_INDEX);

        // Compare the resulting data:
        if (left.totalSum >= right.totalSum &&
            left.totalSum >= cross.totalSum) {
            // Return the  left sub-array, having the maximum.
            return left;
        }
        else if (right.totalSum >= left.totalSum &&
            right.totalSum >= cross.totalSum) {
            // Return the right sub-array, having the maximum.
            return right;
        }
        else {
            // Return the cross sub-array, having the maximum.
            return cross;
        }
    }
}

MaxSubArrayRecord CrossSum(int array[],int START_INDEX, int MID_INDEX, int END_INDEX)
{
    // The  maximum left and right sums of the array, before and 
    // after the midpoint.
    int leftSum = 0;
    int rightSum = 0;
    // Holds the current sum: to test the maximum sums.
    int currentSum = 0;
    // This record would hold the resulting data
    MaxSubArrayRecord result;

    // The left part of the sub-array
    // At least it would contain the first element:
    leftSum = array[MID_INDEX];
    currentSum = array[MID_INDEX];
    result.startIndex = MID_INDEX;
  
    // Start from the next item,
    for (int i = MID_INDEX - 1; i >= START_INDEX; i--) {
        // Add the current item
        currentSum += array[i];
        // If we get a bigger sum, modify the values:
        if (currentSum > leftSum) {
            leftSum = currentSum;
            result.startIndex = i;
        }
    }

    // The right part of the sub-array
    // Re-initialize it with 0
    currentSum = 0;
    // At least, it would contain the first element:
    rightSum = array[MID_INDEX + 1];
    currentSum = array[MID_INDEX + 1];
    result.endIndex = MID_INDEX + 1;

    // Start from the next item,
    for (int i = MID_INDEX + 2; i <= END_INDEX; i++) {
        // Add the current item
        currentSum += array[i];
        // If we get a bigger sum, modify the values:
        if (currentSum > rightSum) {
            rightSum = currentSum;
            result.endIndex = i;
        }
    }

    // update the sum within the record:
    result.totalSum = leftSum + rightSum;
    // return the results:
    return result;
}

void RandomArray(int array[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] = rand() % sizeOfArray;
	}
}