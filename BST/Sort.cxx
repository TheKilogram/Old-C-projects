#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> // std::setprecision
#include <stdio.h> // printf()
#include <time.h>  // clock();
#include <cstdlib> // rand()

using namespace std;

#include "BST.h"

void PrintNode(const Node<int>* n);
void BstSort(double* arr, int n);
void SelectionSort(double* arr, int n);
bool CheckSorted(int n, double* arr1, double* arr2);
void TestSort4(int n, double* array_rand, double* array_solution);
void TestSort5(int n, double* array_rand);

int main()
{
    srand(10);

    {
        cout << "Test 1: build BST" << endl;
        string str, sol;
        //////////////////////////////////////////////////////
        // build binary search tree of the following form   //
        //              10                                  //
        //            /    \                                //
        //           5      20                              //
        //         /   \      \                             //
        //        2     7      30                           //
        //       / \   / \    /                             //
        //      1   4 6   8  25                             //
        //         /                                        //
        //        3                                         //
        //////////////////////////////////////////////////////
        BST<int> bst;   str = bst.ToString(); sol = "()"                                             ;  cout << "        init      is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert(10); str = bst.ToString(); sol = "(10)"                                           ;  cout << "     1) insert 10 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 5); str = bst.ToString(); sol = "(5,10,_)"                                       ;  cout << "     2) insert  5 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert(20); str = bst.ToString(); sol = "(5,10,20)"                                      ;  cout << "     3) insert 20 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 2); str = bst.ToString(); sol = "((2,5,_),10,20)"                                ;  cout << "     4) insert  2 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 1); str = bst.ToString(); sol = "(((1,2,_),5,_),10,20)"                          ;  cout << "     5) insert  1 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 7); str = bst.ToString(); sol = "(((1,2,_),5,7),10,20)"                          ;  cout << "     6) insert  7 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 4); str = bst.ToString(); sol = "(((1,2,4),5,7),10,20)"                          ;  cout << "     7) insert  4 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 6); str = bst.ToString(); sol = "(((1,2,4),5,(6,7,_)),10,20)"                    ;  cout << "     8) insert  6 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert(30); str = bst.ToString(); sol = "(((1,2,4),5,(6,7,_)),10,(_,20,30))"             ;  cout << "     9) insert 30 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 8); str = bst.ToString(); sol = "(((1,2,4),5,(6,7,8)),10,(_,20,30))"             ;  cout << "    10) insert  8 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert( 3); str = bst.ToString(); sol = "(((1,2,(3,4,_)),5,(6,7,8)),10,(_,20,30))"       ;  cout << "    11) insert  3 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        bst.Insert(25); str = bst.ToString(); sol = "(((1,2,(3,4,_)),5,(6,7,8)),10,(_,20,(25,30,_)))";  cout << "    12) insert 25 is "; if(str == sol) cout << "success: structure is " << str << endl; else cout << "failure: " << str << "!=" << sol << endl;
        cout << "      expected structure: " << sol << endl;
        cout << "    your final structure: " << str << endl;
        cout << "    The above two outputs shuld be the same to each other!" << endl;

        cout << endl;
        cout << "Test 2: search elements" << endl;
        cout << "     1) search 10 in BST: "; if (bst.Search(10) != NULL) cout << "success <- found"       << endl; else cout << "failure <- cannot find 10"                     << endl;
        cout << "     2) search 25 in BST: "; if (bst.Search(25) != NULL) cout << "success <- found"       << endl; else cout << "failure <- cannot find 25"                     << endl;
        cout << "     3) search  4 in BST: "; if (bst.Search( 4) != NULL) cout << "success <- found"       << endl; else cout << "failure <- cannot find  4"                     << endl;
        cout << "     4) search  7 in BST: "; if (bst.Search( 7) != NULL) cout << "success <- found"       << endl; else cout << "failure <- cannot find  7"                     << endl;
        cout << "     5) search  0 in BST: "; if (bst.Search( 0) == NULL) cout << "success <- cannot find" << endl; else cout << "failure <- found  0 that should not be in BST" << endl;
        cout << "     6) search  9 in BST: "; if (bst.Search( 9) == NULL) cout << "success <- cannot find" << endl; else cout << "failure <- found  9 that should not be in BST" << endl;
        cout << "     7) search 15 in BST: "; if (bst.Search(15) == NULL) cout << "success <- cannot find" << endl; else cout << "failure <- found 15 that should not be in BST" << endl;
        cout << "     8) search 50 in BST: "; if (bst.Search(50) == NULL) cout << "success <- cannot find" << endl; else cout << "failure <- found 50 that should not be in BST" << endl;

        cout << endl;
        cout << "Test 3: print preorder" << endl;
        cout << "    expected output: 10,5,2,1,4,3,7,6,8,20,30,25," << endl;
        cout << "        your output: "; bst.Preorder(PrintNode); cout << endl;
        cout << "    The above two outputs shuld be the same to each other!" << endl;

        cout << endl;
        cout << "Test 4: print postorder" << endl;
        cout << "    expected output: 1,3,4,2,6,8,7,5,25,30,20,10," << endl;
        cout << "        your output: "; bst.Postorder(PrintNode); cout << endl;
        cout << "    The above two outputs shuld be the same to each other!" << endl;

        cout << endl;
        cout << "Test 5: print inorder" << endl;
        cout << "    expected output: 1,2,3,4,5,6,7,8,10,20,25,30," << endl;
        cout << "        your output: "; bst.Inorder(PrintNode); cout << endl;
        cout << "    The above two outputs shuld be the same to each other!" << endl;
        cout << "    Additionally, both outputs should be sorted!" << endl;
    }

    cout << endl;
    cout << "Test 6: compare sorting results by selection sort and by building BST" << endl;
    try
    {
        cout << "    1) sorting { 1 }" << endl;
        double rand_array  [] = { 1 };
        double sorted_array[] = { 1 };
        int    n = 1;
        TestSort4(n, rand_array, sorted_array);
        cout << "       Success" << endl;
    }
    catch(const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    2) sorting { 1, 0, 2 })" << endl;
        double rand_array  [] = { 1, 0, 2 };
        double sorted_array[] = { 0, 1, 2 };
        int    n = 3;
        TestSort4(n, rand_array, sorted_array);
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    3) sorting { 2, 0, 2, 1, 4 })" << endl;
        double rand_array  [] = { 2, 0, 2, 1, 4 };
        double sorted_array[] = { 0, 1, 2, 2, 4 };
        int    n = 5;
        TestSort4(n, rand_array, sorted_array);
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    4) sorting { 0, 2, 1, 9, 3, 8, 6, 3, 5, 4, 9, 7, 1, 5 })" << endl;
        double rand_array  [] = { 0, 2, 1, 9, 3, 8, 6, 3, 5, 4, 9, 7, 1, 5 };
        double sorted_array[] = { 0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 8, 9, 9 };
        int    n = 14;
        TestSort4(n, rand_array, sorted_array);
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    cout << endl;
    cout << "Test 7: compare sorting times by selection sort and by building BST" << endl;
    try
    {
        cout << "    1) sorting 10 random values" << endl;
        int     n = 10;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    2) sorting 100 random values" << endl;
        int     n = 100;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    3) sorting 500 random values" << endl;
        int     n = 500;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    4) sorting 1000 random values" << endl;
        int     n = 1000;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    5) sorting 5000 random values" << endl;
        int     n = 5000;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    6) sorting 10000 random values" << endl;
        int     n = 10000;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    7) sorting 50000 random values" << endl;
        int     n = 50000;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    try
    {
        cout << "    8) sorting 100000 random values" << endl;
        int     n = 100000;
        double* rand_array = new double[n];
        for (int i = 0; i < n; i++)
            rand_array[i] = rand();
        TestSort5(n, rand_array);
        delete[] rand_array;
        cout << "       Success" << endl;
    }
    catch (const char* message)
    {
        cout << "       Failed: " << message << endl;
    }

    cout << endl;
    cout << "Copy the results of \"Test 7\" and paste it in your readme file," << endl;
    cout << "  and write a discussion about which sorting method is better" << endl;
    cout << "  when its input size is large." << endl;
    cout << endl;

    return 0;
}

