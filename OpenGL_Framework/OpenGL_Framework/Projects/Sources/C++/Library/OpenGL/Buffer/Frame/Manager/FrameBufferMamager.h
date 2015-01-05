/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../../Singleton/Singleton.h"
#include "../FrameBuffer.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    //-------------------------------------------------------------
    //!
    //! @brief �t���[���o�b�t�@�}�l�[�W���[
    //! @brief �t���[���o�b�t�@���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_FrameBufferManager : public Singleton::C_Singleton<C_FrameBufferManager>
    {
        friend C_Singleton<C_FrameBufferManager>;
    public:
        void Entry(const FrameBufferPtr& prFrameBuffer, const std::string& rId);                        // �o�^����
        void Remove(const std::string& rId);                                                            // ��������
        void AllRemove();                                                                               // �S�Ẵt���[���o�b�t�@������
        boost::optional<const FrameBufferPtr&> GetFrameBuffer(const std::string& rId) const;            // �t���[���o�b�t�@���擾
    private:
        /* �O���錾 */
        class C_FrameBufferManagerImpl;

        std::unique_ptr<C_FrameBufferManagerImpl> upImpl_;                                              ///< @brief �������

        C_FrameBufferManager();                                                                         // �R���X�g���N�^
        ~C_FrameBufferManager() override;                                                               // �f�X�g���N�^
    };
}