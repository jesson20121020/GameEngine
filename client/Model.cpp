#include "Model.h"
#include "Shader.h"
#include "glheader.h"
#include "stb_image.h"
#include "imgui.h"

Model::Model() :_hasInit(false), _shader(nullptr), _modelName(""), _visible(false)
{
}

void Model::init()
{
}

void Model::draw()
{
}


void Model::render()
{
	if (!hasInit())
	{
		init();
		_hasInit = true;
	}
	draw();
}

void Model::renderImGui()
{
    _shader->drawImGui();
}

void Model::setVisible(bool v)
{
	_visible = v;
	if (_hasInit && !v)
		_hasInit = false;
}


void Model::destroy()
{

}
