// warning: this program can burn your brain, time, life and many more things, check at your own risk

#include<iostream>
#include<vector>

using std::cout;

using std::cin;

using std::vector;

using std::max;

using std::min;

// approach 2

int prune(vector<int>& nums1, vector<int>& nums2, int l1, int u1, int l2, int u2, int k)
{
	// cout << '\n' << l1 << ' ' << u1 << ' ' << l2 << ' ' << u2;

	while(true)
	{
		/*
			checking if a list is empty or not, if found empty then kth
			largest element in other nonempty list is the answer
		*/
		
		if(l1 > u1)
		{
			// first list is empty

			return nums2[l2 + k - 1];
		}

		if(l2 > u2)
		{
			// second list is empty

			return nums1[l1 + k - 1];
		}

		int m = u1 - l1 + 1;	// length of list 1

		int n = u2 - l2 + 1;	// length of list 2

		int mid1 = (l1 + u1) / 2;	// mid of list 1

		int mid2 = (l2 + u2) / 2;	// mid of list 1

		// cout << "\n" << mid1 << ' ' << mid2;

		// cout << "\n" << k << ' ' << (m + n) / 2;

		if(k > (m + n) / 2)
		{
			// cout << "\nhello1";

			// cin.get();

			// kth largest element is not in the first half of the sorted(list1 + list2)
			// hence pruning some elements of first half

			if(nums1[mid1] < nums2[mid2])
			{
				// update k after pruning some smaller elements

				k -= (mid1 - l1 + 1);

				// pruning left half of array 1

				l1 = mid1 + 1;
			}
			else
			{
				// update k after pruning some smaller elements

				k -= (mid2 - l2 + 1);

				// pruning left half of array 2

				l2 = mid2 + 1;
			}
		}
		else
		{
			// cout << "\nhello2";

			// cin.get();

			// kth largest element is not in the second half of the sorted(list1 + list2)
			// hence pruning some elements of second half

			if(nums1[mid1] < nums2[mid2])
			{
				// pruning right half of array 2

				u2 = mid2 - 1;
			}
			else
			{
				// pruning right half of array 1

				u1 = mid1 - 1;
			}
		}
	}
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
	int n = nums1.size();

	int m = nums2.size();

	// cout << m << " " << n;

	if((n + m) % 2)
	{
		// odd

		int k =  (n + m + 1) / 2;

		return prune(nums1, nums2, 0, n - 1, 0, m - 1, k);
	}
	else
	{
		// even

		int k =  (n + m) / 2;

		return (prune(nums1, nums2, 0, n - 1, 0, m - 1, k) + prune(nums1, nums2, 0, n - 1, 0, m - 1, k + 1)) / 2.0;
	}
}

// approach 3

// not reliable if A and B both are empty

double findMedianSortedArrays_adv(vector<int>& A, vector<int>& B)
{
	if(A.size() > B.size())
	{
		return findMedianSortedArrays(B, A);
	}

	int m = A.size();

	int n = B.size();

	// range in array A where we look for partition_A

	int left = 0;

	int right = m;

	while(left <= right)
	{
		int partition_A = (left + right) / 2;

		int partition_B = (m + n + 1) / 2 - partition_A;	// Aleft.length + Bleft.length == (m + n + 1) / 2

		int max_A_left = (partition_A == 0) ? INT32_MIN : A[partition_A - 1];

		int min_A_right = (partition_A == m) ? INT32_MAX : A[partition_A];

		int max_B_left = (partition_B == 0) ? INT32_MIN : B[partition_B - 1];

		int min_B_right = (partition_B == n) ? INT32_MAX : B[partition_B];

		if(max_A_left <= min_B_right && max_B_left <= min_A_right)
		{
			if((m + n) % 2)
			{
				// (m + n) is odd

				// return max of the smaller half of the sorted list

				return max(max_A_left, max_B_left);
			}
			else
			{
				// (m + n) is even

				// return avg of max of the smaller half and min of the larger half of the sorted list

				return (max(max_A_left, max_B_left) + max(min_A_right, min_B_right)) / 2.0;
			}
		}
		else if(max_A_left > min_B_right)
		{
			// need to move partition_A towards left so pruning part of A right of partition_A

			right = partition_A - 1;
		}
		else
		{
			// (max_B_left > min_A_right)
			// need to move partition_A towards right so pruning part of A left of partition_A

			left = partition_A + 1;
		}
	}

	return 0.0;
}

int main()
{
	vector<int> arr1({1, 3, 4, 5}), arr2({2, 7, 8, 8, 9});

	cout << findMedianSortedArrays_adv(arr1, arr2);

	return 0;
}

// g++ median_of_two_array.cpp -o op\median_of_two_array.exe && op\median_of_two_array.exe