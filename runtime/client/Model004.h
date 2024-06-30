#ifndef MODEL004_H
#define MODEL004_H
#include "Model.h"

class Model004 : public Model {

public:
	Model004();
	void init() override;
	void draw() override;
	void destroy() override;
	virtual void renderImGui() override;
private:
	unsigned int _vao, _texture, _texture1;
	float _fov;
	float _modelRotate[3];
	float _viewPos[3];
};
#endif // !MODEL004_H
