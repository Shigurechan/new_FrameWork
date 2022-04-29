#ifndef ___SPRITE_USE_HPP_
#define ___SPRITE_USE_HPP_
#include <glm/glm.hpp>
#include "Resource.hpp"

namespace FrameWork
{
    void RenderGraph(const glm::mat4 view,const glm::vec3 position,const FrameWork::Texture texture);
    void RenderGraph_Size(const glm::mat4 view,const glm::vec3 position,const FrameWork::Texture texture,glm::vec2 startSize,glm::vec2 endSize);

    
}

#endif
