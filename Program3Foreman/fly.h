#ifndef FLY_H
#define FLY_H

class fly {
public:
	fly();
	~fly();
	void drawFly(int v);
	void dropFly(int x);
	void updateFly();
	void setLive(bool new_live);
	bool getLive();
	int getX();
	int getY();
	int getBoundx();
	int getBoundy();
	void setVersion(int v);
	int getVersion();

private:
	int x, y;
	int boundx, boundy;
	bool live;
	int speed;
	int version;
	ALLEGRO_BITMAP* images[2];
};
#endif