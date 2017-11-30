#pragma once
class Camera
{
public:
	Camera(int w, int h);
	Camera(int w, int h, int posX, int posY);
	void setPosX(int);
	void setPosY(int);
	void setWidth(int);
	void setHeight(int);
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	~Camera();

private:
	int posX;
	int posY;
	int width;
	int height;
};

