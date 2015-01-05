/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../../Singleton/Singleton.h"
#include "../PrimitiveBuffer.h"


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
    //! @brief �v���~�e�B�u�o�b�t�@�}�l�[�W���[
    //! @brief �v���~�e�B�u�o�b�t�@���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_PrimitiveBufferManager : public Singleton::C_Singleton<C_PrimitiveBufferManager>
    {
        friend C_Singleton<C_PrimitiveBufferManager>;
    public:
        void Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId);                    // �o�^����
        void Remove(const std::string& rId);                                                                // ��������
        void AllRemove();                                                                                   // �S�Ẵv���~�e�B�u�o�b�t�@������
        boost::optional<const PrimitiveBufferPtr&> GetPrimitiveBuffer(const std::string& rId) const;        // �v���~�e�B�u�o�b�t�@���擾
    private:
        /* �O���錾 */
        class C_PrimitiveBufferManagerImpl;

        std::unique_ptr<C_PrimitiveBufferManagerImpl> upImpl_;                                              ///< @brief �������

        C_PrimitiveBufferManager();                                                                         // �R���X�g���N�^
        ~C_PrimitiveBufferManager() override;                                                               // �f�X�g���N�^
    };
}