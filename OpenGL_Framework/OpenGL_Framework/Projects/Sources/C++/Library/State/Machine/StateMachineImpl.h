//-------------------------------------------------------------
//!
//! @brief �X�e�[�g
//! @brief ��Ԋ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace State
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �I�[�i�[
     *  @param  ���݂̃X�e�[�g
     *  @param  �O���[�o���X�e�[�g
     *
     ****************************************************************/
    template<typename T>
    C_StateMachine<T>::C_StateMachine(T* pOwner) :

        // �I�[�i�[
        pOwner_(pOwner)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    C_StateMachine<T>::~C_StateMachine()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�[�g�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::Update() const
    {
        // �O���[�o���X�e�[�g�̍X�V����
        if (pGlobalState_) pGlobalState_->Execute(pOwner_);

        // ���݂̃X�e�[�g�̍X�V����
        if (pCurrentState_) pCurrentState_->Execute(pOwner_);
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  ���b�Z�[�W
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_StateMachine<T>::MessageProcess(const GameObject::Message::S_Telegram& rTelegram) const
    {
        // ���݂̃X�e�[�g�փ��b�Z�[�W����
        if (pCurrentState_ && pCurrentState_->MessageProcess(pOwner_, rTelegram) == true) return true;

        // �O���[�o���X�e�[�g�փ��b�Z�[�W����
        if (pGlobalState_ && pGlobalState_->MessageProcess(pOwner_, rTelegram) == true) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �V�����X�e�[�g�ɕύX����
     *  @param  �V�����X�e�[�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::ChangeState(StatePtr pNewState)
    {
        assert(pNewState);

        // ���݂̃X�e�[�g���ȑO�̃X�e�[�g�ɂ���
        pPreviousState_ = pCurrentState_;

        // ���݂̃X�e�[�g�̏I������
        if (pCurrentState_) pCurrentState_->Exit(pOwner_);

        // �V�����X�e�[�g�ɐ؂�ւ���
        pCurrentState_ = pNewState;

        // �V�����X�e�[�g�̊J�n����
        pCurrentState_->Enter(pOwner_);
    }


    /*************************************************************//**
     *
     *  @brief  �ȑO�̃X�e�[�g�ɕύX����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::RevertToPreviousState()
    {
        ChangeState(pPreviousState_);
    }


    /*************************************************************//**
     *
     *  @brief  ���݂̃X�e�[�g���m�F����
     *  @param  �X�e�[�g
     *  @return ���݂̃X�e�[�g�Ɠ����Ftrue
     *  @return ���݂̃X�e�[�g���Ⴄ�Ffalse
     *
     ****************************************************************/
    template<typename T>
	bool C_StateMachine<T>::CheckCurrentState(StatePtr pState) const
    {
		return (typeid(*pCurrentState_) == typeid(*pState)) ? true : false;
    }


    /*************************************************************//**
     *
     *  @brief  ���݂̃X�e�[�g���擾����
     *  @param  �Ȃ�
     *  @return ���݂̃X�e�[�g
     *
     ****************************************************************/
    template<typename T>
    typename C_StateMachine<T>::StatePtr C_StateMachine<T>::GetCurrentState() const
    {
        return pCurrentState_;
    }


    /*************************************************************//**
     *
     *  @brief  �ȑO�̃X�e�[�g���擾����
     *  @param  �Ȃ�
     *  @return �ȑO�̃X�e�[�g
     *
     ****************************************************************/
    template<typename T>
    typename C_StateMachine<T>::StatePtr C_StateMachine<T>::GetPreviousState() const
    {
        return pPreviousState_;
    }


    /*************************************************************//**
     *
     *  @brief  �O���[�o���X�e�[�g���擾����
     *  @param  �Ȃ�
     *  @return �O���[�o���X�e�[�g
     *
     ****************************************************************/
    template<typename T>
    typename C_StateMachine<T>::StatePtr C_StateMachine<T>::GetGlobalState() const
    {
        return pGlobalState_;
    }


    /*************************************************************//**
     *
     *  @brief  ���݂̃X�e�[�g��ݒ肷��
     *  @param  ���݂̃X�e�[�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::SetCurrentState(StatePtr pCurrentState)
    {
        pCurrentState_ = pCurrentState;
    }


    /*************************************************************//**
     *
     *  @brief  �ȑO�̃X�e�[�g��ݒ肷��
     *  @param  �ȑO�̃X�e�[�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::SetPreviousState(StatePtr pPreviousState)
    {
        pPreviousState_ = pPreviousState;
    }


    /*************************************************************//**
     *
     *  @brief  �ȑO�̃X�e�[�g��ݒ肷��
     *  @param  �ȑO�̃X�e�[�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::SetGlobalState(StatePtr pGlobalState)
    {
        pGlobalState_ = pGlobalState;
    }
}