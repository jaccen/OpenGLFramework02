//-------------------------------------------------------------
//!
//! @brief �^�X�N
//! @brief �^�X�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Task
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    C_SpecialTaskSystem<T>::C_SpecialTaskSystem()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    C_SpecialTaskSystem<T>::~C_SpecialTaskSystem()
    {
        if (pUpdateTaskList_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �^�X�N�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_SpecialTaskSystem<T>::Update()
    {
        // �\��^�X�N�̃}�[�W����
        MergeReserveTask();

        // ���[�v�J�E���^
        int32_t loopCount = 0;

        // �C�e���[�^
        auto iterator = pUpdateTaskList_.begin();

        // �S�Ẵ^�X�N���X�V
        while (iterator != pUpdateTaskList_.end())
        {
            // �X�V��A���̃^�X�N���I�����ׂ��ꍇ�̓��X�g���珜������
            if ((*iterator)->Update() == false)
            {
                iterator = pUpdateTaskList_.erase_after(std::next(pUpdateTaskList_.before_begin(), loopCount));
                continue;
            }

            ++iterator;
            ++loopCount;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �^�X�N�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_SpecialTaskSystem<T>::Draw()
    {
        // ���[�v�J�E���^
        int32_t loopCount = 0;

        // �C�e���[�^
        auto iterator = wpDrawTaskList_.begin();

        // �S�Ẵ^�X�N��`��
        while (iterator != wpDrawTaskList_.end())
        {
            // �Ď����Ă���^�X�N���擾�ł����ꍇ�͕`��A�ł��Ȃ��ꍇ�͂��̃^�X�N����������
            if ((*iterator).expired() == false)
            {
                auto pTask = (*iterator).lock();
                pTask->Draw();

                ++iterator;
                ++loopCount;
            }
            else
            {
                iterator = wpDrawTaskList_.erase_after(std::next(wpDrawTaskList_.before_begin(), loopCount));
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵ^�X�N����������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_SpecialTaskSystem<T>::AllRemove()
    {
        pUpdateTaskList_.clear();
        wpDrawTaskList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�D��x�ł̃\�[�g��L��������
     *  @param  �L�����𔻒f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_SpecialTaskSystem<T>::EnableUpdatePrioritySort(bool validFlag)
    {
        updatePrioritySortFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �`��D��x�ł̃\�[�g��L��������
     *  @param  �L�����𔻒f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_SpecialTaskSystem<T>::EnableDrawPrioritySort(bool validFlag)
    {
        drawPrioritySortFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �^�X�N���X�g���擾����
     *  @param  �Ȃ�
     *  @return �^�X�N���X�g
     *
     ****************************************************************/
    template<typename T>
    std::forward_list<typename C_SpecialTaskSystem<T>::SpecialTaskPtr>& C_SpecialTaskSystem<T>::GetTaskList()
    {
        return pUpdateTaskList_;
    }


    /*************************************************************//**
     *
     *  @brief  �\��^�X�N�̃}�[�W���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_SpecialTaskSystem<T>::MergeReserveTask()
    {
        if (pReserveTasks_.empty() == false)
        {
            // �\��^�X�N���e�^�X�N���X�g�Ƀ}�[�W
            for (auto& prReserveTask : pReserveTasks_)
            {
                pUpdateTaskList_.push_front(prReserveTask);
                wpDrawTaskList_.emplace_front(prReserveTask);
            }

            // �e�^�X�N���X�g��D��x�Ń\�[�g
            if (updatePrioritySortFlag_ == true) pUpdateTaskList_.sort(C_UpdateTaskSortObject);
            if (drawPrioritySortFlag_ == true) wpDrawTaskList_.sort(C_DrawTaskSortObject);

            pReserveTasks_.clear();
        }
    }
}