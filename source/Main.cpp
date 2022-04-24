#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../FrameWork/header/FrameWork.hpp"

int main()
{
    
    if (glfwInit() == GL_FALSE)
	{
		std::cerr << "glfw を初期化出来ません。" << std::endl;
	}


    std::shared_ptr<FrameWork::Window> window = std::make_shared<FrameWork::Window>(glm::ivec2(840,680),"sample");
    FrameWork::SetCurrentWindowContext(window);
 
    if (glewInit() != GLEW_OK)
	{
		std::cerr << "glew を初期化出来ません。" << std::endl;
	}



    FrameWork::Init();
    std::shared_ptr<FrameWork::Camera> camera = std::make_shared<FrameWork::Camera>();
    FrameWork::Texture texture = FrameWork::LoadTexture("Asset/texture/debug_A1.png");



    while(*window)
    {
        camera->ClearBuffer();

        FrameWork::RenderGraph(camera->getViewOrthographic(),glm::vec3(0,0,0),texture);



        camera->RendererBuffer();
        window->SwapBuffer();
    }



    return 0;
}