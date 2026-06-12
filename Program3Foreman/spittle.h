
class spittle {
public:
	spittle();
	~spittle();
	void drawSpittle();
	void fireSpittle(float angle);
	void updateSpittle();
	bool getLive();

private:
	int x;
	int y;
	int speed;
	bool live;
	float radian_angle;
	ALLEGRO_BITMAP* image;
};
