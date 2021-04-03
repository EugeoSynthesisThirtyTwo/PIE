#include <iostream>
#include <vector>
#include <fstream>

//#define SDL_MainHandled
#include "SDL.h"

#include "grid.h"
#include "AStar.h"
#include "labyrinthe.h"
#include "SDL2_gfxPrimitives.h"

//#define FULL_SCREEN
#define FPS 60

void savePath(std::string filePath, const std::vector<std::pair<int, int>>& path)
{
	std::ofstream ofs = std::ofstream(filePath);

	if (ofs.is_open())
	{
		int imax = path.size() - 1;
		int dx, dy;

		for (int i = 0; i < imax; i++)
		{
			dx = path[i + 1].first - path[i].first;
			dy = path[i + 1].second - path[i].second;

			if (dx == -1)
			{
				if (dy == -1)
					ofs << '7';
				else if (dy == 0)
					ofs << '6';
				else if (dy == 1)
					ofs << '5';
			}
			else if (dx == 0)
			{
				if (dy == -1)
					ofs << '0';
				else if (dy == 1)
					ofs << '4';
			}
			else if (dx == 1)
			{
				if (dy == -1)
					ofs << '1';
				else if (dy == 0)
					ofs << '2';
				else if (dy == 1)
					ofs << '3';
			}
		}

		ofs.close();
	}
	else
	{
		throw "can't open " + filePath;
	}
}

void drawCases(SDL_Renderer* renderer, AStar& astar)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	int width, height;
	SDL_GetRendererOutputSize(renderer, &width, &height);

	SDL_Rect rect;
	rect.w = width / astar.grid.getWidth();
	rect.h = height / astar.grid.getHeight();

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	for (int y = 0; y < astar.grid.getHeight(); y++)
	{
		for (int x = 0; x < astar.grid.getWidth(); x++)
		{
			if (astar.grid.at(x, y))
			{
				rect.x = x * rect.w;
				rect.y = y * rect.h;
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}

void drawPath(SDL_Renderer* renderer, AStar& astar, int x_start, int y_start, int x_end, int y_end)
{
	int width, height;
	SDL_GetRendererOutputSize(renderer, &width, &height);

	SDL_Rect rect;
	rect.w = width / astar.grid.getWidth();
	rect.h = height / astar.grid.getHeight();

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	for (const Node* node : astar.explored)
	{
		rect.x = node->x * rect.w;
		rect.y = node->y * rect.h;
		SDL_RenderFillRect(renderer, &rect);
	}

	std::vector<std::pair<int, int>> path = astar.findPath(x_start, y_start, x_end, y_end);
	savePath("path.txt", path);

	SDL_Point current = {0, 0}, prev;
	bool initialized = false;

	for (const std::pair<int, int>& p : path)
	{
		current.x = (p.first + 0.5) * rect.w;
		current.y = (p.second + 0.5) * rect.h;

		if (initialized)
			thickLineRGBA(renderer, prev.x, prev.y, current.x, current.y, 5, 255, 0, 0, 255);
		else
			initialized = true;

		prev = current;
	}
}

void drawGrid(SDL_Renderer* renderer, AStar& astar)
{
	int width, height;
	SDL_GetRendererOutputSize(renderer, &width, &height);

	SDL_Rect rect;
	rect.w = width / astar.grid.getWidth();
	rect.h = height / astar.grid.getHeight();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int mapped;

	for (int y = 0; y < astar.grid.getHeight(); y++)
	{
		mapped = y * rect.h;
		SDL_RenderDrawLine(renderer, 0, mapped, width, mapped);
		SDL_RenderDrawLine(renderer, 0, mapped + rect.h - 1, width, mapped + rect.h - 1);
	}

	for (int x = 0; x < astar.grid.getWidth(); x++)
	{
		mapped = x * rect.w;
		SDL_RenderDrawLine(renderer, mapped, 0, mapped, height);
		SDL_RenderDrawLine(renderer, mapped + rect.w - 1, 0, mapped + rect.w - 1, height);
	}
}

void loop(SDL_Renderer* renderer)
{
	int width, height;
	SDL_GetRendererOutputSize(renderer, &width, &height);
	SDL_Event event;
	double timeDifference = 1.0 / FPS;
	double time = SDL_GetTicks() / 1000.0 - timeDifference;
	double newTime;
	double dt;
	bool continuer = true;
	int pressed = 0;

	Grid grid(10, 10);
	AStar astar(grid);

	int x_start = -1, y_start = -1;
	int x_end = -1, y_end = -1;

	bool middle_pressed = false;

	while (continuer)
	{
		newTime = SDL_GetTicks() / 1000.0;
		dt = newTime - time;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					continuer = 0;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							continuer = 0;
							break;
						case SDLK_1:
							grid.clear(false);
							break;
						case SDLK_2:
							grid.clear(true);
							break;
						case SDLK_s:
							grid.save("map.bin");
							break;
						case SDLK_l:
							std::ifstream f("map.bin");
							if (f.good())
							{
								f.close();
								grid = std::move(Grid::load("map.bin"));
							}
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT && pressed == 1 ||
						event.button.button == SDL_BUTTON_RIGHT && pressed == 2)
						pressed = 0;
					else if (event.button.button == SDL_BUTTON_MIDDLE)
						middle_pressed = false;

					break;
				case SDL_MOUSEBUTTONDOWN:
					if (!pressed && event.button.button == SDL_BUTTON_LEFT)
						pressed = 1;
					else if (!pressed && event.button.button == SDL_BUTTON_RIGHT)
						pressed = 2;
					else if (!middle_pressed && event.button.button == SDL_BUTTON_MIDDLE)
					{
						x_start = x_end = event.button.x * grid.getWidth() / width;
						y_start = y_end = event.button.y * grid.getHeight() / height;
						middle_pressed = true;
					}

					break;
				case SDL_MOUSEMOTION:
					if (middle_pressed)
					{
						x_end = event.button.x * grid.getWidth() / width;
						y_end = event.button.y * grid.getHeight() / height;
					}

					break;
			}

			if (pressed)
			{
				int x = event.button.x * grid.getWidth() / width;
				int y = event.button.y * grid.getHeight() / height;

				if (grid.isInside(x, y))
					grid.set(x, y, 2 - pressed);
			}
		}

		if (dt >= timeDifference)
		{
			time = newTime;
			drawCases(renderer, astar);
			drawPath(renderer, astar, x_start, y_start, x_end, y_end);
			drawGrid(renderer, astar);
			SDL_RenderPresent(renderer);
		}
	}
}

int main(int argc, char** argv)
{
	#ifdef SDL_MainHandled
	SDL_SetMainReady();
	#endif

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Echec de l'initalisation de la SDL : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	#ifdef FULL_SCREEN

	SDL_Window* window = SDL_CreateWindow("Fenetre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

	#else

	SDL_Window* window = SDL_CreateWindow("Fenetre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, 0);

	#endif

	if (window == NULL)
	{
		fprintf(stderr, "Echec de la creation de la fenetre : %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
		fprintf(stderr, "Erreur a la creation du renderer : %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	std::srand((unsigned int) time(NULL));
	loop(renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}