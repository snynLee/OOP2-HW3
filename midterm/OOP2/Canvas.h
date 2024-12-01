#pragma once

#include <iostream>
#include "Utils.h"

class GameObject;


class Canvas {
	char* screen;
	int		frame_rate;
	int		n_frames;

	Dimension dim;
	int		width;
	int		height;
	int		size;

	static Canvas* Instance;


	Canvas(const Dimension& dim = { 80, 20 }, int frame_rate = 30)
		: dim{ dim }, width{ dim.x }, height{ dim.y }, size((dim.x + 1)* dim.y), screen(new char[((size_t)dim.x + 1) * dim.y]), frame_rate(frame_rate), n_frames(0)
	{}

public:


	static Canvas* GetInstance();


	int getWidth() const { return width; }

	int getHeight() const { return height; }
	

	~Canvas()
	{
		delete[] screen;
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	//void draw(const GameObject* obj);

	void draw(const char* shape, const Position& worldPos, const Dimension& dim)
	{
		if (!shape) return;
		
		ScreenPosition scrPos(worldPos);
		for (int h = 0; h < dim.y; h++)
		{
			if (scrPos.y + h < 0) continue;
			if (scrPos.y + h >= height) break;
			for (int w = 0; w < dim.x; w++)
			{
				if (scrPos.x + w < 0) continue;
				if (scrPos.x + w >= width) break;
				screen[(scrPos.y + h) * (width + 1) + scrPos.x + w] = shape[h * dim.x + w];
			}
		}
	}

	void render() const
	{
		Borland::GotoXY(0, 0);
		for (int i = 0; i < height; i++) 
			screen[i * (width + 1) + width] = '\n';
		screen[size] = '\0';

		std::cout << screen;

		Sleep(1000 / frame_rate);
	}

	bool isOutOfScreen(const GameObject* obj) const;

	void update()
	{
		n_frames++;
	}

	// getter
	int getCurrentFrameNumber() const { return n_frames; }

	Dimension getScreenSize() const { return { width, height }; }

	int getFrameRate() const { return frame_rate; }
};

