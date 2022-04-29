#ifndef ___CAMERA_USE_HPP_
#define ___CAMERA_USE_HPP_

#include "Camera.hpp"

/*#########################################################################
# Camera 設定

説明
	
###########################################################################*/


namespace FrameWork
{
    void SetCurrentCamera(std::shared_ptr<FrameWork::Camera> c);
    std::shared_ptr<FrameWork::Camera> GetCurrentCamera();

}

#endif