#include "camera.h"

typedef enum{A,B,C}fuzzy_subset_enum;
// 模糊子集的相关隶属度
static float u(fuzzy_subset_enum subset,uint8 L1,uint8 L2,uint8 L3,uint8 L4)
{
	float u;
	switch (subset)
	{
		case A:
			break;
		case B:
			break;
		case C:
			break;
		defult:break;
	}
	return u;
}

// 模糊OSTU实现图象二值化
uint8_t binaryzation(uint8_t *image,uint16_t column,uint16_t row)
{
	uint8 rise_Flag = 0,down_Flag = 0,max = 0, min = 255,max_index = 0,min_index = 0;
	uint8 peak_index[4],bottom_index[4],threshold = 0;
	uint16_t height = row,length = column,histogram[256];
	uint8_t *p = image;
	
	for (int i = 0;i < 256;i++)
	{
		histogram[i] = 0;
	}
	
	for (int i =0;i < 4;i++)
	{
		peak_index[i] = 0,bottom_index[i] = 0;
	}
	
	// 遍历得到灰度直方图
	for (int i = 0;i < length;i++)
	{
		for (int j = 0;j < height;j++)
		{
			histogram[*(p + (i - 1) * length + j)]++;
		}
	}
	
	// 得到灰度直方图的谷点与峰点
	for (int i = 1;i < 256;i++)
	{
		if (histogram[i] > histogram[i - 1]&&histogram[i + 1] > histogram[i])
		{
			rise_Flag = 1,down_Flag = 0,min = 255;
			if (bottom_index[0] != 0 || min_index != 0)
			{
				if (bottom_index[0] == 0)	 bottom_index[0] = min_index;
				else if (bottom_index[1] == 0)		bottom_index[1] = min_index;
				else if (bottom_index[2] == 0)		bottom_index[2] = min_index;
				else if (bottom_index[3] == 0)		bottom_index[3] = min_index;
			}
		}
		else if (histogram[i] < histogram[i - 1]&&histogram[i + 1] < histogram[i])
		{
			down_Flag = 1,rise_Flag = 0,max = 0;
			if (peak_index[0] == 0)	 peak_index[0] = max_index;
			else if (peak_index[1] == 0)		peak_index[1] = max_index;
			else if (peak_index[2] == 0)		peak_index[2] = max_index;
			else if (peak_index[3] == 0)		peak_index[3] = max_index;
		}
		if ((rise_Flag)&&histogram[i] > max)	max = histogram[i],max_index = i;
		else if ((down_Flag)&&histogram[i] < min)	min = histogram[i],min_index = i;
	}
	
	// 实现模糊OSTU得到二值化的阈值
	// 区域A：蓝色底布	区域B：反光		区域C：白色赛道
	uint8 peak_num = 0,L1,L2,L3,L4,bottom_peak01_index,bottom_peak12_index,Left_Peak_Flag = 0;
	float variance = 0.0,area_A_proporation = 0.0,area_B_proporation = 0.0;
	float area_C_proporation = 0.0,aver_grey_degree_A = 0.0,aver_grey_degree_B = 0.0;
	float aver_grey_degree_C = 0.0;
	for (int i = 0;i < 4;i++)
	{
		if (peak_index[i] != 0)		peak_num++;
	}
	
	if (peak_num == 2)// 双峰图像可以直接对峰值取平均值
		threshold = (peak_index[0] + peak_index[1])/2;// 我觉得这里就算做整数除法问题也不大
	else if (peak_num == 3)// 对三峰图象使用模糊算法
	{
		A:
		for (int i = 0;i < 4;i++)
		{
			if (histogram[bottom_index[i]] < histogram[peak_index[0]]&& \
				histogram[bottom_index[i]] > histogram[peak_index[1]])
				bottom_peak01_index = bottom_index[i];
			else if (histogram[bottom_index[i]] < histogram[peak_index[1]]&& \
				histogram[bottom_index[i]] > histogram[peak_index[2]])
				bottom_peak12_index = bottom_index[i];
		}
		int left_peak_num = 0,bottom_aver_index;
		for (int i = 0;i < 3;i++)
		{
			bottom_aver_index = (bottom_peak01_index + bottom_peak12_index)/2;
			if (peak_index[i] <= bottom_aver_index)		left_peak_num++;
		}
		if (left_peak_num >= 2)		Left_Peak_Flag = 1;
		if (Left_Peak_Flag)
		{
			L4 = histogram[peak_index[2]],L3 = bottom_aver_index,L1 = histogram[peak_index[0]];
			for (L2 = L1;L2 < L3;L2++)
			{
				
			}
		}
		else
		{
			
		}
	}
	else if (peak_num == 4)// 四峰图像就应该是把其中相聚最近的两个峰合并成一个峰
	{
		int distance[3];
		for (int i = 0;i < 3;i++)
		{
			distance[i] = peak_index[i + 1] - peak_index[i];
		}
		
		// 改变数组满足三峰图象
		if (distance[0] <= distance[1]&&distance[0] <= distance[2])
			peak_index[1] = peak_index[2],peak_index[2] = peak_index[3];
		else if (distance[1] <= distance[0]&&distance[1] <= distance[2])
		{
			if (distance[0] <= distance[2])
				peak_index[2] = peak_index[3];
			else
				peak_index[1] = peak_index[2],peak_index[2] = peak_index[3];
		}
		else if (distance[2] <= distance[0]&&distance[2] <= distance[1])
			peak_index[2] = peak_index[3];
		goto A;
	}
	
	return threshold;
}
