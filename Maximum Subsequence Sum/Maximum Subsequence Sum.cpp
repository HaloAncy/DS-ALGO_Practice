#include<iostream>
#define MaxSize 10005
using namespace std;

/*优化暴力 O(n2)*/
int MaxSubseqSum2(int A[], int N) {
	int MaxSum = 0;
	for (int i = 0; i < N; i++) {
		int ThisSum = 0;
		for (int j = i; j < N; j++) {
			ThisSum += A[j];
			if (ThisSum > MaxSum) MaxSum = ThisSum;
		}
	}
	return MaxSum;
}

/*分治 O(nlogn)*/
int Maxfrom3(int A, int B, int C) {
	return A > B ? (A > C ? A : C) : (B > C ? B : C);
}

//left、right指向数组下标
int DivideAndConquer(int A[], int left, int right) {
	//终止条件
	if (left == right) {
		//如果序列中所有整数皆为负数，则输出0。
		if (A[left] > 0) return A[left];
		else return 0;
	}
	int center = (left + right) / 2;
	int MaxLeftSum = DivideAndConquer(A, left, center);
	int MaxRightSum = DivideAndConquer(A, center + 1, right);
	
	//跨分界线
	int MaxLeftBorderSum = 0, LeftBorderSum = 0;
	for (int i = center; i >= left; i--) {
		LeftBorderSum += A[i];
		if (LeftBorderSum > MaxLeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;
	}
	int MaxRightBorderSum = 0, RightBorderSum = 0;
	for (int i = center + 1; i <= right; i++) {
		RightBorderSum += A[i];
		if (RightBorderSum > MaxRightBorderSum)
			MaxRightBorderSum = RightBorderSum;
	}

	return Maxfrom3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubseqSum3(int A[], int N) {
	return DivideAndConquer(A, 0, N);
}

/*在线处理 O(n)*/
//改进输出首位元素//
void MaxSubseqSum4(int A[], int N) {
	int MaxSum = 0, ThisSum = 0;
	int start=0, end=0;//
	int laststart = 1;//
	int zero = 0;//是否有0
	for (int i = 0; i < N; i++) {
		ThisSum += A[i];
		if (ThisSum > MaxSum) {
			MaxSum = ThisSum;
			end = i;//
			laststart = start;//
		}
		else if (ThisSum < 0) {
			ThisSum = 0;
			start = i + 1;//
		}
		else if (ThisSum == 0) zero = 1;//
	}
	//所有数字均为负，定义最大和为0，并且输出序列的第一个和最后一个数字
	if (laststart > end) {
		laststart = 0;
		end = N - 1;
	}//
	//最大和为0且存在0，输出0 0 0
	if (zero == 1 && MaxSum == 0) {
		A[laststart] = 0;
		A[end] = 0;
	}//
	cout << MaxSum << " " << A[laststart] << " " << A[end] << endl;//
	//return MaxSum;
}

/*动态规划 O(n) 
dp[n] = max(0, dp[n-1]) + num[n]
dp[n]表示以第n个数结尾的最大连续子序列的和
*/
int DPMaxSubseqSum(int A[], int N) {
	int MaxSum = A[0];
	//改变了数组元素
	for (int i = 1; i < N; i++) {
		if (A[i - 1] > 0) A[i] += A[i - 1];
		if (A[i] > MaxSum) MaxSum = A[i];
	}
	return MaxSum;
}

/*其他优化：放弃K数组，直接处理输入
利用sum数组（连续几项的和）*/

//全局区数组可以开很大
int K[MaxSize];
int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> K[i];
	//cout << MaxSubseqSum2(K, N);
	//cout << MaxSubseqSum3(K, N-1);
	MaxSubseqSum4(K, N);
	//cout << DPMaxSubseqSum(K, N);
	return 0;
}