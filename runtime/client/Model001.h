#ifndef MODEL001_H
#define MODEL001_H
#include "Model.h"

class Model001 : public Model {

public:
	Model001();
	void init();
	void draw();
	void destroy();
private:
	unsigned int _vao;
};
#endif // !MODEL002_H
