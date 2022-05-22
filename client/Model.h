#include "Shader.h"

class Model{

public:
	Model();
	void init();
	inline bool hasInit(){ return _hasInit; }
	void render();
	void draw();
	void destroy();
	Shader* getShader() {return _shader; }
	
private:
	bool _hasInit;
	Shader* _shader;
	unsigned int _vao, _texture, _texture1;
};
