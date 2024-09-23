/*
	if pivot index is i then sum of all the numbers before
	it is equal to the sum of all the numbers on or after it
*/

#include<iostream>

using std::cout;

int pivot(int arr[], int n)
{
	int front = 0, rear = n - 1, sumf = 0, sumr = 0;

	/*
		we need to check when front == rear as they would
		be pointing to a single element not yet checked
	*/

	while(front <= rear)
	{
		if(sumf < sumr)
		{
			// front goes ahead and add the number pointed by front index to sumf

			sumf += arr[front++];
		}
		else
		{
			// rear goes back and add the number pointed by rear index to sumr

			sumr += arr[rear--];
		}

		// cout << "\nfront:" << front << "\trear:" << rear;

		// cout << "\nsumf:" << sumf << "\tsumr:" << sumr;
	}

	if(sumf == sumr)
	{
		return front;
	}
	else
	{
		return -1;
	}
}

int main()
{
	int arr[] = {5, 1, 5, 11};

	cout << pivot(arr, sizeof(arr) / sizeof(int));
}