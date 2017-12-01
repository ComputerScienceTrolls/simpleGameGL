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
	void setDX(int);
	void setDY(int);
	void setCameraForce(float, float);
	int getPosX();
	int getPosY();
	int getDX();
	int getDY();
	int getWidth();
	int getHeight();
	~Camera();

private:
	int posX;
	int posY;
	int dx;
	int dy;
	int width;
	int height;
};

