#include "stdafx.h"
#include "primitives/line_primitive.h"
#include "engine.h"
#include "render/Renderer.h"

using namespace DX2D;

LinePrimitive::LinePrimitive(void)
{
}


LinePrimitive::~LinePrimitive(void)
{
}

void DX2D::LinePrimitive::Render()
{
	CEngine::GetInstance()->GetRenderer().AddToRender(this);
}