void PrintNode(const Node<int>* n)
{
    cout << n->GetValue() << ",";
}

bool CheckSorted(int n, double* arr1, double* arr2)
{
    // compare if two arrays have the same elements in order
    for (int i = 0; i < n; i++)
        if (arr1[i] != arr2[i])
            return false;
    // compare if the elements in arr1 are sorted
    for (int i = 0; i < n - 1; i++)
        if (arr1[i] > arr1[i + 1])
            return false;

    return true;
}

void TestSort4(int n, double* array_rand, double* array_solution)
{
    // create two arrays
    double* arr_bst = new double[n];
    double* arr_sel = new double[n];

    // assign the random numbers to the two arrays
    for (int i = 0; i < n; i++)
    {
        arr_bst[i] = array_rand[i];
        arr_sel[i] = array_rand[i];
    }

    // call two sorting functions
    BstSort(arr_bst, n);
    SelectionSort(arr_sel, n);

    // print outputs
    cout << "       input        : "; for (int i = 0; i < n; i++) cout << array_rand    [i] << ","; cout << endl;
    cout << "       solution     : "; for (int i = 0; i < n; i++) cout << array_solution[i] << ","; cout << endl;
    cout << "       BstSort      : "; for (int i = 0; i < n; i++) cout << arr_bst       [i] << ","; cout << endl;
    cout << "       SelectionSort: "; for (int i = 0; i < n; i++) cout << arr_sel       [i] << ","; cout << endl;

    // test if the sorted results are correct
    if (CheckSorted(n, arr_bst, arr_sel) == false)
        throw "selection sort result is not the same to result of sorting using BST";

    // test if the sorted results are the same to the solution
    if (array_solution != NULL)
        if (CheckSorted(n, arr_bst, array_solution) == false)
            throw "sorting result is not the same to the solution";
}

