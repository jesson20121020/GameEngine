#ifndef MODEL003_H
#define MODEL003_H
#include "Model.h"

class Model003 : public Model {

public:
	Model003();
	void init();
	void draw();
	void destroy();

private:
	unsigned int _vao, _texture, _texture1;
};
#endif // !MODEL003_H
