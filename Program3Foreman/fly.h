#ifndef FLY_H
#define FLY_H

class fly {
public:
	fly();
	~fly();
	void drawFly();
	void dropFly(int x);
	void updateFly();
	void setLive(bool new_live);
	bool getLive();
	int getX();
	int getY();

private:
	int x, y;
	bool live;
	int speed;
	ALLEGRO_BITMAP* image;
};
#endif