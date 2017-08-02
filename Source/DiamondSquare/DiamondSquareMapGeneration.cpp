// Copyright (c) 2017, Vadim Petrov - MIT License

#include "DiamondSquare.h"
#include "DiamondSquareMapGeneration.h"
#include <random>
#include <ctime>

using namespace std;

DiamondSquareMapGeneration::DiamondSquareMapGeneration(int size)
{
	vector<vector<double>> vec(size, vector<double>(size, 0));
	tiles = vec;

	worldSize = size;

	generateWorld();
}

void DiamondSquareMapGeneration::generateWorld() 
{
	timeReset();
	const float SEED = 0.0f;
	tiles[0][0] = tiles[0][worldSize - 1] = tiles[worldSize - 1][worldSize - 1] = SEED;
	double h = 0.75;
	for (int sideLength = worldSize - 1; sideLength >= 2; sideLength /= 2, h /= 2.0) {
		int halfSide = sideLength / 2;

		for (int x = 0; x < worldSize - 1; x += sideLength) {
			for (int y = 0; y < worldSize - 1; y += sideLength) {
				double avg = tiles[x][y] + tiles[x + sideLength][y] + tiles[x][y + sideLength] + tiles[x + sideLength][y + sideLength];
				avg /= 4.0;

				tiles[x + halfSide][y + halfSide] = (float)(avg + (fRand2(0, 1) * 2 * h) - h);
			}
		}

		for (int x = 0; x < worldSize - 1; x += halfSide) {
			for (int y = (x + halfSide) % sideLength; y < worldSize - 1; y += sideLength) {
				float avg =
					tiles[(x - halfSide + worldSize - 1) % (worldSize - 1)][y] + //left of center
					tiles[(x + halfSide) % (worldSize - 1)][y] + //right of center
					tiles[x][(y + halfSide) % (worldSize - 1)] + //below center
					tiles[x][(y - halfSide + worldSize - 1) % (worldSize - 1)]; //above center
				avg /= 4.0;

				avg = (float)(avg + (fRand2(0, 1) * 2 * h) - h);
				tiles[x][y] = avg;
				if (x == 0) tiles[worldSize - 1][y] = avg;
				if (y == 0) tiles[x][worldSize - 1] = avg;
			}
		}
	}
}

double DiamondSquareMapGeneration::fRand2(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void DiamondSquareMapGeneration::timeReset()
{
	srand(time(0)); //Seed the random system, important, otherwise the number the same
}

void DiamondSquareMapGeneration::init_blocks_cords(DiamondSquareMapGeneration algorithm)
{
	int block = 0, point = 0;
	for (int fill_x = 0; fill_x < algorithm.worldSize - 1; fill_x++) {
		for (int fill_y = 0; fill_y < algorithm.worldSize - 1; fill_y++, block++) {

			hmCoord.clear();
			for (int step = 0, x = fill_y, mx = fill_x, y = fill_y, z = fill_x; step <= 3; step++) {
				if (step == 2) {
					x--;
					mx++;
					y--;
					z++;
					hmCoord.insert(pair<int, vector<double> >(step, { (double)x, algorithm.tiles[mx][y], (double)z }));
				}
				else if (step == 3) {
					x--;
					y--;
					hmCoord.insert(pair<int, vector<double> >(step, { (double)x, algorithm.tiles[mx][y], (double)z }));
				}
				else {
					hmCoord.insert(pair<int, vector<double> >(step, { (double)x, algorithm.tiles[mx][y], (double)z }));
					x++;
					y++;
				}
			}
			hmBlocks.insert(pair<int, map<int, vector<double> >>(block, hmCoord));
		}
	}
}

void DiamondSquareMapGeneration::setScaleASmooth(int scale, int smooth)
{
	vector<vector<double>> blockCoords;
	vector<double> singlePointCoords;

	// блок, точка, координата
	typedef map<int, std::map<int, std::vector<double>>>::const_iterator MapIterator;
	for (MapIterator iter = hmBlocks.begin(); iter != hmBlocks.end(); iter++)
	{
		for (int i = 0; i <= 3; i++) // точки 
		{
			for (int j = 0; j <= 2; j++) // координаты
			{
				if (j == 0) // координаты
				{
					singlePointCoords.push_back(hmBlocks.at(iter->first)[i][j] * scale); // x
				}
				else if (j == 1)
				{
					singlePointCoords.push_back(hmBlocks.at(iter->first)[i][j] * smooth); // y
				}
				else if (j == 2)
				{
					singlePointCoords.push_back(hmBlocks.at(iter->first)[i][j] * scale); // z
				}
			}
			blockCoords.push_back(singlePointCoords);
			singlePointCoords.clear();
		}
		finalMapOfBlocksWithSizeASmooth.insert(pair<int, vector<vector<double>>>(iter->first, blockCoords));
		blockCoords.clear();
	}
}

std::map<int, std::vector<std::vector<double>>> DiamondSquareMapGeneration::getBlocks()
{
	return finalMapOfBlocksWithSizeASmooth;
}