/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "../../Library/Camera/Camera/Camera.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/KeyFrame/KeyAnimation.h"
#include "../../Library/JSON/Object/JsonObject.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /** �J�����f�[�^�̎�� */
    enum class ecCameraDataType
    {
        BACKGROUND_EYE_POINT,
        BACKGROUND_TARGET_POINT,
        BACKGROUND_UP_VECTOR,
    };


    //-------------------------------------------------------------
    //!
    //! @brief �J�����R���g���[���[
    //! @brief �J�����𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_CameraController : public GameObject::C_GameObject
    {
    public:
        C_CameraController(const std::string& rId, int32_t type);               // �R���X�g���N�^
        virtual ~C_CameraController() override;                                 // �f�X�g���N�^
        bool Update() override;                                                 // �X�V����
        void Draw() override;                                                   // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                // ���b�Z�[�W����
        void SetCameraData(const JSON::JsonObjectPtr& prCameraData);            // �J�����f�[�^��ݒ�
        void SetNowFrame(int32_t frame);                                        // ���݂̃t���[������ݒ�
        void SetIndex(int32_t index, ecCameraDataType cameraDataType);          // �C���f�b�N�X�̐ݒ�
    protected:
        Camera::CameraPtr pMainCamera_;                                         ///< @brief ���C���J����
        std::shared_ptr<Camera::C_PerspectiveCamera> pBackgroundCamera_;        ///< @brief �w�i�J����
        S_CameraData mainCameraData_;                                           ///< @brief ���C���J�����f�[�^
        S_CameraData backgroundCameraData_;                                     ///< @brief �w�i�J�����f�[�^
        Shader::GLSL::UniformBufferPtr pMainCameraBuffer_;                      ///< @brief ���C���J�����o�b�t�@
        Shader::GLSL::UniformBufferPtr pBackgroundCameraBuffer_;                ///< @brief �w�i�J�����o�b�t�@
        KeyFrame::C_KeyAnimation<Vector3> backgroundCameraWorkers_[3];          ///< @brief �w�i�J�������[�J�[
    };
}
