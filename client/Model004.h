#ifndef MODEL004_H
#define MODEL004_H
#include "Model.h"

class Model004 : public Model {

public:
	Model004();
	void init();
	void draw();
	void destroy();
private:
	unsigned int _vao;
};
#endif // !MODEL004_H