void TestSort5(int n, double* array_rand)
{
    // create two arrays
    double* arr_bst = new double[n];
    double* arr_sel = new double[n];

    // assign the random numbers to the two arrays
    for (int i = 0; i < n; i++)
    {
        arr_bst[i] = array_rand[i];
        arr_sel[i] = array_rand[i];
    }

    // call two sorting functions
    clock_t t1 = clock();
    BstSort(arr_bst, n);
    clock_t t2 = clock();
    SelectionSort(arr_sel, n);
    clock_t t3 = clock();

    // print times spent to call the two functions
    printf("       BstSort      (..) takes %1.6f secs\n", (((double)t2 - t1) / CLOCKS_PER_SEC));
    printf("       SelectionSort(..) takes %1.6f secs\n", (((double)t3 - t2) / CLOCKS_PER_SEC));

    // test if the sorted results are correct
    if (CheckSorted(n, arr_sel, arr_bst) == false)
        throw "selection sort result is not the same to result of sorting using BST";
}

double* BSTSort_arr = NULL;     // array sorted by BST
int     BSTSort_n   = -1;       // size of array
int     BSTSort_cnt = -1;       // number of used elements in BSTSort_arr
void AddToBstSortArr(const Node<double>* n)
{
    // add elements visited by in-order traversal into array sorted by BST
    if (BSTSort_cnt >= BSTSort_n)
        throw "index out of range exception in AddToBstSortArr()";
    BSTSort_arr[BSTSort_cnt] = n->GetValue();
    BSTSort_cnt++;
}
void BstSort(double* arr, int n)
{
    // allocate BSTSort_arr
    BSTSort_arr = new double[n];
    BSTSort_n   = n;
    BSTSort_cnt = 0;

    // build BST with arr
    BST<double> bst;
    for (int i = 0; i < n; i++)
        bst.Insert(arr[i]);

    // run in-order traversal
    bst.Inorder(AddToBstSortArr);

    // copy elements in the sorted array into arr
    for (int i = 0; i < n; i++)
        arr[i] = BSTSort_arr[i];

    // delete BSTSort_arr
    delete[] BSTSort_arr;
    BSTSort_arr = NULL;
    BSTSort_n   = -1;
    BSTSort_cnt = -1;
}

void SelectionSort(double* arr, int n)
{
    ///////////////////////////////////////////
    // Do not change the above.
    // Implement function body
    
    double tmp,*i,*j;
    double *last;
	
	last=arr+n-1;

	for(i =arr; i<last; i++)
	{
		for(j=i+1;j<=last; j++)
		{
			if(*i>*j)
			{
				

				tmp=*i;
				*i=*j;
				*j=tmp;
				
			}
		}
		
		
	}
    // Implement function body
    ///////////////////////////////////////////
}
