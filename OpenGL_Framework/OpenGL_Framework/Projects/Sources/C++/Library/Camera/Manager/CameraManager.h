/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"



//-------------------------------------------------------------
//!
//! @brief �J����
//! @brief �J�����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Camera
{
    /* �O���錾 */
    class IC_Camera;


    /* �ʖ� */
    using CameraPtr = std::shared_ptr<IC_Camera>;                                           // CameraPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �J�����}�l�[�W���[
    //! @brief �J�������Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_CameraManager : public Singleton::C_Singleton<C_CameraManager>
    {
        friend C_Singleton<C_CameraManager>;                                                // �V���O���g���N���X���t�����h��
    public:
        C_CameraManager();                                                                  // �R���X�g���N�^
        ~C_CameraManager() override;                                                        // �f�X�g���N�^
        void Update();                                                                      // �X�V����
        void Entry(const CameraPtr& prCamera,                                               // �o�^����
                   const std::string& rId,
                   bool updateFlag = true);
        void Remove(const std::string& rId);                                                // ��������
        void AllRemove();                                                                   // �S�ẴJ����������
        boost::optional<const CameraPtr&> GetCamera(const std::string& rId) const;          // �J�������擾
    private:
        /* �O���錾 */
        class C_CameraManagerImpl;

        std::unique_ptr<C_CameraManagerImpl> upImpl_;                                       ///< @brief �������
    };
}
