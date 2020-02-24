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
MaxSubArrayRecord MaxSubArray(int ARR[], int START_INDEX, int END_INDEX);
MaxSubArrayRecord MaxCross(int ARR[], int START_INDEX, int MID_INDEX, int END_INDEX);
MaxSubArrayRecord MaxSubArrayHybrid(int ARR[], int START_INDEX, int END_INDEX);

void RandomArray(int array[], int size);
int sizeOfArray = 0;
int main()
{ 
        cout << "Enter the size of Array: ";
        cin >> sizeOfArray;
        int* array = new int[sizeOfArray];			// array for storing the numbers
        RandomArray(array, sizeOfArray);			// fills the array with random generated numbers
        MaxSubArrayRecord result;
        high_resolution_clock::time_point startTime, endTime;

        cout << "Brute-force:\n";
        startTime = high_resolution_clock::now();
        
        result = MaxSubArrayBrute(array, 0, sizeOfArray - 1, 0);            // Compute the algorithm
        endTime = high_resolution_clock::now();
        
        auto duration = duration_cast<microseconds>(endTime - startTime).count();       // Compute the duration in nanoseconds
        cout << "Time taken by Brute-Force function : "<< duration << " Microseconds" << endl;

        startTime = high_resolution_clock::now();									// returns the start time before the function call
        result = MaxSubArray(array, 0, sizeOfArray - 1);
        endTime = high_resolution_clock::now();										// returns the start time after the function call
        cout << "--------------------------------------------\n";
        cout << "Recursive Method:\n";

        duration = duration_cast<microseconds>(endTime - startTime).count();			// calculate the time consumed by function
        cout << "Time taken by Recursive function : "
            << duration << " Microseconds" << endl;

        startTime = high_resolution_clock::now();									// returns the start time before the function call
        result = MaxSubArrayHybrid(array, 0, sizeOfArray - 1);
        endTime = high_resolution_clock::now();										// returns the start time after the function call
        cout << "--------------------------------------------\n";
        cout << "Hybrid Function:\n";

        duration = duration_cast<microseconds>(endTime - startTime).count();			// calculate the time consumed by function
        cout << "Time taken by Hybrid function : "
            << duration << " Microseconds" << endl;
    
	ofstream output;
	output.open("HybridMaxSubArray.csv");				// save the sorted array in csv file
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

MaxSubArrayRecord MaxSubArrayBrute(int array[], int startIndex, int endIndex, int totalSum)
{
    // Initialization
    startIndex = 0;
    endIndex = 0;
    totalSum = array[0];
    int sum;
    MaxSubArrayRecord res;
    for (int i = 0; i < sizeOfArray; i++)
    {
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

MaxSubArrayRecord MaxSubArray(int ARR[], int START_INDEX, int END_INDEX)
{
    // The base case: array of a single element
    if (END_INDEX == START_INDEX) {
        // This record would hold the resulting data
        MaxSubArrayRecord result;

        result.startIndex = START_INDEX;
        result.endIndex = END_INDEX;
        result.totalSum = ARR[START_INDEX];

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
        left = MaxSubArray(ARR, START_INDEX, midIndex);
        right = MaxSubArray(ARR, midIndex + 1, END_INDEX);
        cross = MaxCross(ARR, START_INDEX, midIndex, END_INDEX);

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

MaxSubArrayRecord MaxCross(int ARR[], int START_INDEX, int MID_INDEX, int END_INDEX)
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
    leftSum = ARR[MID_INDEX];
    currentSum = ARR[MID_INDEX];
    result.startIndex = MID_INDEX;

    // Start from the next item,
    for (int i = MID_INDEX - 1; i >= START_INDEX; i--) {
        // Add the current item
        currentSum += ARR[i];
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
    rightSum = ARR[MID_INDEX + 1];
    currentSum = ARR[MID_INDEX + 1];
    result.endIndex = MID_INDEX + 1;

    // Start from the next item,
    for (int i = MID_INDEX + 2; i <= END_INDEX; i++) {
        // Add the current item
        currentSum += ARR[i];
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

MaxSubArrayRecord MaxSubArrayHybrid(int ARR[],int START_INDEX,int END_INDEX)
{
    // The base case: the size is below the threshole
    int size = END_INDEX - START_INDEX + 1;
    if (size < 180) {
        // Call the brute-force algorithm, and return the result
        return MaxSubArrayBrute(ARR, START_INDEX,END_INDEX,0);
    }
    else {
	// Call the Recursive algorithm, and return the result
        return MaxSubArray(ARR,START_INDEX,END_INDEX);
    }
}

/*Create the Random number and fill the array */
void RandomArray(int array[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] = rand() % sizeOfArray;
	}
}
