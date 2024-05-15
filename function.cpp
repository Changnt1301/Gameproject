#include "texture.h"
#include "variables.h"
#include "constant.h"
#include "button.h"
#include "function.h"
#include "time.h"
#include <sstream>
#include <fstream>
using namespace std;
vector <vector<LButton> > Buttons(3, vector<LButton>(2));
LButton face;
LButton goBack;
LButton sound;
LTimer timer;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!\n");
    }
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    return true;
}

bool loadTexture(LTexture &texture, const std::string &path)
{
    if (!texture.loadFromFile(path))
    {
        printf("Failed to load texture: %s\n", path.c_str());
        return false;
    }
    return true;
}

bool loadMedia()
{
    bool success = true;
    if (!loadTexture(Tiles_image, "res/images/tiles5.jpg"))
    {
        success = false;
    }
    else
    {
        for (int i = 0; i < 12; i++)
        {
            Tilesprites[i] = {i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
        }
    }
    if (!loadTexture(Digits, "res/images/Untitled1.png"))
    {
        success = false;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            Digitsprites[i] = {i * 28, 0, 28, 46};
        }
    }
    success &= loadTexture(easyTable, "res/images/easy.png");
    success &= loadTexture(mediumTable, "res/images/medium.png");
    success &= loadTexture(hardTable, "res/images/hard.png");
    success &= loadTexture(winFace, "res/images/winface.png");
    success &= loadTexture(loseFace, "res/images/loseface.png");
    success &= loadTexture(playingFace, "res/images/playingface.png");
    success &= loadTexture(back, "res/images/backicon.png");
    success &= loadTexture(sound_on, "res/images/unmute.png");
    success &= loadTexture(sound_off, "res/images/mute.png");
    gFont = TTF_OpenFont("res/font.ttf", 20);
    if (gFont == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    SDL_Color textColorWhite = { 255, 255, 255 };
    SDL_Color textColorRed = { 255, 0, 0 };
    if (!startButton.loadFromRenderedText("START", textColorWhite))
    {
        printf("Failed to load 'START' text texture!\n");
        success = false;
    }
    if (!exitButton.loadFromRenderedText("EXIT", textColorWhite))
    {
        printf("Failed to load 'EXIT' text texture!\n");
        success = false;
    }
    if (!startButtonColor.loadFromRenderedText("START", textColorRed))
    {
        printf("Failed to load colored 'START' text texture!\n");
        success = false;
    }
    if (!exitButtonColor.loadFromRenderedText("EXIT", textColorRed))
    {
        printf("Failed to load colored 'EXIT' text texture!\n");
        success = false;
    }
    loseMusic = Mix_LoadMUS("res/audio/scratch.wav");
    if (loseMusic == nullptr)
    {
        printf("Failed to load lose music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    winMusic = Mix_LoadMUS("res/audio/beat.wav");
    if (winMusic == nullptr)
    {
        printf("Failed to load win music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    click = Mix_LoadWAV("res/audio/click.wav");
    if (click == nullptr)
    {
        printf("Failed to load click sound! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

bool loadTextTexture(LTexture &texture, const std::string &text, SDL_Color color)
{
    if (!texture.loadFromRenderedText(text, color))
    {
        printf("Failed to render text: %s\n", text.c_str());
        return false;
    }
    return true;
}

bool loadMenuMedia()
{
    bool success = true;
    success &= loadTexture(menuTheme, "res/images/menu2.jpg");
    success &= loadTexture(levelTheme, "res/images/mode2.jpg");
    SDL_Color whiteColor = { 255, 255, 255 };
    success &= loadTextTexture(easyChoice, "EASY MODE", whiteColor);
    success &= loadTextTexture(mediumChoice, "MEDIUM MODE", whiteColor);
    success &= loadTextTexture(hardChoice, "HARD MODE", whiteColor);
    SDL_Color redColor = { 255, 0, 0 };
    success &= loadTextTexture(easyChoiceColor, "EASY MODE", redColor);
    success &= loadTextTexture(mediumChoiceColor, "MEDIUM MODE", redColor);
    success &= loadTextTexture(hardChoiceColor, "HARD MODE", redColor);
    return success;
}

void InitializeBoard()
{
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            sBoard[i][j] = 10;
            board[i][j] = 0;
        }
    }
}

void PlaceMines()
{
    int mineCount = 0;
    while (mineCount < NumberOfMines)
    {
        int i = rand() % BOARD_SIZE_X;
        int j = rand() % BOARD_SIZE_Y;
        if (board[i][j] == 9) continue;
        board[i][j] = 9;
        mineCount++;
    }
}

void CalculateNumbers()
{
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            if (board[i][j] == 9) continue;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int xpos = i + x;
                    int ypos = j + y;
                    if (xpos >= 0 && xpos < BOARD_SIZE_X && ypos >= 0 && ypos < BOARD_SIZE_Y && board[xpos][ypos] == 9)
                    {
                        board[i][j]++;
                    }
                }
            }
        }
    }
}

void CreateBoard()
{
    srand(static_cast<unsigned int>(time(0)));
    InitializeBoard();
    PlaceMines();
    CalculateNumbers();
}

void setButtonPosition()
{
	face.setPosition(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	goBack.setPosition(0, 0);
	sound.setPosition(timeDigit_x - 10, 0);
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		for (int j = 0; j < BOARD_SIZE_Y; j++)
		{
			Buttons[i][j].setPosition(i * TILE_SIZE + distance_x, j * TILE_SIZE + distance_y);
		}
	}
}

void createMenu()
{
	menuTheme.render(0, 0);
	startButton.render(125, 260);
    exitButton.render(125, 290);
	SDL_RenderPresent(renderer);
}

void createModeMenu()
{
	levelTheme.render(0, 0);
	easyChoice.render(300, 200);
	mediumChoice.render(300, 250);
	hardChoice.render(300, 300);
}

void showMenu()
{
    bool startInside = false;
    bool exitInside = false;
    bool isMenuShowing = true;
    SDL_Event event;
    createMenu();
    while (isMenuShowing)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                mainLoop = false;
                isMenuShowing = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > 125 && x < 125 + startButton.getWidth() && y > 260 && y < 260 + startButton.getHeight()) startInside = true;
                else startInside = false;
                if (x > 125 && x < 125 + exitButton.getWidth() && y > 290 && y < 290 + exitButton.getHeight()) exitInside = true;
                else exitInside = false;
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (startInside == true)
                        {
                            start = true;
                            isMenuShowing = false;
                        }
                        if (exitInside == true)
                        {
                            mainLoop = false;
                            isMenuShowing = false;
                        }
                    }
                }
                if (event.type == SDL_MOUSEMOTION)
                {
                    if (startInside == true)
                    {
                        startButtonColor.render(125, 260);
                    }
                    else startButton.render(125, 260);
                    if (exitInside == true)
                    {
                        exitButtonColor.render(125, 290);
                    }
                    else exitButton.render(125, 290);
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
}

