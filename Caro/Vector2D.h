#pragma once

class Vector2D
{
public:
	Vector2D(float x, float y) { this->X = x; this->Y = y; }

	Vector2D operator+(const Vector2D& v2) {
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	//void setX(float x) { this->x = x; }
	//void setY(float y) { this->y = y; }

	//float getX() { return x; }
	//float getY() { return y; }

	float X, Y;
private:
};

