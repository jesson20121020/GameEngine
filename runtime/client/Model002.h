#ifndef MODEL002_H
#define MODEL002_H
#include "Model.h"

class Model002 : public Model {

public:
	Model002();
	void init();
	void draw();
	void destroy();

private:
	unsigned int _vao, _texture, _texture1;
};
#endif // !MODEL002_H