/* �w�b�_�t�@�C�� */
#include "LoadFunction.h"
#include "ConnectWarsDefine.h"
#include "../../Library/Window/Manager/WindowManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Model/SelfMade/Loader/Manager/ModelLoaderManager.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Common/CommonHelper.h"



//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �^�C�g���̃f�[�^�̃��[�h�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_LoadFunction::s_LoadTitleData()
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�[�W01�̃f�[�^�̃��[�h�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_LoadFunction::s_LoadStage01Data()
    {
        assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
        auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

        // ���C���J�����̃��[�h����
        if (!Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN))
        {
            auto CameraData = JSON::JsonObject::s_CreateFromFile(Path::JSON::s_pCAMERA);

            auto pMainCamera = std::make_shared<Camera::C_PerspectiveCamera>();

            pMainCamera->SetEyePoint(Camera::Vector3(static_cast<float>(CameraData["CameraData"]["MainCamera"]["EyePoint"][0].GetValue<JSON::Real>()),
                                                     static_cast<float>(CameraData["CameraData"]["MainCamera"]["EyePoint"][1].GetValue<JSON::Real>()),
                                                     static_cast<float>(CameraData["CameraData"]["MainCamera"]["EyePoint"][2].GetValue<JSON::Real>())));

            pMainCamera->SetTargetPoint(Camera::Vector3(static_cast<float>(CameraData["CameraData"]["MainCamera"]["TargetPoint"][0].GetValue<JSON::Real>()),
                                                        static_cast<float>(CameraData["CameraData"]["MainCamera"]["TargetPoint"][1].GetValue<JSON::Real>()),
                                                        static_cast<float>(CameraData["CameraData"]["MainCamera"]["TargetPoint"][2].GetValue<JSON::Real>())));

            pMainCamera->SetFieldOfViewY(static_cast<float>(CameraData["CameraData"]["MainCamera"]["FieldOfViewY"].GetValue<JSON::Real>()));
            pMainCamera->SetNearClippingPlane(static_cast<float>(CameraData["CameraData"]["MainCamera"]["NearClippingPlane"].GetValue<JSON::Real>()));
            pMainCamera->SetFarClippingPlane(static_cast<float>(CameraData["CameraData"]["MainCamera"]["FarClippngPlane"].GetValue<JSON::Real>()));
            pMainCamera->SetUpVector(Camera::Vector3::s_UP_DIRECTION);
            pMainCamera->SetAspectRatio(pMainWindow->GetAspectRatio<float>());
            pMainCamera->Update();

            Camera::C_CameraManager::s_GetInstance()->Entry(pMainCamera, ID::Camera::s_pMAIN);
        }

        // �e���f���̃��[�h����
        const char* pPrimitiveIdList[] = 
        {
            ID::Primitive::s_pNORMAL_PLAYER,
        };

        const char* pModelPathList[] =
        {
            Path::Model::s_pNORMAL_PLAYER,
        };

        const char* pModelIdList[] =
        {
            ID::Model::s_pNORMAL_PLAYER,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pPrimitiveIdList); i < arraySize; ++i)
        {
            if (!OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(pPrimitiveIdList[i]))
            {
                auto pModelLoader = Model::SelfMade::C_ModelLoader::s_Create();
                pModelLoader->LoadModel(pModelPathList[i]);

                Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->Entry(pModelLoader, pModelIdList[i]);
            }
        }

        // Json����e�f�[�^�����[�h
        const char* pJsonIdList[] =
        {
            ID::JSON::s_pNORMAL_PLAYER,
            ID::JSON::s_pSPEED_UP_OPTION,
        };


        const char* pJsonPathList[] =
        {
            Path::JSON::s_pNORMAL_PLAYER,
            Path::JSON::s_pSPEED_UP_OPTION,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pJsonIdList); i < arraySize; ++i)
        {
            if (!JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(pJsonIdList[i]))
            {
                auto pJsonObject = JSON::JsonObject::s_CreatePointerFromFile(pJsonPathList[i]);
                JSON::C_JsonObjectManager::s_GetInstance()->Entry(pJsonObject, pJsonIdList[i]);
            }
        }

        return true;
    }
}