void showModeChoice()
{
	bool easyInside = false;
	bool mediumInside = false;
	bool hardInside = false;
	SDL_Event event;
	createModeMenu();
	while (isChoosing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isChoosing = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x > 300 && x < 300 + easyChoice.getWidth() && y > 200 && y < 200 + easyChoice.getHeight()) easyInside = true;
				else easyInside = false;
				if (x > 300 && x < 300 + mediumChoice.getWidth() && y > 250 && y < 250 + mediumChoice.getHeight()) mediumInside = true;
				else mediumInside = false;
				if (x > 300 && x < 300 + hardChoice.getWidth() && y > 300 && y < 300 + hardChoice.getHeight()) hardInside = true;
				else hardInside = false;

				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (easyInside == true)
						{
							isRunning = true;
							isChoosing = false;
							timer.start();
							easy = true;
							medium = false;
							hard = false;
							SDL_SetWindowSize(window, 294, 436);
							setGameMode(9, 9, 10, 21, 163, 25, 80, 235, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							CreateBoard();
						}
						if (mediumInside == true)
						{
							isRunning = true;
							isChoosing = false;
							timer.start();
							easy = false;
							medium = true;
							hard = false;
							SDL_SetWindowSize(window, 488, 630);
							setGameMode(16, 16, 40, 21, 163, 25, 80, 430, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							CreateBoard();
						}
						if (hardInside == true)
						{
							isRunning = true;
							isChoosing = false;
							timer.start();
							easy = false;
							medium = false;
							hard = true;
							SDL_SetWindowSize(window, 880, 632);
							setGameMode(30, 16, 99, 21, 163, 25, 80, 820, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							CreateBoard();
						}
					}
				}
				if (event.type == SDL_MOUSEMOTION)
				{
					if (easyInside == true) easyChoiceColor.render(300, 200);
					else easyChoice.render(300, 200);
					if (mediumInside == true) mediumChoiceColor.render(300, 250);
					else mediumChoice.render(300, 250);
					if (hardInside == true) hardChoiceColor.render(300, 300);
					else hardChoice.render(300, 300);
				}
			}
			SDL_RenderPresent(renderer);
		}
	}
}

void handleEvent()
{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				isRunning = false;
				mainLoop = false;
			}
			face.handleEventAgain(&e);
			goBack.handleEventBack(&e);
			sound.handleEventMute(&e);
			for (int i = 0; i < BOARD_SIZE_X; i++)
			{
				for (int j = 0; j < BOARD_SIZE_Y; j++)
				{
					Buttons[i][j].handleEvent(&e);
				}
			}

		}
}

