#ifndef ___SCENE_HPP_
#define ___SCENE_HPP_


/*#########################################################################
# Camera 設定

説明
	
###########################################################################*/

namespace FrameWork
{
    class Scene
    {
    public:

        Scene()
        {

        }

        ~Scene()
        {

        }

        virtual void Update() = 0;
        virtual void Renderer() = 0;
    };
}
#endif
