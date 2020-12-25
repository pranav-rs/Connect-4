//
//  main.cpp
//  Connect 4
//
//  Created by Pranav Rs on 22/06/20.
//  Copyright © 2020 Pranav Rs. All rights reserved.
//

#include <iostream>
#define ROW 6
#define COL 7
using namespace std;
//doing this because I can't use system("clear") in xcode and the other options that I read
//online are either too complicated or didn't work for me
void clrscr()
{
	int counter;
	counter=10;
	while(counter--)
		cout<<endl;
}

int checkHorizontal(int gameMatrix[ROW][COL])
{
	int rowLooper,colLooper,checkLooper,checkValue;
	for(rowLooper=ROW-1;rowLooper>=0;rowLooper--)
	{
		for(colLooper=0;colLooper<COL-3;colLooper++)
		{
			if(gameMatrix[rowLooper][colLooper]==-1)
				continue;
			checkValue=gameMatrix[rowLooper][colLooper];
			for(checkLooper=1;checkLooper<4;checkLooper++)
				if(gameMatrix[rowLooper][colLooper+checkLooper]!=checkValue)
					break;
			if(checkLooper==4)
				return checkValue;
		}
	}
	return -1;
}
int checkVertical(int gameMatrix[ROW][COL])
{
	int rowLooper,colLooper,checkLooper,checkValue;
	for(colLooper=0;colLooper<COL;colLooper++)
	{
		for(rowLooper=0;rowLooper<ROW-3;rowLooper++)
		{
			if(gameMatrix[rowLooper][colLooper]==-1)
				continue;
			checkValue=gameMatrix[rowLooper][colLooper];
			for(checkLooper=1;checkLooper<4;checkLooper++)
				if(gameMatrix[rowLooper+checkLooper][colLooper]!=checkValue)
					break;
			if(checkLooper==4)
				return checkValue;
		}
	}
	return -1;
}
int checkDiagonal(int gameMatrix[ROW][COL])
{
	int rowLooper,colLooper,checkValue,checkLooper;
	//bottom right and top left diagonal
	for(rowLooper=0;rowLooper<ROW-3;rowLooper++)
	{
		for(colLooper=0;colLooper<COL-3;colLooper++)
		{
			if(gameMatrix[rowLooper][colLooper]==-1)
				continue;
			checkValue=gameMatrix[rowLooper][colLooper];
			for(checkLooper=1;checkLooper<4;checkLooper++)
				if(gameMatrix[rowLooper+checkLooper][colLooper+checkLooper]!=checkValue)
					break;
			if(checkLooper==4)
				return checkValue;
		}
	}
	//bottom left and top right diagonal
	for(colLooper=COL-4;colLooper<COL;colLooper++)
	{
		for(rowLooper=0;rowLooper<ROW-3;rowLooper++)
		{
			if(gameMatrix[rowLooper][colLooper]==-1)
				continue;
			checkValue=gameMatrix[rowLooper][colLooper];
			for(checkLooper=1;checkLooper<4;checkLooper++)
				if(gameMatrix[rowLooper+checkLooper][colLooper-checkLooper]!=checkValue)
					break;
			if(checkLooper==4)
				return checkValue;
		}
	}
	
	return -1;
}
int checkWinner(int gameMatrix[ROW][COL],int &winner,int places[])
{
	//if we have a winner,return 1(used as condition in the do while loop in main() )
	winner=checkHorizontal(gameMatrix);
	if(winner!=-1)
		return 1;
	winner=checkVertical(gameMatrix);
	if(winner!=-1)
		return 1;
	winner=checkDiagonal(gameMatrix);
	if(winner!=-1)
		return 1;
	return 0;
}
//initialize the elements of gameMatrix to -1.
//0 and 1 are used to identify players
void initialize(int gameMatrix[ROW][COL])
{
	int rowLooper,colLooper;
	for(rowLooper=0;rowLooper<ROW;rowLooper++)
		for(colLooper=0;colLooper<COL;colLooper++)
			gameMatrix[rowLooper][colLooper]=-1;
}
//places stores the row where a move will be made for each column
//(First move for any column will be at the bottom most row)
void initialize(int places[],int size,int value)
{
	int looper;
	for(looper=0;looper<size;looper++)
		places[looper]=value;
}
//to print the matrix
void output(int gameMatrix[ROW][COL])
{
	int rowLooper,colLooper;
	clrscr();
	for(rowLooper=0;rowLooper<ROW;rowLooper++)
	{
		for(colLooper=0;colLooper<COL;colLooper++)
		{
			if(gameMatrix[rowLooper][colLooper]==-1)
				cout<<"_ ";
			else if(gameMatrix[rowLooper][colLooper]==0)
				cout<<"X ";
			else
				cout<<"O ";
		}
		cout<<endl<<endl;
	}
}
//to declare the winner
void declareWinner(int winner)
{
	if(winner==-1)
		 cout<<"Draw between players 1 and 2!!\n";
	else
		cout<<"Player "<<winner+1<<" wins\n";
}
/*
 We have two teams,Team 0 and Team 1.
 This is why the matrix is initialized to -1.
 The winner variable will check the gameMatrix. If we have a winner,the winner variable will be updated,
 and the function checkWinner will return 1.
 Then,we can just output the winner using the value in the winner variable.
 */
int main() {
	int gameMatrix[ROW][COL],places[COL],winner;
	int currentMove,currentPlayer,count;
	winner=-1;
	currentPlayer=0;
	count=0;
	initialize(gameMatrix);
	initialize(places,COL,ROW-1);
	clrscr();
	output(gameMatrix);
	do
	{
		cin>>currentMove;
		if(currentMove<1 || currentMove>7 || places[currentMove-1]<0)
		{
			clrscr();
			output(gameMatrix);
			cout<<"Invalid move!!";
			continue;
		}
		gameMatrix[places[currentMove-1]][currentMove-1]=currentPlayer;
		places[currentMove-1]--;
		count++;
		currentPlayer=1-currentPlayer;
		clrscr();
		output(gameMatrix);
	}while(!checkWinner(gameMatrix,winner,places) && count<ROW*COL);
	output(gameMatrix);
	declareWinner(winner);
	return 0;
}
