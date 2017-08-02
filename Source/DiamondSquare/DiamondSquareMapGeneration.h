// Copyright (c) 2017, Vadim Petrov - MIT License

#pragma once

#include <vector>
#include <map>

class DiamondSquareMapGeneration
{
public:

	DiamondSquareMapGeneration(int size);

	void generateWorld();

	double fRand2(double fMin, double fMax);

	void timeReset();

	void init_blocks_cords(DiamondSquareMapGeneration algorithm);

	void setScaleASmooth(int scale, int smooth);

	std::map<int, std::vector<std::vector<double>>> getBlocks();

	std::vector<std::vector<double>> tiles;
	int worldSize; // Only the power of two + 1

	// ����� ������� ������ � ���� id ����� � ������ ����� � id ����� � � ������������
	// ��� ������� � ����������� ����� � ���������� ��� �����
	std::map<int, std::map<int, std::vector<double>>> hmBlocks;
	// id ����� � ���������� 4 �����
	std::map<int, std::vector<double>> hmCoord;
	// final set of drawing blocks, block id - point id - x || y || z
	std::map<int, std::vector<std::vector<double>>> finalMapOfBlocks;
	// final set of drawing blocks, block id - point id - x || y || z with smooth
	std::map<int, std::vector<std::vector<double>>> finalMapOfBlocksWithSizeASmooth;
};