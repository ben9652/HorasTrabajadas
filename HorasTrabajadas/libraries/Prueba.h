#ifndef __PRUEBAS_
#define __PRUEBAS_

class Prueba
{
public:
	Prueba(int _x);

	static int x_stat;

	void setX(int _x);
	int getX();

private:
	int x;
};

#endif