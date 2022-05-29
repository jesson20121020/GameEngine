#ifndef MODEL003_H
#define MODEL003_H
#include "Model.h"

class Model003 : public Model {

public:
	Model003();
	void init() override;
	void draw() override;
	void destroy() override;
	virtual void renderImGui() override;

private:
	unsigned int _vao, _texture, _texture1;
	float _scale[2];
	float _pos[2];
	float _rotate[2];
};
#endif // !MODEL003_H
