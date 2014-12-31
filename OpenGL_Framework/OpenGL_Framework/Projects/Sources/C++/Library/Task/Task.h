/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �^�X�N
//! @brief �^�X�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Task
{
    /* �O���錾 */
    class IC_Task;


    /* �ʖ� */
    using TaskPtr = std::shared_ptr<IC_Task>;                                   // TaskPtr�^
    using TaskWeakPtr = std::weak_ptr<IC_Task>;                                 // TaskWeakPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �^�X�N( �C���^�[�t�F�[�X )
    //! @brief �^�X�N�̃C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    class IC_Task
    {
    public:
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        IC_Task(float updatePriority, float drawPriority) :

            // �X�V�D��x
            updatePriority_(updatePriority),

            // �`��D��x
            drawPriority_(drawPriority)

        {
        }

        virtual ~IC_Task() = default;                                           //!< @brief �f�t�H���g�f�X�g���N�^
        virtual bool Update() = 0;                                              //!< @brief �X�V����
        virtual void Draw() = 0;                                                //!< @brief �`�揈��

        /*************************************************************//**
         *
         *  @brief  �X�V�D��x���擾����
         *  @param  �Ȃ�
         *  @return �X�V�D��x
         *
         ****************************************************************/
        float GetUpdatePriority() const
        {
            return updatePriority_;
        }

        /*************************************************************//**
         *
         *  @brief  �`��D��x���擾����
         *  @param  �Ȃ�
         *  @return �`��D��x
         *
         ****************************************************************/
        float GetDrawPriority() const
        {
            return drawPriority_;
        }
    private:
        float updatePriority_ = 0.0f;                                           ///< @brief �X�V�D��x
        float drawPriority_ = 0.0f;                                             ///< @brief �`��D��x
    };


    //-------------------------------------------------------------
    //!
    //! @brief �^�X�N
    //! @brief �^�X�N��\���N���X
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_Task : public IC_Task
    {
    public:

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �D��x
         *
         ****************************************************************/
        C_Task(const std::shared_ptr<T>& sprTask, float updatePriority, float drawPriority) : IC_Task(updatePriority, drawPriority),

            // �^�X�N
            spTask_(sprTask)

        {
        }

        ~C_Task() override = default;                                   //!< @brief �f�t�H���g�f�X�g���N�^

        /*************************************************************//**
         *
         *  @brief  �X�V�������s��
         *  @param  �Ȃ�
         *  @return �^�X�N�𑱍s�Ftrue
         *  @return �^�X�N���I���Ffalse
         *
         ****************************************************************/
        bool Update()
        {
            return spTask_->Update();
        }

        /*************************************************************//**
         *
         *  @brief  �`�揈�����s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void Draw()
        {
            spTask_->Draw();
        }

        /*************************************************************//**
         *
         *  @brief  �^�X�N���擾����
         *  @param  �Ȃ�
         *  @return �^�X�N
         *
         ****************************************************************/
        T* GetTask() const
        {
            return spTask_.get();
        }
    private:
        std::shared_ptr<T> spTask_;                                     ///< @brief �^�X�N
    };
}