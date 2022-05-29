#ifndef MODEL_H
#define MODEL_H
#include "Shader.h"

class Model {

public:
	Model();
	void setVisible(bool val);
	bool isVisible() { return _visible; }
	void render();
	virtual void renderImGui();
	std::string getModelName() {return _modelName; }
	Shader* getShader() { return _shader; }
	inline bool hasInit() { return _hasInit; }
	virtual void init();
	virtual void draw();
	virtual void destroy();

protected:
	bool _hasInit;
	bool _visible;
	Shader* _shader;
	std::string _modelName;
};
#endif // !MODEL_H


