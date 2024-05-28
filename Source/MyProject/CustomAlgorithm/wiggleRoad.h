#pragma once
template <typename T>
class RandArray
{
private:
	TArray<T> Array;
	int size=0;
public:
	RandArray<T>()
	{
		size=0;
		Array=TArray<T>();
	}
	void push(T elem)
	{
		Array.Add(elem);
		size++;
	}
	T pop()
	{
		
		size--;
		int32 RandomIndex = FMath::RandRange(0, size);
		T RemovedTile = Array[RandomIndex];
		Array.RemoveAt(RandomIndex);
		return RemovedTile;
	}
	bool empty()
	{
		return size==0;
	}
	TArray<T> getArray()
	{
		return Array;
	}
};

struct   Tile
{
	int X;
	int Y;
	Tile(int X,int Y):X(X),Y(Y){};
};

class wiggleRoad
{
	int sizeX;
	int sizeY;
	int start;
	int exit;
	int**array;
	RandArray<Tile>Neighbours;
	RandArray<Tile>Result;
public:
	wiggleRoad(int32 sizeX,int32 sizeY,int32 start,int32 exit)
	:start(start),exit(exit),sizeX(sizeX),sizeY(sizeY),
	Neighbours(), Result()
	{
		array = new int*[sizeX];
		for (int i = 0; i < sizeX; ++i) {
			array[i] = new int[sizeY];
		}
	}
	TArray<Tile> callculate()
	{
		array = new int*[sizeX];
		for (int i = 0; i < sizeX; ++i) {
			array[i] = new int[sizeY];
		}
		populateArray();
		callculateRoad();
		DeleteArray();
		return Result.getArray();
	}
private:
	void populateArray()
	{
		for (int i = 0; i < sizeX; ++i) {
			for (int j = 0; j < sizeY; ++j) {
				array[i][j] = 0;
			}
		}
		array[start][0]=3;
		Result.push(Tile(start,0));
		array[exit][sizeY-1]=3;
		Result.push(Tile(exit,sizeY-1));
		for (int32 Row = 0; Row < sizeX; ++Row)
		{
			if(Row!=start)
			{
				array[Row][0]= (Row-start)<0?1:2;
				Neighbours.push(Tile(Row,0));
			}
			if(Row!=exit)
			{
				array[Row][sizeY-1]= (Row-exit)<0?1:2;
				Neighbours.push(Tile(Row,sizeY-1));
			}
		}
		for (int32 Column = 1; Column < sizeY-1; ++Column)
		{
			array[0][Column]=1;
			Neighbours.push(Tile(0,Column));
			array[sizeX-1][Column]=2;
			Neighbours.push(Tile(sizeX-1,Column));
		}
	}
	void callculateRoad()
	{
		while (!Neighbours.empty())
		{
			Tile tile= Neighbours.pop();
			int x = tile.X;
			int y = tile.Y;
			int index = array[x][y];
			if(index==3)
				continue;
			array[x][y]=-1;
			for (int i = -1; i < 2; ++i)
			{
				for (int j = -1; j < 2; ++j)
				{
					int newX=(x+i);
					int newY=(y+j);
					if(newX<0||newX==sizeX||newY<0||newY==sizeY)
						continue;
					int index2 =array[newX][newY];
					if(index2==0)
					{
						array[newX][newY]=index;
						Neighbours.push(Tile(newX,newY));
					}
					else if(index2==index||index2==3||index2==-1)
					{
						continue;
					}
					else if(index2==(index==2?1:2))
					{
						array[newX][newY]=3;
						Result.push(Tile(newX,newY));
					}
				}
			}
			
		}
		for (int i = 0; i < sizeX; ++i)
		{
			FString rowValues;
			for (int j = 0; j < sizeY; ++j)
			{
				rowValues += FString::FromInt(array[i][j]+1) + TEXT(" ");
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *rowValues);
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

class Maze
{
	int sizeX;
	int sizeY;
	int start;
	int exit;
	int**array;
	RandArray<Tile>Neighbours;
	RandArray<Tile>Result;
public:
	Maze(int32 sizeX,int32 sizeY,int32 start,int32 exit)
	:start(start),exit(exit),sizeX(sizeX),sizeY(sizeY),
	Neighbours(), Result()
	{
		array = new int*[sizeX];
		for (int i = 0; i < sizeX; ++i) {
			array[i] = new int[sizeY];
		}
	}
	TArray<Tile> callculate()
	{
		array = new int*[sizeX];
		for (int i = 0; i < sizeX; ++i) {
			array[i] = new int[sizeY];
		}
		populateArray();
		callculateRoad();
		DeleteArray();
		return Result.getArray();
	}
private:
	void populateArray()
	{
		for (int i = 0; i < sizeX; ++i) {
			for (int j = 0; j < sizeY; ++j) {
				array[i][j] = 0;
			}
		}
		array[start][0]=-1;
		array[exit][sizeY-1]=-1;
		for (int32 Row = 0; Row < sizeX; ++Row)
		{
			if(Row!=start)
			{
				//array[Row][0]= 0;
				Neighbours.push(Tile(Row,0));
			}
			if(Row!=exit)
			{
				//array[Row][sizeY-1]= 0;
				Neighbours.push(Tile(Row,sizeY-1));
			}
		}
		for (int32 Column = 1; Column < sizeY-1; ++Column)
		{
			array[0][Column]=1;
			Neighbours.push(Tile(0,Column));
			array[sizeX-1][Column]=1;
			Neighbours.push(Tile(sizeX-1,Column));
		}
	}
	void callculateRoad()
	{
		while (!Neighbours.empty())
		{
			Tile tile= Neighbours.pop();
			int x = tile.X;
			int y = tile.Y;
			int index = array[x][y];
			if(index==3)
				continue;
			array[x][y]=-1;
			const TArray<FVector2D> Directions = { FVector2D(0, 1), FVector2D(1, 0), FVector2D(0, -1), FVector2D(-1, 0) };
			TArray<FVector2D> empty={};
			int sum = 0;
			for (const auto& Dir : Directions) {
				FVector2D NewVector = FVector2D(x, y) + Dir;
				int newX = NewVector.X;
				int newY = NewVector.Y;
				
				if(newX<0||newX==sizeX||newY<0||newY==sizeY)
				{
					sum++;
					continue;	
				}
				int index2 =array[newX][newY];
				if(index2==2)
				{
					sum++;
					continue;
				}
				if(index2==0)
				{
					array[newX][newY]=1;
					Neighbours.push(Tile(newX,newY));
				}
				empty.Push(Dir);
			}
			if(sum==1)
			{
				for (const auto& Dir1 : empty)
				{
					for (const auto& Dir2 : empty)
					{
						if(Dir1.Equals(Dir2))
						{
							continue;
						}
						FVector2D NewVector = FVector2D(x, y) + Dir1+Dir2;
						int newX = NewVector.X;
						int newY = NewVector.Y;
				
						if(newX<0||newX==sizeX||newY<0||newY==sizeY)
						{
							sum++;
							continue;
						}
						int index2 =array[newX][newY];
						if(index2==2)
						{
							sum++;
						}
						
					}
				}
				if(sum==1)
				{
					array[x][y]=2;
					Result.push(Tile(x,y));
				}
			}
		}
		for (int i = 0; i < sizeX; ++i)
		{
			FString rowValues;
			for (int j = 0; j < sizeY; ++j)
			{
				rowValues += FString::FromInt(array[i][j]+1) + TEXT(" ");
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *rowValues);
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
//n*n + (n*n*(random+push))*