void reveal(int i, int j)
{
	if (sBoard[i][j] == 10 || sBoard[i][j] == 11)
	{
		if (sBoard[i][j] == 11)
		{
			return;
		}
		sBoard[i][j] = board[i][j];
		if (sBoard[i][j] != 9) CountTileLeft--;
		if (sBoard[i][j] == 0)
		{
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int xpos = i + x;
					int ypos = j + y;
					if (xpos < 0 || xpos > BOARD_SIZE_X - 1 || ypos < 0 || ypos > BOARD_SIZE_Y - 1) continue;
					reveal(xpos, ypos);
				}
			}
		}
	}
}

void isPlayerWinning()
{
	if (CountTileLeft == NumberOfMines) isWinning = true;
}

void GameManager()
{
	if (playAgain)
	{
		PlayAgain();
		return;
	}
	if (lose)
	{
		timer.pause();
		DisplayLose();
		return;
	}
	if (isWinning)
	{
		timer.pause();
		DisplayWin();
		return;
	}
}

void DisplayLose()
{
    loseFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            Buttons[i][j].loseRender(i, j);
        }
    }
}

void DisplayWin()
{
    winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
}

std::string getTime()
{
	stringstream Time{};
	if (isWinning == true)
	{
		int n = timer.getTicks() / 1000;
		int h, m, s;
		h = n / 3600;
		m = (n - h * 3600) / 60;
		s = (n - h * 3600 - m * 60);
		Time.str( "" );
		Time << h << ":" << m << ":" << s;
		return Time.str();
	}
	return Time.str();
}

void PlayAgain()
{
	timer.start();
	CreateBoard();
	Mix_HaltMusic();
	mineCountLeft = NumberOfMines;
	CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;
	isWinning = false;
	lose = false;
	playAgain = false;
}

void Return()
{
    SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
				isRunning = false;
				isChoosing = true;
				isWinning = false;
				lose = false;
				easy = false;
				medium = false;
				hard = false;
}

void MineManager()
{
	int n = mineCountLeft;
	if (mineCountLeft < 10)
	{
		Digits.render(digit_x, digit_y, &Digitsprites[0]);
		for (int i = 0; i <= 9; i++)
		{
			if (i == mineCountLeft) Digits.render(digit_x + 28, digit_y, &Digitsprites[i]);
		}
	}
	else
	{
		int i = 0;
		while (n > 0)
		{
			int x = n % 10;
			n /= 10;
			Digits.render(digit_x + (1 - i) * 28, digit_y, &Digitsprites[x]);
			i++;
		}
	}
}

void TimeManager()
{
	int n = timer.getTicks() / 1000;
	if (n < 10)
	{
		Digits.render(timeDigit_x, digit_y, &Digitsprites[n]);
	}
	else
	{
		std::string timeStr = std::to_string(n);
		int numDigits = timeStr.size();
		int x = timeDigit_x - (numDigits - 1) * 28;
		for (int i = 0; i < numDigits; ++i)
		{
			int digit = timeStr[i] - '0';
			Digits.render(x, digit_y, &Digitsprites[digit]);
			x += 28;
		}
	}
}

void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x)
{
	BOARD_SIZE_X = x;
	BOARD_SIZE_Y = y;
	NumberOfMines = n;
	mineCountLeft = n;
	CountTileLeft = x * y;
	distance_x = dx;
	distance_y = dy;
	digit_x = d1x;
	digit_y = d1y;
	timeDigit_x = dtx;
	Buttons.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		Buttons[i].resize(BOARD_SIZE_Y);
	}
	sBoard.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		sBoard[i].resize(BOARD_SIZE_Y);
	}
	board.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		board[i].resize(BOARD_SIZE_Y);
	}
}

void renderButton()
{
	for (int i = 0;i < BOARD_SIZE_X; i++)
	{
		for (int j = 0;j < BOARD_SIZE_Y; j++)
		{
			Buttons[i][j].render(i, j);
		}
	}
}

void renderGame()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	if (mute == false)
	{
		sound_on.render(timeDigit_x - 10, 0);
		loseMusic = Mix_LoadMUS("res/audio/scratch.wav");
		winMusic = Mix_LoadMUS("res/audio/beat.wav");
		click = Mix_LoadWAV("res/audio/click.wav");
	}
	else
	{
		sound_off.render(timeDigit_x - 10, 0);
		click = NULL;
		winMusic = NULL;
		loseMusic = NULL;
	}
	if (easy)
		easyTable.render(0, 50);
	else if (medium)
		mediumTable.render(0, 50);
	else if (hard)
		hardTable.render(0, 50);
	playingFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	renderButton();
	back.render(0, 0);
	MineManager();
	isPlayerWinning();
	TimeManager();
	GameManager();

	SDL_RenderPresent(renderer);
}

void close()
{
	Tiles_image.free();
	TTF_CloseFont(gFont);
	gFont = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



