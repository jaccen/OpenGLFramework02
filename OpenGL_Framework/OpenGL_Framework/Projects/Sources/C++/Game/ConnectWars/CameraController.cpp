/* �w�b�_�t�@�C�� */
#include "CameraController.h"
#include "../../Library/Camera/Manager/CameraManager.h"


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
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_CameraController::C_CameraController(const std::string& rId, int32_t type) : C_GameObject(rId, type)
    {
        // �e�J�������擾
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN));
        pMainCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN).get();

        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pBACKGROUND));
        pBackgroundCamera_ = std::dynamic_pointer_cast<Camera::C_PerspectiveCamera>(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pBACKGROUND).get());

        // �e�f�[�^��ݒ�
        mainCameraData_.viewMatrix_ = pMainCamera_->GetViewMatrix();
        mainCameraData_.projectionMatrix_ = pMainCamera_->GetProjectionMatrix();
        mainCameraData_.viewProjectionMatrix_ = pMainCamera_->GetViewProjectionMatrix();

        backgroundCameraData_.viewMatrix_ = pBackgroundCamera_->GetViewMatrix();
        backgroundCameraData_.projectionMatrix_ = pBackgroundCamera_->GetProjectionMatrix();
        backgroundCameraData_.viewProjectionMatrix_ = pBackgroundCamera_->GetViewProjectionMatrix();

        // �e�o�b�t�@���擾
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA));
        pMainCameraBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA).get();

        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA));
        pBackgroundCameraBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA).get();

        // �w�i�J�������[�J�[�̊e�֐���ݒ�
        for (auto& rCameraWorker : backgroundCameraWorkers_)
        {
            rCameraWorker.SetLinearFunction(Vector3::s_Lerp);
            rCameraWorker.SetHermiteFunction(Vector3::s_Hermite);
            rCameraWorker.EnableLoop();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CameraController::~C_CameraController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �^�X�N���s�Ftrue
     *  @return �^�X�N�I���Ffalse
     *
     ****************************************************************/
    bool C_CameraController::Update()
    {
        // �e�J�����f�[�^��ݒ�
        mainCameraData_.viewMatrix_ = pMainCamera_->GetViewMatrix();
        mainCameraData_.projectionMatrix_ = pMainCamera_->GetProjectionMatrix();
        mainCameraData_.viewProjectionMatrix_ = pMainCamera_->GetViewProjectionMatrix();

        // �e�o�b�t�@�̏�������
        pMainCameraBuffer_->Rewrite(&mainCameraData_, sizeof(S_CameraData), OpenGL::Modify::s_DYNAMIC);
        pBackgroundCameraBuffer_->Rewrite(&backgroundCameraData_, sizeof(S_CameraData), OpenGL::Modify::s_DYNAMIC);

        for (auto& rCameraWorker : backgroundCameraWorkers_) rCameraWorker.Update();

        pBackgroundCamera_->SetEyePoint(backgroundCameraWorkers_[0].GetValue());
        pBackgroundCamera_->SetTargetPoint(backgroundCameraWorkers_[1].GetValue());
        pBackgroundCamera_->SetUpVector(backgroundCameraWorkers_[2].GetValue());

        backgroundCameraData_.viewMatrix_ = pBackgroundCamera_->GetViewMatrix();
        backgroundCameraData_.projectionMatrix_ = pBackgroundCamera_->GetProjectionMatrix();
        backgroundCameraData_.viewProjectionMatrix_ = pBackgroundCamera_->GetViewProjectionMatrix();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraController::Draw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_CameraController::MessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �J�����f�[�^��ݒ肷��
     *  @param  �J�����f�[�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    void C_CameraController::SetCameraData(const JSON::JsonObjectPtr& prCameraData)
    {
        KeyFrame::S_Key<Vector3> key;

        for (size_t i = 0, eyePointDataCount = (*prCameraData)["BackgroundCameraData"]["EyePointDataCount"].GetValue<JSON::Integer>(); i < eyePointDataCount; ++i)
        {
            key.frame_ = (*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Frame"].GetValue<JSON::Integer>();
            auto type = (*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Type"].GetValue<JSON::String>();

            if (type == "Hermite")
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::HERMITE;
            }
            else if (type == "Linear")
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::LINEAR;
            }
            else
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::CONSTANT;
            }

            key.value_.x_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Point"][0].GetValue<JSON::Real>());
            key.value_.y_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Point"][1].GetValue<JSON::Real>());
            key.value_.z_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Point"][2].GetValue<JSON::Real>());

            key.tangent_.x_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Tangent"][0].GetValue<JSON::Real>());
            key.tangent_.y_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Tangent"][1].GetValue<JSON::Real>());
            key.tangent_.z_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["EyePoint"][i]["Tangent"][2].GetValue<JSON::Real>());

            // �L�[��ǉ�
            backgroundCameraWorkers_[0].Add(key);
        }

        for (size_t i = 0, targetPointDataCount = (*prCameraData)["BackgroundCameraData"]["TargetPointDataCount"].GetValue<JSON::Integer>(); i < targetPointDataCount; ++i)
        {
            key.frame_ = (*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Frame"].GetValue<JSON::Integer>();
            auto type = (*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Type"].GetValue<JSON::String>();

            if (type == "Hermite")
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::HERMITE;
            }
            else if (type == "Linear")
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::LINEAR;
            }
            else
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::CONSTANT;
            }

            key.value_.x_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Point"][0].GetValue<JSON::Real>());
            key.value_.y_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Point"][1].GetValue<JSON::Real>());
            key.value_.z_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Point"][2].GetValue<JSON::Real>());

            key.tangent_.x_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Tangent"][0].GetValue<JSON::Real>());
            key.tangent_.y_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Tangent"][1].GetValue<JSON::Real>());
            key.tangent_.z_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["TargetPoint"][i]["Tangent"][2].GetValue<JSON::Real>());

            // �L�[��ǉ�
            backgroundCameraWorkers_[1].Add(key);
        }

        for (size_t i = 0, upVectorDataCount = (*prCameraData)["BackgroundCameraData"]["UpVectorDataCount"].GetValue<JSON::Integer>(); i < upVectorDataCount; ++i)
        {
            key.frame_ = (*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Frame"].GetValue<JSON::Integer>();
            auto type = (*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Type"].GetValue<JSON::String>();

            if (type == "Hermite")
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::HERMITE;
            }
            else if (type == "Linear")
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::LINEAR;
            }
            else
            {
                key.interpolationType_ = KeyFrame::ecInterpolationType::CONSTANT;
            }

            key.value_.x_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Direction"][0].GetValue<JSON::Real>());
            key.value_.y_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Direction"][1].GetValue<JSON::Real>());
            key.value_.z_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Direction"][2].GetValue<JSON::Real>());

            key.tangent_.x_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Tangent"][0].GetValue<JSON::Real>());
            key.tangent_.y_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Tangent"][1].GetValue<JSON::Real>());
            key.tangent_.z_ = static_cast<float>((*prCameraData)["BackgroundCameraData"]["UpVector"][i]["Tangent"][2].GetValue<JSON::Real>());

            // �L�[��ǉ�
            backgroundCameraWorkers_[2].Add(key);
        }
    }
}