#pragma once

class wiggleRoad
{
	int sizeX;
	int sizeY;
	int start;
	int exit;
	int**array;
	
	
public:
	wiggleRoad(int32 sizeX,int32 sizeY)
	{
		array = new int*[sizeX];
		for (int i = 0; i < sizeX; ++i) {
			array[i] = new int[sizeY];
		}
	}
private:
	void populateArray()
	{
		for (int i = 0; i < sizeX; ++i) {
			for (int j = 0; j < sizeY; ++j) {
				array[i][j] = 0;
			}
		}
		for (int32 Row = 0; Row < sizeX; ++Row)
		{
			if(Row!=start)
				array[Row][0]= (Row-start)<0?1:2;
			if(Row!=exit)
				array[Row][sizeY-1]= (Row-exit)<0?1:2;
		}
		array[start][0]=3;
		array[exit][sizeY-1]=3;
		for (int32 Column = 1; Column < sizeY-1; ++Column)
		{
			array[0][Column]=1;
			array[sizeX-1][Column]=2;
		}
	}
	void DeleteArray()
	{
		for (int i = 0; i < sizeX; ++i) {
			delete[] array[i];
		}
		delete[] array;
	}
	
};
