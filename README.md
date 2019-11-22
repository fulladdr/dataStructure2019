# 2019-Data-Structure
CSE3080 DS Assignments Spring Semester

HW1.

#1 

숫자들로 이루어진 string이 주어졌을 때, 숫자들의 순서를 바꾸지 않고 가능한 모든 partition을 출력하는 C 프로그램을 recursion을 이용하여 작성하시오.


  ex. 1234 -> 1/2/3/4, 1/2/34, 1/23/4, 1/234, 12/3/4, ...
  
  
 
#2 

0-9까지의 숫자를 포함하는 string과 target이 주어졌을 때, 주어진 string과 binary operator +, -, *만을 사용하여 계산 결과가 target인 수식을 만드는 놀이를 하려 한다. 예를 들어, string 123과 target 6이 주어졌을 때 만들 수 있는 수식은 1+2+3, 1*2*3의 두 가지가 된다. target을 만드는 가능한 모든 수식을 출력하는 C 프로그램을 recursion을 이용하여 작성하시오. 이 때, 주어진 string의 순서는 바꾸지 않는다.


  ex. 123 6 -> 1+2+3 = 6, 1*2*3 = 6
  ex. 123 7 -> 1*2+5, 12-5
  ex. 1 1 -> 1
  ex. 123 4 -> none
  ex. 234 14 -> 2+3*4
  ex. 1001 -> 1+0+0+1, 1+0-0+1, 1+0*0+1, 1-0+0+1, 1-0-0+1, 1-0*0+1
  
  
  
  
HW2.
 #1
 
 강의 자료의 pmatch() 함수는 KMP algorithm을 사용하여 주어진 string내에 pattern이 존재하는지를 찾아주는 함수이다.
만약 string에서 pattern이 발견되면, pmatch()는 가장 처음 pattern과 string이 matching되는 부분의 starting index를 return한다.
pmatch()를 수정하여, string과 pattern이 matching되는 모든 부분의 starting indices를 출력하는 함수 pmatch_all()을 작성하라

 #2 Array을 parameter로 받은 후, 연속된 숫자만이 저장되어 있는지 확인하는 함수 check_array()를 만들고자 한다. 예를 들어, {4, 1, 5, 2, 3}와 같은 array의 경우에는 1부터 5까지의 연속적인 숫자들이 저장되어 있으므로, check_array()가 1을 return하도록 한다. 그러나 {10, 14, 12, 15, 11, 9}와 같은 array의 경우에는 중간에 13이 빠져 있으므로 check_array()가 0을 return하도록 한다.
check_array()를 구현하는 데에는 여러 가지가 있지만, 가장 쉬운 방법은 배열을 먼저 sorting한 후 중간에 빠진 숫자가 있는지 찾는 것이다. 이 경우, array의 크기를 n이라 할 때, 함수의 시간 복잡도는 𝑂(𝑛𝑙𝑜𝑔𝑛)이 된다. 물론 이보다 더 나은 방법도 존재한다. 𝑂(𝑛)의 시간 복잡도를 가지도록 check_array()를 작성해보자.

HW3.
 #1 
 교재에 주어진 eval과 postfix 함수는 (Program 3.13, 3.15) +, -, /, *, % 등 5개의 operator에 한해서만 동작한다. 이를 수정하여 unary operator인 –까지 포함할 수 있도록 만들고자 한다. (단, 구분을 위해서 postfix에서는 – 대신 #로 표시한다고 가정하자.) unary operator –와 +, -, /, *, %를 포함하는 수식이 입력으로 들어왔을 때, 해당 수식을 postfix로 바꾼 결과와, postfix 식의 계산 결과를 출력하는 C 프로그램을 작성하라.
  ex. input : -6 Postfix : 6#, Result : -6
  ex. input : (1-(-3)-5) Postfix : 13#-5-, Result : -1
  
  
 #2 
 새로운 방식을 사용하여 infix를 prefix로 바꿔 보고자 한다. postfix 함수를 사용하지 않고, stack을 사용하여 infix 수식을 prefix 수식으로 바꾸어 주는 C 프로그램을 작성하라
  ex. Infix: 3*8+7/1 Prefix: +*38/71 
  ex. 5-99 Invalid expression
  
  
HW4.
  #1 
  Given a sparse matrix in "input.txt" file, write a program that reads the matrix by the linked representation as in Figure 4.19, and computes the transpose of the matrix, and writes the answer into "output.txt" file. The input and output format is to be explained later. 
    ex.예제 입력 (input.txt) 4 5 6 0 2 11 0 4 6 1 0 12 1 1 7 2 1 -4 3 3 -15 
    출력 (output.txt) 5 4 6 0 1 12 1 1 7 1 2 -4 2 0 11 3 3 -15 4 0 6
  
  
  #2 
  Write a C program to manage SNS friends using equivalence classes. Your program should be able to deal with the following commands: 
  ▪ P <name> : Create a person record of the specified name. You may assume that no two people have the same name. ▪ F <name1> <name2> : Record that the two specified people are friends. ▪ U <name1> <name2> : Record that the two specified people are no longer friends. ▪ L <name> : Print out the friends of the specified person. ▪ Q <name1> <name2> : Check whether the two people are friends. If so, print “Yes”; if not, print “No” ▪ X : Terminate the program.



HW5.
  #1 
  Write insertion and deletion functions for a max heap represented as a linked binary tree. Assume that each node has a parent field as well as the usual left child, right child, and key fields.
  
  
  #2
  Write a C program to construct binary search tree from given preorder traversal, and perform inorder and postorder traversal on it.
  
HW6.
  #1
  Write a complete code that outputs all of the connected components of an undirected graph 𝐺 = (𝑉,𝐸). The graph does not have self-loops and multiple occurrences of the same edge. An input text file that has an adjacency matrix of a graph is given. Your program needs to read the input file and transform the adjacency matrix into the adjacency list representation and then your DFS should work on the graph represented by the adjacency list.
 
  
  #2 
  Write a C program that finds a minimum cost spanning tree using Kruskal’s algorithm. 
