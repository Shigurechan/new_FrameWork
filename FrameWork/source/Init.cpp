
#include "../header/Sprite.hpp"
#include "../header/Init_Use.hpp"
#include "../header/Init.hpp"

std::shared_ptr<FrameWork::Sprite> FrameWork::sprite = nullptr;	

void FrameWork::Init()
{
    FrameWork::sprite = std::make_shared<FrameWork::Sprite>();	

}