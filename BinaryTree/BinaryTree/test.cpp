#include"BinaryTree.h"
void TestBinaryTree1()
{
	int array1[10] = { 1, 2, 3, '#', '#', 4, '#' , '#', 5, 6 };
	int array2[15] = { 1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8 };
	BinaryTree<int> b1(array1, 10, '#');
	BinaryTree<int> b2(array2, 15, '#');
	std::cout << "µÝ¹éÏÈÐò£º";
	b1.PreOrderTraverse();
	cout << b1.Size() << endl;
	cout << "µÝ¹éÖÐÐò£º";
	b1.InOrderTraverse();
	cout << "µÝ¹éºóÐò£º";
	b1.PostOrderTraverse();
	cout << "Find 6?" << b1.Find(6)->_data << endl;
	cout << "Find 10?" << b1.Find(10) << endl;
	cout << "b1 depth:" << b1.Depth() << endl;
	b1.TierOrderTraverse();
	cout << "µÝ¹éÏÈÐò£º";
	b2.PreOrderTraverse();
	cout << "b2 size:" << b2.Size() << endl;
	cout << "µÝ¹éÖÐÐò£º";
	b2.InOrderTraverse();
	cout << "µÝ¹éºóÐò£º";
	b2.PostOrderTraverse();
	cout << "b2 depth:" << b2.Depth() << endl;
}

void TestBinaryTree2()
{
	int array1[10] = { 1, 2, 3, '#', '#', 4, '#' , '#', 5, 6 };
	int array2[15] = { 1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8 };
	BinaryTree<int> b1(array1, 10, '#');
	BinaryTree<int> b2(array2, 15, '#');
	cout << "·ÇµÝ¹éÏÈÐò£º";
	b1.PreOrderTraverseNonR();
	cout << "·ÇµÝ¹éÖÐÐò£º";
	b1.InOrderTraverseNonR();
	cout << "·ÇµÝ¹éºóÐò£º";
	b1.PostOrderTraverseNonR();
	cout << endl;
	b1.PostOrderTraverseNonR();
	cout << "·ÇµÝ¹éÏÈÐò£º";
	b2.PreOrderTraverseNonR();
	cout << "·ÇµÝ¹éÖÐÐò£º";
	b2.InOrderTraverseNonR();
	cout << "·ÇµÝ¹éºóÐò£º";
	b2.PostOrderTraverseNonR();

	cout << b1.FindKLevel(3)<<endl;
	cout << b1.FindKLevel(2) << endl;
	cout << b1.FindKLevel(1) << endl;
}

int main()
{
	TestBinaryTree1();
	TestBinaryTree2();
	system("pause");
	return 0;
}