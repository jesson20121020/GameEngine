#ifndef MODEL005_H
#define MODEL005_H
#include "Model.h"
#include "Camera.h"

class Model005 : public Model {

public:
	Model005();
	void init() override;
	void draw() override;
	void destroy() override;
	virtual void renderImGui() override;
private:
	unsigned int _vao, _texture, _texture1;
	float _fov;
	float _modelRotate[3];
	float _viewPos[3];
	Camera* _camera;
};
#endif // !MODEL005_H
