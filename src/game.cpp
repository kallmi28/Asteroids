#include "game.h"

Game::Game(unsigned int & highScoreInit) :  pl(NULL), numOfShots(0), maxShots(5), objects(NULL), numOfUpgrades(0), numOfObjects(0), maxObjects(30), score(0), highScore(highScoreInit)
{
	objects = new MovingObject * [maxObjects];
	for (int i = 0; i < UPGRADE_TYPES; ++i)
		upgradeDuration[i] = 0;
	
}

Game::~Game()
{
	for (int i = 0; i < numOfObjects; ++i)
	{
		delete objects[i];
	}
	delete[] objects;

	for (int i = 0; i < numOfUpgrades; ++i)
	{
		delete upgrades[i];
	}
}

void Game::render(SDL_Renderer * ren, TTF_Font * font) const
{
	SDL_SetRenderDrawColor( ren, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( ren );
	int i = 0;
	// check invisibility bonus
	if(SDL_GetTicks() < upgradeDuration[0])
		i++;
	for (; i < numOfObjects; ++i)
	{
		objects[i]->render(ren);
	}
	for (int i = 0; i < numOfUpgrades; ++i)
	{
		upgrades[i]->render(ren);
	}
	// score
	printScoreBoards(ren, font);
	SDL_RenderPresent( ren );
}

void Game::printScoreBoards(SDL_Renderer * ren, TTF_Font * font) const
{
	int boardHeight;
	SDL_Color textColor;
	if(highScore <= score)
	{
		textColor = {0xFF, 0xFF, 0x00, 0xFF};
		highScore = score;
	}
	else
		textColor = { 0xFF, 0xFF , 0xFF, 0xFF };
	stringstream scoreText;
	scoreText.str("");
	scoreText << setw(8) << setfill('0') << score;
	SDL_Surface * scoreBoard = TTF_RenderText_Solid( font, scoreText.str().c_str(), textColor);
	SDL_Texture * tex = SDL_CreateTextureFromSurface( ren, scoreBoard );
	SDL_Rect renderQuad = {20, 20, scoreBoard->w, scoreBoard->h };
	SDL_RenderCopyEx(ren, tex, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);

	boardHeight = scoreBoard->h;
	SDL_FreeSurface( scoreBoard );
	SDL_DestroyTexture( tex );

	textColor = {0xFF, 0xFF, 0x00, 0xFF};
	scoreText.str("");
	scoreText << setw(8) << setfill('0') << highScore;
	scoreBoard = TTF_RenderText_Solid( font, scoreText.str().c_str(), textColor);
	tex = SDL_CreateTextureFromSurface( ren, scoreBoard );
	renderQuad = {20, 20 + boardHeight + 10, scoreBoard->w, scoreBoard->h };
	SDL_RenderCopyEx(ren, tex, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
	SDL_FreeSurface( scoreBoard );
	SDL_DestroyTexture( tex );


}

void Game::makePlayer (SDL_Surface * surface, SDL_Renderer * ren, const int screenHeight, const int screenWidth)
{
	pl = new Player(screenWidth / 2, screenHeight / 2);
	pl->loadTexture(surface, ren);
	objects[numOfObjects++] = pl; 
}

void Game::changePlayerAngle (const int add)
{
	pl->changeAngle(add);
}

void Game::moveObjects (bool forward, const int screenWidth, const int screenHeight)
{
	for (int i = 0; i < numOfObjects; ++i)
	{
		//printf("1:%d\n", objects[i]);
		Shot * sh_ = dynamic_cast<Shot*>(objects[i]);
		if(sh_ != NULL)
			if(sh_->getShotTick() == 0)
			{
				MovingObject * tmp = objects[i];
				objects[i] = objects[numOfObjects - 1];
				objects[--numOfObjects] = tmp;
				//printf("1free: %x\n", objects[numOfObjects]);
				delete objects[numOfObjects];
				i --;
				numOfShots --;
				continue;
			}
		objects[i]->move(screenWidth, screenHeight, forward);
	}
}

void Game::makeAsteroids (SDL_Surface ** textureSurfaces, SDL_Renderer * ren, ifstream & fin)
{
	int num;
	fin.read((char *)&num, sizeof(int));
	for (int i = 0; i < num; ++i)
	{
		int x, y;
		int xVec, yVec;
		int size;
		fin.read((char *)&x, sizeof(int));
		fin.read((char *)&y, sizeof(int));
		fin.read((char *)&xVec, sizeof(int));
		fin.read((char *)&yVec, sizeof(int));
		fin.read((char *)&size, sizeof(int));
		Vector * velocity = new Vector (xVec, yVec);
		objects[numOfObjects] = new Asteroid(x, y, velocity, 2 - size);
		objects[numOfObjects++]->loadTexture(textureSurfaces[(rand() % 2) + 2 * (size + 1)], ren);
	}
}

int Game::checkCollision(SDL_Surface ** textureSurfaces, SDL_Renderer * ren)
{
	for (int i = 0; i < numOfUpgrades; ++i)
	{
		if(sat(pl->getHitbox(), upgrades[i]->getHitbox()))
		{
			int upgradeType = (int) upgrades[i]->getIdentifier();
			upgradeDuration[upgradeType] = SDL_GetTicks() + (10 * 1000);
			if(upgradeType == 2) maxShots = 10;
			Upgrade * tmp = upgrades[i];
			upgrades[i] = upgrades[numOfUpgrades - 1];
			upgrades[numOfUpgrades--] = NULL;
			printf("Upgrade %d picked up.\n", upgradeType);
			delete tmp;
		}
	}
	//check collision between player and upgrade
	for (int i = 1; i < numOfObjects; ++i)
	{
		{
			Asteroid * as_ = dynamic_cast<Asteroid*>(objects[i]);
			// _object is asteroid, collision control is only with player
			if(as_ != NULL)
			{
				if(sat(pl->getHitbox(), as_->getHitbox()))
				{
					//printf("Collision between player and moving object %d (Asteroid)\n", i);
					// check if invincibility bonus is available
					if(SDL_GetTicks() > upgradeDuration[1])
					{
						objects[0] = objects[--numOfObjects];
						delete pl;
						pl = NULL;
						for (int i = 0; i < UPGRADE_TYPES; ++i)
							upgradeDuration[i] = 0;
						return -1;
					}
				}
				continue;
			}
		}
		// _object must be shot, collision control is with all asteroids
		for (int j = 0; j < numOfObjects; ++j)
		{
			Asteroid * as_ = dynamic_cast<Asteroid*>(objects[j]);
			if(as_ == NULL) 
				continue;
			// collision control between asteroid and shot

			if(sat(as_->getHitbox(), objects[i]->getHitbox()))
			{
				score += as_->getScore();
				// if colliding, then switch shot with last moving_object and delete it
				// decrement i
				SDL_Point upgradeSpawn = objects[i]->getHitbox()->getCentre();
				{
					Shot * tmp = dynamic_cast<Shot*>(objects[i]);
					objects[i--] = objects[--numOfObjects];
					numOfShots--;
					if(j == numOfObjects)
						j = i + 1;
					delete tmp;
				}
				// splitting asteroid
				Asteroid ** tmp = as_->split(textureSurfaces, ren);
				// if ret value is NULL, then only switch asteroid with last moving object_and delete
				// decrement j
				if(tmp == NULL)
				{
					delete objects[j];
					objects[j--] = objects[numOfObjects - 1];
					objects[numOfObjects--] = NULL;
				}

				// if ret value is not NULL, then i switch asteroid with last 
				else
				{
					delete objects[j];
					objects[j] = tmp[0];
					if(numOfObjects + 1 >= maxObjects)
					{
						maxObjects *= 2;
						MovingObject ** t = new MovingObject * [maxObjects];
						for (int k = 0; k < numOfObjects; ++k)
						{
							t[k] = objects[k];
						}
						delete[] objects;
						objects = t;
					}
					objects[numOfObjects++] = tmp[1];
				}
				// randomly generate bonus
				if(rand() % 100 > 95)
					makeUpgrade(textureSurfaces[8], ren, upgradeSpawn);
				delete[] tmp;
				break;
			}
		}
	}

	if(numOfObjects - numOfShots == 1)
	{
		return 1;
	}
	return 0;
}

void Game::playerShoot(SDL_Renderer * ren, SDL_Surface * shotSurface)
{
	if(SDL_GetTicks() > upgradeDuration[2])
		maxShots = 5;
	if(numOfShots < maxShots)
	{
		numOfShots++;
		if(numOfObjects + 1 >= maxObjects)
		{
			maxObjects *= 2;
			MovingObject ** t = new MovingObject * [maxObjects];
			for (int k = 0; k < numOfObjects; ++k)
			{
				t[k] = objects[k];
			}
			delete[] objects;
			objects = t;
		}
		objects[numOfObjects++] = pl->shoot(shotSurface, ren);
	}
}

void Game::makeUpgrade(SDL_Surface * upgradeSurface, SDL_Renderer * ren, SDL_Point centre)
{
	if(numOfUpgrades < MAX_UPGRADES)
	{	
		upgrades[numOfUpgrades] = new Upgrade(centre.x, centre.y, rand() % 3);
		upgrades[numOfUpgrades++]->loadTexture(upgradeSurface, ren);
	}
}

/*
* Following code is taken over from
* http://www.phailed.me/2011/02/polygonal-collision-detection/#tut7 
*/

double* Game::project(Polygon * a, Vector * axis)
{
	Vector * ax = axis->normalize();
	Vector ** vertices = a->getVertices();
	SDL_Point centre = a->getCentre();
	Vector * k = new Vector (vertices[0]->getAxisX() + centre.x, vertices[0]->getAxisY() + centre.y);
	double min = ax->dotProduct(*k);
	double max = min;
	for (int i = 0; i < a->getNumOfVertices(); ++i){
		delete k;
		k = new Vector (vertices[i]->getAxisX() + centre.x, vertices[i]->getAxisY() + centre.y);
		double proj = ax->dotProduct(*k);
		if (proj < min) 
			min = proj;
		if (proj > max) 
			max = proj;
	}
	delete k;
	double* arr = new double [2];
	arr[0] = min; arr[1] = max;
	delete ax;
	return arr;
}

bool Game::contains(double n, double* range)
{
	double a = range[0], b = range[1];
	if (b < a)
	{
		a = b;
		b = range[0];
	}
	return (n >= a && n <= b);
}

bool Game::overlap(double* a_, double* b_)
{
	if (contains(a_[0],b_)) return true;
	if (contains(a_[1],b_)) return true;
	if (contains(b_[0],a_)) return true;
	if (contains(b_[1],a_)) return true;
	return false;
}

bool Game::sat(Polygon * a, Polygon * b)
{
	Vector ** axis = a->getEdges();
	
	int i;
	for (i=0;i<a->getNumOfVertices();i++){
		Vector * ax = new Vector (axis[i]->getAxisX(), axis[i]->getAxisY());
		ax->rotate(90);
		double *a_ = project(a,ax);
		double *b_ = project(b,ax);
		if (!overlap(a_,b_))
		{
			delete[] a_;
			delete[] b_;
			delete ax;
			return false;
		} 
		delete[] a_;
		delete[] b_;
		delete ax;
	}
	axis = b->getEdges();
	for (i=0;i<b->getNumOfVertices();i++){
		Vector * ax = new Vector (axis[i]->getAxisX(), axis[i]->getAxisY());
		ax->rotate(90);
		double *a_ = project(a,ax);
		double *b_ = project(b,ax);
		if (!overlap(a_,b_))
		{
			delete[] a_;
			delete[] b_;
			delete ax;
			return false;
		} 
		delete[] a_;
		delete[] b_;
		delete ax;
	}
	return true;
}
