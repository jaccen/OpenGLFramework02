/* �w�b�_�t�@�C�� */
#include "BaseBackground.h"
#include "BackgroundStraightMoveLogic.h"


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
    C_BaseBackground::C_BaseBackground(const std::string& rId, int32_t type) : C_GameObject(rId, type)
    {
        upMoveLogic_ = std::make_unique<C_BackgroundStraightMoveLogic>();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseBackground::~C_BaseBackground()
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
    bool C_BaseBackground::Update()
    {
        DoUpdate();

        upMoveLogic_->Process(this);

        if (lifeFrame_ == frameCounter_.GetCount())
        {
            existenceFlag_ = false;
        }
        else
        {
            frameCounter_.CountUp();
        }

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBackground::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BaseBackground::MessageProcess(const Telegram& rTelegram)
    {
        return DoMessageProcess(rTelegram);
    }


    /*************************************************************//**
     *
     *  @brief  ���W���擾����
     *  @param  �Ȃ�
     *  @return ���W
     *
     ****************************************************************/
    const Vector3& C_BaseBackground::GetPosition() const
    {
        return position_;
    }


    /*************************************************************//**
     *
     *  @brief  ��]�ʂ��擾����
     *  @param  �Ȃ�
     *  @return ��]��
     *
     ****************************************************************/
    const Vector3& C_BaseBackground::GetRotation() const
    {
        return rotation_;
    }


    /*************************************************************//**
     *
     *  @brief  �ړ����W�b�N���擾����
     *  @param  �Ȃ�
     *  @return �ړ����W�b�N
     *
     ****************************************************************/
    C_BackgroundMoveLogic* C_BaseBackground::GetMoveLogic() const
    {
        return upMoveLogic_.get();
    }


    /*************************************************************//**
     *
     *  @brief  ���W��ݒ肷��
     *  @param  ���W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBackground::SetPosition(const Vector3& rPosition)
    {
        position_ = rPosition;
    }


    /*************************************************************//**
     *
     *  @brief  ��]�ʂ�ݒ肷��
     *  @param  ��]��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBackground::SetRotation(const Vector3& rRotation)
    {
        rotation_ = rRotation;
    }


    /*************************************************************//**
     *
     *  @brief  �g�嗦��ݒ肷��
     *  @param  �g�嗦
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBackground::SetScale(const Vector3& rScale)
    {
        scale_ = rScale;
    }


    /*************************************************************//**
     *
     *  @brief  �����t���[������ݒ肷��
     *  @param  �����t���[����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBackground::SetLifeFrame(int32_t lifeFrame)
    {
        lifeFrame_ = lifeFrame;
    }
}