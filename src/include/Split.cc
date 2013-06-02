#include "Split.hh"

cSplit::cSplit()
{
  diff = 5;
}
void cSplit::findSentenceBoundary(cBitmap * bmp)
{
	int s_width = bmp->getWidth();
	int s_height = bmp->getHeight();
	int top_found = 0;
	int start_top, start_left;
	int height, width;
	Pixel prev, cur;

	for(int i = 0; i < s_height; i++)
	{
		int count = 0;
		for(int j = 0; j < s_width; j++)
		{
			if(j == 0)
			{
				bmp->getPixel(j, i, prev);
			}
			else
			{
				bmp->getPixel(j, i, cur);
				//The conditions of decision making. Need to be checked.
				if(top_found == 0)
				{
					//The upper boundary of a sentence should have an extreme change of pixel
					if((abs(cur.r - prev.r) > diff) || (abs(cur.g - prev.g) > diff) || (abs(cur.b - prev.b) > diff))
					{
						start_top = i;
						top_found = 1;
						if(start_left == -1)
						{
							start_left = j;
						}
						else if(j < start_left)
						{
							start_left = j;
						}
						break;
					}
					else
					{
						prev.r = cur.r;
						prev.g = cur.g;
						prev.b = cur.b;
						prev.a = cur.a;
					}
				}
				else
				{
					//Decide the real left boundary
					if((abs(cur.r - prev.r) > diff) && (abs(cur.g - prev.g) > diff) && (abs(cur.b - prev.b) > diff))
					{
						if(j < start_left)
						{
							start_left = j;
						}
						break;
					}
					else//Find the bottom boundary if count == s_width - 1
					{
						prev.r = cur.r;
						prev.g = cur.g;
						prev.b = cur.b;
						prev.a = cur.a;
						count++;
					}
				}
			}
		}
		if(count == s_width - 1) //j == 0 was used to be the "prev"
		{
			int right_most = 0;
			height = i - start_top;
			for(int k = start_top; k < (start_top + height); k++)
			{
				for(int l = s_width - 1; l >= 0; l--)
				{
					if(l == s_width - 1)
					{
						bmp->getPixel(l, k, prev);
					}
					else
					{
						bmp->getPixel(l, k, cur);
						//Find the right boundary of an sentence
						if((abs(cur.r - prev.r) > diff) || (abs(cur.g - prev.g) > diff) || (abs(cur.b - prev.b) > diff))
						{
							if(l > right_most)
							{
								right_most = l;
							}
							break;
						}
						else
						{
							prev.r = cur.r;
							prev.g = cur.g;
							prev.b = cur.b;
							prev.a = cur.a;
						}
					}
				}
			}
			width = right_most - start_left;
			FontBoundary sentence_a;
			sentence_a.top = start_top;
			sentence_a.left = start_left;
			sentence_a.right = start_left + width;
			sentence_a.bottom = start_top + height;
			sentences.push_back(sentence_a);
			top_found = 0;
		}
	}
	return;
}
void cSplit::extract(cBitmap * bmp)
{
	int left_found = 1;
	int start_left, start_top = -1;
	Pixel prev, cur;
	int width;
	for( unsigned int i = 0; i < sentences.size(); i++)
	{
		start_left = sentences[i].left;
		start_top = sentences[i].top;
		int s_height = sentences[i].bottom - sentences[i].top;
		vector<FontBoundary> vec;
		for(int j = sentences[i].left; j < sentences[i].right; j++)
		{
			int count = 0;
			for(int k = sentences[i].top; k < sentences[i].bottom; k++)
			{
				if(k == sentences[i].top)
				{
					bmp->getPixel(j, k, prev);
				}
				else
				{
					bmp->getPixel(j, k, cur);
					if(left_found == 0)
					{
						//The left boundary should suffer an extreme change of pixel
						if((abs(cur.r - prev.r) > diff) && (abs(cur.g - prev.g) > diff) && (abs(cur.b - prev.b) > diff))
						{
							start_left = j;
							left_found = 1;
							break;
						}
						else
						{
							prev.r = cur.r;
							prev.g = cur.g;
							prev.b = cur.b;
							prev.a = cur.a;
						}
					}
					else
					{
						//The right boundary of a character should be homogeneous
						if((abs(cur.r - prev.r) > diff) || (abs(cur.g - prev.g) > diff) || (abs(cur.b - prev.b) > diff))
						{
							break;
						}
						else
						{
							prev.r = cur.r;
							prev.g = cur.g;
							prev.b = cur.b;
							prev.a = cur.a;
							count++;
						}
					}
				}
			}
			if(count == s_height - 1) //j == 0 was used to be the "prev"
			{
				width = j - start_left;
				FontBoundary sentence_a;
				sentence_a.top = start_top;
				sentence_a.left = start_left;
				sentence_a.right = start_left + width;
				sentence_a.bottom = sentences[i].bottom;
				vec.push_back(sentence_a);
				left_found = 0;
			}
		}
		characters.push_back(vec);
	}
}

void cSplit::getSentences( FontBoundary & s, unsigned int i ){
 s = sentences[i];
}

void cSplit::printSentences()
{
	for( unsigned int i = 0; i < sentences.size(); i++)
	{
		fprintf(stderr, "%d %d %d %d\n", sentences[i].top, sentences[i].bottom, sentences[i].left, sentences[i].right);
	}
	return;
}
void cSplit::printCharacters()
{
	for( unsigned int i = 0; i < characters.size(); i++)
	{
		for( unsigned int j = 0; j < characters[i].size(); j++)
		{
			fprintf(stderr, "%d %d %d %d\n", characters[i][j].top, characters[i][j].bottom, characters[i][j].left, characters[i][j].right);
		}
	}
	return;
}
void cSplit::IO(unsigned char * bmp, int width, int b)
{
	int i = 0;//The index of the sentences
	int sum_w = 0, sum = 0, height = characters[i][0].bottom - characters[i][0].top;
	for( unsigned int j = 0; j < characters[i].size(); j++)
	{
		sum_w += characters[i][j].right - characters[i][j].left;
	}
	sum = 3 * height * sum_w;
	fprintf(stderr, "total_width = %d, height = %d, total = %d\n", sum_w, height, sum);
	int accum = 0, count = 0;
	unsigned char *result = new unsigned char[sum];
	for( unsigned int m = 0; m < characters[i].size(); m++)
	{
		for(int j = characters[i][m].top; j < characters[i][m].bottom; j++)
		{
			for(int k = characters[i][m].left; k < characters[i][m].right; k++)
			{
				for(int l = 0; l < 3; l++)
				{
					int tmp_r = 3 * (j - characters[i][m].top) * sum_w + 3 * accum + 3 * (k - characters[i][m].left) + l;
					int tmp_b = b * j * width + b * k + l;

					result[tmp_r] = bmp[tmp_b];
					count++;
				}
			}
		}
		accum += characters[i][m].right - characters[i][m].left;
	}
	fprintf(stderr, "%d %d %d %d\n", count, accum, sum_w, sum);
	FILE *ftp = fopen("./output.raw", "w");
	fwrite(result, 1, sum, ftp);
}
