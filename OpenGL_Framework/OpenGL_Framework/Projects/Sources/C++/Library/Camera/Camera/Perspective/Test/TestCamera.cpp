/* �w�b�_�t�@�C�� */
#include "TestCamera.h"
#include "../../../../Input/Keyboard/KeyboardManager.h"
#include "../../../../Input/Mouse/MouseManager.h"
#include "../../../../Math/Vector/Vector4.h"
#include "../../../../Math/Quaternion/Quaternion.h"
#include "../../../../Math/Define/MathDefine.h"
#include <algorithm>


//-------------------------------------------------------------
//!
//! @brief �J����
//! @brief �J�����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Camera
{
    /* �ʖ� */
    using Vector4 = Math::S_Vector4<float>;                 // Vector4�^


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TestCamera::C_TestCamera()
    {
        // �ȑO�̃}�E�X�̍��W��������
        previousMousePositionX_ = Input::C_MouseManager::s_GetInstance()->GetCursorPositionX();
        previousMousePositionY_ = Input::C_MouseManager::s_GetInstance()->GetCursorPositionY();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TestCamera::~C_TestCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �e�X�g�J�����̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::Update()
    {
        // ���_�������_���ύX���ꂽ�ꍇ�A�������Čv�Z���t���O��������
        if (pointChangeFlag_ == true)
        {
            distance_ = eyePoint_ - targetPoint_;
            pointChangeFlag_ = false;
        }

        // �J�����̌��������߂�
        direction_ = targetPoint_ - eyePoint_;
        direction_.Normalize();
        direction_.Invert();

        // �e���͂ɂ��X�V����
        if (keyboardFlag_ == true) InputKeyboardUpdate();
        if (mouseFlag_ == true) InputMouseUpdate();

        // �J�����̍X�V����
        C_PerspectiveCamera::Update();
    }


    /*************************************************************//**
     *
     *  @brief  ���_��ݒ肷��
     *  @param  ���_
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::SetEyePoint(const Vector3& rEyePoint)
    {
        eyePoint_ = rEyePoint;

        // �t���O�������Ă��Ȃ��ꍇ�͗��Ă�
        if (pointChangeFlag_ == false) pointChangeFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  �����_��ݒ肷��
     *  @param  �����_
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::SetTargetPoint(const Vector3& rTargetPoint)
    {
        targetPoint_ = rTargetPoint;

        // �t���O�������Ă��Ȃ��ꍇ�͗��Ă�
        if (pointChangeFlag_ == false) pointChangeFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  �L�[���̓t���O��ݒ肷��
     *  @param  �L�[���̓t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::SetKeyboradFlag(bool keyboardFlag)
    {
        keyboardFlag_ = keyboardFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �}�E�X���̓t���O��ݒ肷��
     *  @param  �}�E�X���̓t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::SetMouseFlag(bool mouseFlag)
    {
        mouseFlag_ = mouseFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��̑傫����ݒ肷��
     *  @param  �ړ��̑傫��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::SetMoveScale(float moveScale)
    {
        moveScale_ = moveScale;
    }


    /*************************************************************//**
     *
     *  @brief  �L�[���͂ɂ��X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::InputKeyboardUpdate()
    {
        // ��L�[����͂����ꍇ�̓J������O�ֈړ�
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_UP) > 0)
        {
            eyePoint_ -= direction_ * moveScale_;
            targetPoint_ -= direction_ * moveScale_;
        }

        // ���L�[����͂����ꍇ�̓J���������ֈړ�
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_DOWN) > 0)
        {
            eyePoint_ += direction_ * moveScale_;
            targetPoint_ += direction_ * moveScale_;
        }

        // ���L�[����͂����ꍇ�̓J���������ֈړ�
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_LEFT) > 0)
        {
            // �J�����̍����������߂�
            Vector3 leftDirection = Vector3::s_CrossProduct(direction_, upVector_);

            eyePoint_ += leftDirection * moveScale_;
            targetPoint_ += leftDirection * moveScale_;
        }

        // �E�L�[����͂����ꍇ�̓J�������E�ֈړ�
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_RIGHT) > 0)
        {
            // �J�����̉E���������߂�
            Vector3 rightDirection = Vector3::s_CrossProduct(direction_, upVector_ * -1.0f);

            eyePoint_ += rightDirection * moveScale_;
            targetPoint_ += rightDirection * moveScale_;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �}�E�X���͂ɂ��X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TestCamera::InputMouseUpdate()
    {
        // �}�E�X�̃h���b�O���ɗ��p����␳�l
        const float RIGHT_DRAG_CORRECTION_VALUE = 0.01f;
        const float MIDDLE_DRAG_CORRECTION_VALUE_ = 0.02f;

        // �}�E�X�̍��W���擾
        int mousePositionX = Input::C_MouseManager::s_GetInstance()->GetCursorPositionX();
        int mousePositionY = Input::C_MouseManager::s_GetInstance()->GetCursorPositionY();

        // �}�E�X�̈ړ���
        int mouseMovementX = mousePositionX - previousMousePositionX_;
        int mouseMovementY = mousePositionY - previousMousePositionY_;

        // �}�E�X�z�C�[�����N���b�N���Ȃ���h���b�O�����ꍇ�̓h���b�O���������ɉ����ăJ�������ړ�
        if (Input::C_MouseManager::s_GetInstance()->GetButtonPressingCount(Input::BUTTON_MIDDLE) > 0)
        {
            // �J�����̍����������߂�
            Vector3 leftDirection = Vector3::s_CrossProduct(direction_, upVector_);

            // �J�����̉����������߂�
            Vector3 downDirection = Vector3::s_CrossProduct(direction_, leftDirection);

            // �ړ��ʂ����߂�
            Vector3 movement = (leftDirection * MIDDLE_DRAG_CORRECTION_VALUE_ * static_cast<float>(mouseMovementX))
                + (downDirection * MIDDLE_DRAG_CORRECTION_VALUE_ * static_cast<float>(-mouseMovementY));

            // ���_�ƒ����_�Ɉړ��ʂ�ǉ�
            eyePoint_ += movement * moveScale_;
            targetPoint_ += movement * moveScale_;
        }

        // �E�N���b�N�����Ȃ���h���b�O�����ꍇ�̓h���b�O���������ɉ����ăJ��������]
        if (Input::C_MouseManager::s_GetInstance()->GetButtonPressingCount(Input::BUTTON_RIGHT) > 0)
        {
            // �}�E�X�̈ړ��ʂ����]�p�x�����߂�
            mouseRightDragAngleX_ -= mouseMovementX * RIGHT_DRAG_CORRECTION_VALUE;
            mouseRightDragAngleY_ += mouseMovementY * RIGHT_DRAG_CORRECTION_VALUE;

            // �W���o�����b�N�ɂȂ�Ȃ��悤������]�Ɍ��E��݂���
            mouseRightDragAngleY_ = std::max(mouseRightDragAngleY_, static_cast<float>(Math::s_PI_DIVISION2 - RIGHT_DRAG_CORRECTION_VALUE) * -1.0f);
            mouseRightDragAngleY_ = std::min(mouseRightDragAngleY_, static_cast<float>(Math::s_PI_DIVISION2 - RIGHT_DRAG_CORRECTION_VALUE));

            // ��]�s����쐬
            Matrix4 rotateMatrix = Matrix4::s_CreateRotationYawPitchRoll(mouseRightDragAngleY_,
                mouseRightDragAngleX_,
                0.0f);

            // ������Vector4�ɕϊ�
            Vector4 distanceV4(distance_, 0.0f);

            // �����ɉ�]�s��������A���_�ɒǉ�
            distanceV4 = rotateMatrix * distanceV4;
            eyePoint_ = targetPoint_ + distanceV4.xyz_;
        }

        // �}�E�X�z�C�[������ɃX�N���[�������ꍇ�̓J������O�ֈړ�
        if (Input::C_MouseManager::s_GetInstance()->GetWheelScrollingCount(Input::WHEEL_SCROLL_UP) > 0)
        {
            eyePoint_ -= direction_ * moveScale_;
            targetPoint_ -= direction_ * moveScale_;
        }

        // �}�E�X�z�C�[�������ɃX�N���[�������ꍇ�̓J���������ֈړ�
        if (Input::C_MouseManager::s_GetInstance()->GetWheelScrollingCount(Input::WHEEL_SCROLL_DOWN) > 0)
        {
            eyePoint_ += direction_ * moveScale_;
            targetPoint_ += direction_ * moveScale_;
        }

        // 1�t���[���O�̃}�E�X�̍��W��ێ�
        previousMousePositionX_ = mousePositionX;
        previousMousePositionY_ = mousePositionY;
    }
}